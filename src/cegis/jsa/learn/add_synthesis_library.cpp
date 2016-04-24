#include <ansi-c/cprover_library.h>
#include <ansi-c/c_types.h>
#include <util/bv_arithmetic.h>
#include <goto-programs/goto_convert_functions.h>
#include <linking/zero_initializer.h>

#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/learn/add_synthesis_library.h>

// XXX: Debug
#include <util/ui_message.h>
// XXX: Debug

#define CPROVER_INIT "__CPROVER_initialize"

namespace
{
void add_placenholder(symbol_tablet &st, const irep_idt &id)
{
  if (st.has_symbol(id)) return;
  symbolt symbol;
  symbol.name=id;
  symbol.base_name=symbol.name;
  symbol.pretty_name=symbol.base_name;
  symbol.type=signed_int_type();
  symbol.is_lvalue=true;
  symbol.mode=ID_C;
  symbol.module=JSA_MODULE;
  st.add(symbol);
}

std::string get_array_size(const typet &type)
{
  const irep_idt &type_id=type.id();
  if (ID_array == type_id)
  {
    const bv_arithmetict bv(to_array_type(type).size());
    return std::to_string(bv.to_integer().to_ulong());
  }
  assert(ID_pointer == type_id);
  return "0u";
}

std::string get_sizes(const symbol_tablet &st)
{
  const namespacet ns(st);
  const typet &type=ns.follow(st.lookup(JSA_HEAP_TAG).type);
  const struct_typet &struct_type=to_struct_type(type);
  std::string sizes("#define __CPROVER_JSA_MAX_CONCRETE_NODES ");
  sizes+=get_array_size(struct_type.get_component("concrete_nodes").type());
  sizes+="\n#define __CPROVER_JSA_MAX_ABSTRACT_NODES ";
  sizes+=get_array_size(struct_type.get_component("abstract_nodes").type());
  sizes+="\n#define __CPROVER_JSA_MAX_ITERATORS ";
  sizes+=get_array_size(struct_type.get_component("iterators").type());
  sizes+="\n#define __CPROVER_JSA_MAX_LISTS ";
  sizes+=get_array_size(struct_type.get_component("list_head_nodes").type());
  return sizes+='\n';
}

std::vector<irep_idt> get_functions(const symbol_tablet &st)
{
  std::vector<irep_idt> functions;
  for (const symbol_tablet::symbolst::value_type &symbol : st.symbols)
    if (ID_code == symbol.second.type.id()) functions.push_back(symbol.first);
  return functions;
}

bool is_jsa_constant(const symbolt &symbol)
{
  if (!symbol.is_static_lifetime) return false;
  return std::string::npos != id2string(symbol.name).find(JSA_CONSTANT_PREFIX);
}

void zero_new_global_vars(const symbol_tablet &st, goto_functionst &gf)
{
  goto_functionst::function_mapt &fm=gf.function_map;
  const goto_functionst::function_mapt::iterator it=fm.find(CPROVER_INIT);
  assert(fm.end() != it);
  goto_functionst::goto_functiont &init=it->second;
  assert(init.body_available());
  goto_programt &body=init.body;
  goto_programt::targett pos=std::prev(body.instructions.end(), 2);
  null_message_handlert msg;
  const source_locationt loc(jsa_builtin_source_location());
  const namespacet ns(st);
  for (const symbol_tablet::symbolst::value_type &symbol : st.symbols)
    if (is_jsa_constant(symbol.second))
    {
      pos=body.insert_after(pos);
      pos->type=goto_program_instruction_typet::ASSIGN;
      pos->source_location=loc;
      const symbol_exprt lhs(ns.lookup(symbol.first).symbol_expr());
      const exprt rhs(zero_initializer(lhs.type(), loc, ns, msg));
      pos->code=code_assignt(lhs, rhs);
    }
}
}

#define JSA_LIB "__CPROVER_jsa_assume_valid_heap"
#define QUERY_LIB "__CPROVER_jsa_query_execute"

void add_jsa_synthesis_library(jsa_programt &prog, const size_t max_sz,
    const size_t num_pred_ops)
{
  std::string library_text("#define JSA_SYNTHESIS_H_");
  library_text+="\n#define __CPROVER_JSA_MAX_QUERY_SIZE ";
  library_text+=std::to_string(max_sz + 1);
  library_text+="\n#define __CPROVER_JSA_MAX_PRED_SIZE ";
  library_text+=std::to_string(max_sz);
  library_text+='\n';
  library_text+=get_sizes(prog.st);
  const std::set<irep_idt> functions= { JSA_LIB, QUERY_LIB };
  symbol_tablet blank;
  add_placenholder(blank, JSA_LIB);
  add_placenholder(blank, QUERY_LIB);
  library_text+=get_cprover_library_text(functions, blank);
  blank.clear();
  //null_message_handlert msg;
  // XXX: Debug
  ui_message_handlert msg(ui_message_handlert::PLAIN, "");
  // XXX: Debug
  add_library(library_text, blank, msg);

  symbol_tablet &st=prog.st;
  for (const symbol_tablet::symbolst::value_type &symbol : blank.symbols)
    if (!st.has_symbol(symbol.first)) st.add(symbol.second);
  goto_functionst &gf=prog.gf;
  const std::vector<irep_idt> new_funcs(get_functions(blank));
  for (const irep_idt &func_name : new_funcs)
    goto_convert(func_name, st, gf, msg);
  zero_new_global_vars(blank, gf);
  gf.compute_loop_numbers();
  gf.update();
}
