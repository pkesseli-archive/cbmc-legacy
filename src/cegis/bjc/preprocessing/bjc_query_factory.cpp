#include <ansi-c/c_types.h>
#include <ansi-c/cprover_library.h>
#include <util/arith_tools.h>
#include <util/expr_util.h>
#include <goto-programs/goto_convert_functions.h>

#include <cegis/cegis-util/program_helper.h>

#include <cegis/instrument/literals.h>
#include <cegis/instrument/instrument_var_ops.h>
#include <cegis/instrument/meta_variables.h>
#include <cegis/instrument/cegis_library.h>
#include <cegis/bjc/options/bjc_program.h>
#include <cegis/bjc/preprocessing/bjc_literals.h>
#include <cegis/bjc/preprocessing/bjc_query_factory.h>

// XXX: Debug
#include <util/ui_message.h>
// XXX: Debug

namespace
{
goto_programt::targett find_loop_end(goto_programt &body)
{
  goto_programt::instructionst &instrs=body.instructions;
  for (goto_programt::targett it=instrs.begin(); it != instrs.end(); ++it)
    if (!is_builtin(it->source_location) && it->is_backwards_goto()) return it;
  assert(!"Could not identify loop to be refactored.");
}

pointer_typet heap_type()
{
  return pointer_typet(symbol_typet(BJC_HEAP_TYPE_NAME));
}

typet ptr_t()
{
  return unsigned_int_type();
}

pointer_typet instr_type()
{
  return pointer_typet(symbol_typet(CEGIS_INSTRUCTION_TYPE_NAME));
}

const char HEAP_ARG_BASE_NAME[]="heap";
const char ORIGINAL_LIST_ARG_BASE_NAME[]="original_list";
const char NEW_LIST_ARG_BASE_NAME[]="new_list";
const char LIST_ARG_BASE_NAME[]="list";
const char LHS_ARG_BASE_NAME[]="lhs";
const char RHS_ARG_BASE_NAME[]="rhs";
const char PRED_ARG_BASE_NAME[]="pred";
const char PRED_SZ_ARG_BASE_NAME[]="pred_sz";
const char QUERY_ARG_BASE_NAME[]="query";
const char SIZE_ARG_BASE_NAME[]="size";
const char BASE_NAME_SEP[]="::";

void add_parameter(code_typet &code_type, const typet &type,
    const char * const base_name)
{
  code_typet::parametert parameter(type);
  std::string arg_name(BJC_RUN_QUERY_FUNC_NAME);
  arg_name+=BASE_NAME_SEP;
  arg_name+=base_name;
  parameter.set_identifier(arg_name);
  parameter.set_base_name(HEAP_ARG_BASE_NAME);
  code_type.parameters().push_back(parameter);
}

code_typet new_list_func_type()
{
  code_typet type;
  type.return_type()=ptr_t();
  type.parameter_identifiers().push_back(HEAP_ARG_BASE_NAME);
  add_parameter(type, heap_type(), HEAP_ARG_BASE_NAME);
  return type;
}

code_typet query_execute_type()
{
  code_typet type;
  type.return_type()=c_bool_type();
  type.parameter_identifiers().push_back(HEAP_ARG_BASE_NAME);
  type.parameter_identifiers().push_back(ORIGINAL_LIST_ARG_BASE_NAME);
  type.parameter_identifiers().push_back(NEW_LIST_ARG_BASE_NAME);
  type.parameter_identifiers().push_back(QUERY_ARG_BASE_NAME);
  type.parameter_identifiers().push_back(SIZE_ARG_BASE_NAME);
  add_parameter(type, heap_type(), HEAP_ARG_BASE_NAME);
  add_parameter(type, ptr_t(), ORIGINAL_LIST_ARG_BASE_NAME);
  add_parameter(type, ptr_t(), NEW_LIST_ARG_BASE_NAME);
  add_parameter(type, instr_type(), QUERY_ARG_BASE_NAME);
  add_parameter(type, unsigned_char_type(), SIZE_ARG_BASE_NAME);
  return type;
}

code_typet query_filter_type()
{
  code_typet type;
  type.return_type()=void_typet();
  type.parameter_identifiers().push_back(HEAP_ARG_BASE_NAME);
  type.parameter_identifiers().push_back(LIST_ARG_BASE_NAME);
  type.parameter_identifiers().push_back(PRED_ARG_BASE_NAME);
  type.parameter_identifiers().push_back(PRED_SZ_ARG_BASE_NAME);
  add_parameter(type, heap_type(), HEAP_ARG_BASE_NAME);
  add_parameter(type, ptr_t(), LIST_ARG_BASE_NAME);
  add_parameter(type, instr_type(), PRED_ARG_BASE_NAME);
  add_parameter(type, unsigned_char_type(), PRED_SZ_ARG_BASE_NAME);
  return type;
}

code_typet query_equal_type()
{
  code_typet type;
  type.return_type()=c_bool_type();
  type.parameter_identifiers().push_back(HEAP_ARG_BASE_NAME);
  type.parameter_identifiers().push_back(LHS_ARG_BASE_NAME);
  type.parameter_identifiers().push_back(RHS_ARG_BASE_NAME);
  add_parameter(type, heap_type(), HEAP_ARG_BASE_NAME);
  add_parameter(type, ptr_t(), LHS_ARG_BASE_NAME);
  add_parameter(type, ptr_t(), RHS_ARG_BASE_NAME);
  return type;
}

void add_placeholder(symbol_tablet &symbol_table, const std::string &func_name,
    const code_typet &type)
{
  if (symbol_table.has_symbol(func_name)) return;
  symbolt symbol;
  symbol.name=func_name;
  symbol.base_name=symbol.name;
  symbol.pretty_name=symbol.base_name;
  symbol.type=type;
  symbol.is_lvalue=true;
  symbol.mode=ID_C;
  symbol.module=CEGIS_MODULE;
  symbol_table.add(symbol);
}

void add_bjc_library(symbol_tablet &st, goto_functionst &gf,
    const size_t num_vars, const size_t num_consts, const size_t max_sz,
    message_handlert &msg)
{
  add_cegis_execute_placeholder(st);
  add_placeholder(st, BJC_RUN_QUERY_FUNC_NAME, query_execute_type());
  add_placeholder(st, BJC_FILTER_FUNC_NAME, query_filter_type());
  add_placeholder(st, BJC_EQUAL_FUNC_NAME, query_equal_type());
  const std::set<irep_idt> functions={ CEGIS_EXECUTE, BJC_RUN_QUERY_FUNC_NAME,
  BJC_FILTER_FUNC_NAME, BJC_EQUAL_FUNC_NAME };
  std::string library_text(get_cegis_code_prefix(num_vars, num_consts, max_sz));
  library_text+=get_cprover_library_text(functions, st);
  add_library(library_text, st, msg);
  for (const irep_idt &func_name : functions)
    goto_convert(func_name, st, gf, msg);
  gf.compute_loop_numbers();
  gf.update();
}
}

