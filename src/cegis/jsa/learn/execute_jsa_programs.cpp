#include <cegis/cegis-util/program_helper.h>
#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/learn/execute_jsa_programs.h>

namespace
{
}

void execute_jsa_learn_programs(jsa_programt &prog)
{
  const symbol_tablet &st=prog.st;
  goto_programt &body=get_entry_body(prog.gf);
  goto_programt::targett pos=body.insert_after(prog.base_case);
  pos->type=goto_program_instruction_typet::FUNCTION_CALL;
  pos->source_location=jsa_builtin_source_location();
  code_function_callt call;
  call.lhs()=st.lookup(get_affected_variable(*prog.base_case)).symbol_expr();
  call.function()=st.lookup(JSA_INV).symbol_expr();
}
