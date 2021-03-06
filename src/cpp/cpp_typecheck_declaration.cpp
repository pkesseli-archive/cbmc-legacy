/*******************************************************************\

Module: C++ Language Type Checking

Author: Daniel Kroening, kroening@cs.cmu.edu

\********************************************************************/

#include <util/i2string.h>
#include <util/expr_util.h>

#include "cpp_typecheck.h"
#include "cpp_declarator_converter.h"

/*******************************************************************\

Function: cpp_typecheckt::convert_anonymous_union

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void cpp_typecheckt::convert_anonymous_union(
  cpp_declarationt &declaration,
  codet &code)
{
  codet new_code(ID_decl_block);
  new_code.reserve_operands(declaration.declarators().size());

  // unnamed object
  std::string identifier="#anon_union"+i2string(anon_counter++);

  irept name(ID_name);
  name.set(ID_identifier, identifier);
  name.set(ID_C_source_location, declaration.source_location());

  cpp_namet cpp_name;
  cpp_name.move_to_sub(name);
  cpp_declaratort declarator;
  declarator.name()=cpp_name;

  cpp_declarator_convertert cpp_declarator_converter(*this);

  const symbolt &symbol=
    cpp_declarator_converter.convert(declaration, declarator);

  if(!cpp_is_pod(declaration.type()))
  {
   error().source_location=follow(declaration.type()).source_location();
   error() << "anonymous union is not POD" << eom;
   throw 0;
  }

  codet decl_statement(ID_decl);
  decl_statement.reserve_operands(2);
  decl_statement.copy_to_operands(cpp_symbol_expr(symbol));

  new_code.move_to_operands(decl_statement);

  // do scoping
  symbolt union_symbol=symbol_table.symbols[follow(symbol.type).get(ID_name)];
  const irept::subt &components=union_symbol.type.add(ID_components).get_sub();

  forall_irep(it, components)
  {
    if(it->find(ID_type).id()==ID_code)
    {
      error().source_location=union_symbol.type.source_location();
      error() << "anonymous union `" << union_symbol.base_name
              << "' shall not have function members" << eom;
      throw 0;
    }

    const irep_idt &base_name=it->get(ID_base_name);

    if(cpp_scopes.current_scope().contains(base_name))
    {
      error().source_location=union_symbol.type.source_location();
      error() << "identifier `" << base_name << "' already in scope"
              << eom;
      throw 0;
    }

    cpp_idt &id=cpp_scopes.current_scope().insert(base_name);
    id.id_class = cpp_idt::SYMBOL;
    id.identifier=it->get(ID_name);
    id.class_identifier=union_symbol.name;
    id.is_member=true;
  }

  symbol_table.symbols[union_symbol.name].type.set(
    "#unnamed_object", symbol.base_name);

  code.swap(new_code);
}

/*******************************************************************\

Function: cpp_typecheckt::convert

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void cpp_typecheckt::convert(cpp_declarationt &declaration)
{
  // see if the declaration is empty
  if(declaration.find(ID_type).is_nil() &&
     !declaration.has_operands())
    return;

  // Record the function bodies so we can check them later.
  // This function is used recursively, so we save them.
  function_bodiest old_function_bodies=function_bodies;
  function_bodies.clear();

  // templates are done in a dedicated function
  if(declaration.is_template())
    convert_template_declaration(declaration);
  else
    convert_non_template_declaration(declaration);

  typecheck_function_bodies();
  function_bodies=old_function_bodies;
}

/*******************************************************************\

Function: cpp_typecheckt::convert_non_template_declaration

  Inputs:

 Outputs:

 Purpose:

\*******************************************************************/

void cpp_typecheckt::convert_non_template_declaration(
  cpp_declarationt &declaration)
{
  assert(!declaration.is_template());

  // we first check if this is a typedef
  typet &declaration_type=declaration.type();
  bool is_typedef=declaration.is_typedef();

  declaration.name_anon_struct_union();
  typecheck_type(declaration_type);
  
  // Elaborate any class template instance _unless_ we do a typedef.
  // These are only elaborated on usage!
  if(!is_typedef)
    elaborate_class_template(declaration_type);
  
  // Special treatment for anonymous unions
  if(declaration.declarators().empty() &&
     follow(declaration.type()).get_bool(ID_C_is_anonymous))
  {
    typet final_type=follow(declaration.type());

    if(final_type.id()!=ID_union)
    {
      error().source_location=final_type.source_location();
      error() << "top-level declaration does not declare anything"
              << eom;
      throw 0;
    }

    codet dummy;
    convert_anonymous_union(declaration, dummy);
  }

  // do the declarators (optional)
  Forall_cpp_declarators(it, declaration)
  {
    // copy the declarator (we destroy the original)
    cpp_declaratort declarator=*it;

    cpp_declarator_convertert cpp_declarator_converter(*this);

    cpp_declarator_converter.is_typedef=is_typedef;

    symbolt &symbol=cpp_declarator_converter.convert(
      declaration_type, declaration.storage_spec(),
      declaration.member_spec(), declarator);

    // any template instance to remember?
    if(declaration.find(ID_C_template).is_not_nil())
    {
      symbol.type.set(ID_C_template, declaration.find(ID_C_template));
      symbol.type.set(ID_C_template_arguments, declaration.find(ID_C_template_arguments));
    }

    // replace declarator by symbol expression
    exprt tmp=cpp_symbol_expr(symbol);
    it->swap(tmp);

    // is there a constructor to be called for the declarator?
    if(symbol.is_lvalue &&
       declarator.init_args().has_operands())
    {
      symbol.value=
        cpp_constructor(
          symbol.location,
          cpp_symbol_expr(symbol),
          declarator.init_args().operands());
    }
  }
}
