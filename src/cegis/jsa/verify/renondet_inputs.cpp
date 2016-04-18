#include <cegis/cegis-util/program_helper.h>

#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/verify/renondet_inputs.h>

#define VALID_HEAP JSA_PREFIX "assume_valid_heap"
#define VALID_LIST JSA_PREFIX "assume_valid_list"
#define VALID_IT JSA_PREFIX "assume_valid_iterator"

namespace
{
void call_assume(const symbol_tablet &st, const char * const type,
    const code_function_callt::argumentst &args, goto_programt &body,
    const goto_programt::targett &pos)
{
  const goto_programt::targett assume=body.insert_after(pos);
  assume->source_location=jsa_builtin_source_location();
  assume->type=goto_program_instruction_typet::FUNCTION_CALL;
  code_function_callt call;
  call.function()=st.lookup(type).symbol_expr();
  call.arguments()=args;
  assume->code=call;
}

void call_assume(const symbol_tablet &st, const char * const type,
    const exprt &arg, goto_programt &body, const goto_programt::targett &pos)
{
  const code_function_callt::argumentst args(1, arg);
  call_assume(st, type, args, body, pos);
}

void call_assume(const symbol_tablet &st, const char * const type,
    const address_of_exprt &heap, const exprt &arg, goto_programt &body,
    const goto_programt::targett &pos)
{
  const code_function_callt::argumentst args={ heap, arg };
  call_assume(st, type, args, body, pos);
}
}

void assume_renondet_inputs_valid(jsa_programt &prog)
{
  if (prog.counterexample_locations.empty()) return;
  const symbol_tablet &st=prog.st;
  goto_programt &body=get_entry_body(prog.gf);

  address_of_exprt h;
  for (const goto_programt::targett &pos : prog.inductive_step_renondets)
  {
    const irep_idt &id=get_affected_variable(*pos);
    const symbol_exprt lhs(st.lookup(id).symbol_expr());
    const typet &type=lhs.type();
    if (is_jsa_heap(type))
    {
      h=address_of_exprt(lhs);
      call_assume(st, VALID_HEAP, h, body, pos);
    } else if (is_jsa_list(id)) call_assume(st, VALID_LIST, h, lhs, body, pos);
    else if (is_jsa_iterator(id)) call_assume(st, VALID_IT, h, lhs, body, pos);
  }
}