void add_bjc_query(bjc_programt &prog, const size_t num_vars,
    const size_t num_consts, const size_t max_sz)
{
  goto_programt &body=get_entry_body(prog.gf);
  goto_programt::targett pos=find_loop_end(body);
  symbol_tablet &st=prog.st;
  goto_functionst &gf=prog.gf;
  const constant_exprt sz(from_integer(max_sz, unsigned_int_type()));
  const array_typet type(symbol_typet(CEGIS_INSTRUCTION_TYPE_NAME), sz);
  pos=declare_cegis_meta_variable(st, gf, pos, BJC_QUERY_VAR_NAME, type);
  prog.query_decl=pos;
  const typet bt(c_bool_type());
  pos=declare_cegis_meta_variable(st, gf, pos, BJC_QUERY_RESULT_VAR_NAME, bt);
  // XXX: Debug
  ui_message_handlert msg(ui_message_handlert::PLAIN, "");
  // XXX: Debug
  add_bjc_library(st, gf, num_vars, num_consts, max_sz, msg);
  code_function_callt call;
  const std::string res_var(get_cegis_meta_name(BJC_QUERY_RESULT_VAR_NAME));
  call.lhs()=st.lookup(res_var).symbol_expr();
  call.function()=st.lookup(BJC_RUN_QUERY_FUNC_NAME).symbol_expr();
  code_function_callt::argumentst &args=call.arguments();
  args.push_back(st.lookup(BJC_HEAP_SYMBOL_NAME).symbol_expr());
  args.push_back(st.lookup(BJC_LIST_SYMBOL_NAME).symbol_expr());
  args.push_back(st.lookup(BJC_LIST_COPY_SYMBOL_NAME).symbol_expr());
  const std::string bjc_query_var(get_cegis_meta_name(BJC_QUERY_VAR_NAME));
  const symbol_exprt query_symbol(st.lookup(bjc_query_var).symbol_expr());
  const index_exprt first_elem(query_symbol, gen_zero(unsigned_int_type()));
  args.push_back(address_of_exprt(first_elem));
  args.push_back(sz);
  pos=body.insert_after(pos);
  pos->source_location=default_cegis_source_location();
  pos->type=goto_program_instruction_typet::FUNCTION_CALL;
  pos->code=call;
  pos=body.insert_after(pos);
  pos->source_location=default_cegis_source_location();
  pos->type=goto_program_instruction_typet::ASSERT;
  const symbol_exprt result_symbol(st.lookup(res_var).symbol_expr());
  pos->guard=notequal_exprt(result_symbol, gen_zero(result_symbol.type()));
}
