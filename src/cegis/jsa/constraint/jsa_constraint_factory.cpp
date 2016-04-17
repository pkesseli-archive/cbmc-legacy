#include <util/expr_util.h>
#include <util/simplify_expr.h>

#include <cegis/cegis-util/program_helper.h>
#include <cegis/invariant/meta/meta_variable_names.h>
#include <cegis/invariant/util/invariant_program_helper.h>
#include <cegis/instrument/meta_variables.h>

#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/constraint/jsa_constraint_factory.h>

namespace
{
symbol_exprt as_symbol(const symbol_tablet &st, const irep_idt &id)
{
  return st.lookup(id).symbol_expr();
}

void restrict_true(const jsa_programt &prog, goto_programt &body,
    const goto_programt::targett &pos,
    const goto_program_instruction_typet instr_type)
{
  const goto_programt::targett assume=body.insert_after(pos);
  assume->type=instr_type;
  const symbol_exprt smb(as_symbol(prog.st, get_affected_variable(*pos)));
  assume->guard=notequal_exprt(smb, gen_zero(smb.type()));
  assume->source_location=jsa_builtin_source_location();
}

void add_guard_goto(const jsa_programt &prog, goto_programt &body)
{
  const goto_programt::targett guard_check=body.insert_after(
      std::next(prog.inductive_assumption));
  const namespacet ns(prog.st);
  guard_check->type=goto_program_instruction_typet::GOTO;
  guard_check->guard=simplify_expr(not_exprt(prog.guard), ns);
  guard_check->targets.push_back(prog.property_entailment);
  const goto_programt::targett goto_end=body.insert_after(
      std::next(prog.inductive_step));
  goto_end->type=goto_program_instruction_typet::GOTO;
  goto_end->targets.push_back(std::next(prog.property_entailment, 2));
  body.compute_target_numbers();
}
}

void insert_jsa_constraint(jsa_programt &prog, const bool use_assume)
{
  const goto_program_instruction_typet instr_type(use_assume ? ASSUME : ASSERT);
  goto_programt &body=get_entry_body(prog.gf);
  restrict_true(prog, body, prog.base_case, instr_type);
  restrict_true(prog, body, prog.inductive_assumption, ASSUME);
  restrict_true(prog, body, prog.inductive_step, instr_type);
  restrict_true(prog, body, prog.property_entailment, instr_type);
  add_guard_goto(prog, body);
}
