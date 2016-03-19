#include <ansi-c/c_types.h>
#include <util/arith_tools.h>

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

code_typet query_execute_type()
{
  code_typet type;
  type.return_type()=void_typet();
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
  type.return_type()=c_bool_type();
  return type;
}
}

void add_bjc_query(bjc_programt &prog, const size_t max_size)
{
  goto_programt &body=get_entry_body(prog.gf);
  goto_programt::targett pos=find_loop_end(body);
  symbol_tablet &st=prog.st;
  goto_functionst &gf=prog.gf;
  const constant_exprt sz(from_integer(max_size, unsigned_int_type()));
  const array_typet type(symbol_typet(CEGIS_INSTRUCTION_TYPE_NAME), sz);
  pos=declare_cegis_meta_variable(st, gf, pos, BJC_QUERY_VAR_NAME, type);
  const typet bt(c_bool_type());
  pos=declare_cegis_meta_variable(st, gf, pos, BJC_QUERY_RESULT_VAR_NAME, bt);
  // XXX: Debug
  ui_message_handlert msg(ui_message_handlert::PLAIN, "");
  // XXX: Debug
  add_cegis_library(st, gf, msg, BJC_RUN_QUERY_FUNC_NAME, query_execute_type());
  code_function_callt call;
  const std::string res_var(get_cegis_meta_name(BJC_QUERY_RESULT_VAR_NAME));
  call.lhs()=st.lookup(res_var).symbol_expr();
  call.function()=st.lookup(BJC_RUN_QUERY_FUNC_NAME).symbol_expr();
  code_function_callt::argumentst &args=call.arguments();
  args.push_back(st.lookup(BJC_HEAP_SYMBOL_NAME).symbol_expr());
  args.push_back(st.lookup(BJC_LIST_SYMBOL_NAME).symbol_expr());
  args.push_back(st.lookup(BJC_LIST_COPY_SYMBOL_NAME).symbol_expr());
  const std::string bjcQueryVar(get_cegis_meta_name(BJC_QUERY_VAR_NAME));
  args.push_back(st.lookup(bjcQueryVar).symbol_expr());
  args.push_back(sz);
  pos=body.insert_after(pos);
  pos->source_location=default_cegis_source_location();
  pos->type=goto_program_instruction_typet::FUNCTION_CALL;
  pos->code=call;
  pos=body.insert_after(pos);
  pos->source_location=default_cegis_source_location();
  pos->type=goto_program_instruction_typet::ASSERT;
  pos->guard=st.lookup(res_var).symbol_expr();
}
