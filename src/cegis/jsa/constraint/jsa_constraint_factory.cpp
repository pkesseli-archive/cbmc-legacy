#include <util/expr_util.h>

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

//void assume_true(jsa_programt &prog, goto_programt &body,
//    const goto_programt::targett &pos)
//{
//  const goto_programt::targett assume_Sx0=body.insert_after(pos);
//  assume_Sx0->type=goto_program_instruction_typet::ASSUME;
//  const symbol_exprt smb(as_symbol(prog.st, get_affected_variable(*pos)));
//  assume_Sx0->guard=notequal_exprt(smb, gen_zero(smb.type()));
//  assume_Sx0->source_location=jsa_builtin_source_location();
//}
//
//void add_invariant_step_check(const jsa_programt &prog, goto_programt &body,
//    const invariant_programt::invariant_loopt &loop, const size_t loop_id)
//{
//  const goto_programt::targett guard_check=body.insert_before(loop.body.begin);
//  guard_check->type=goto_program_instruction_typet::GOTO;
//  const symbol_tablet &st=prog.st;
//  const symbol_exprt Gx(as_symbol(st, get_cegis_meta_name(get_Gx(loop_id))));
//  guard_check->guard=notequal_exprt(Gx, gen_zero(Gx.type()));
//  guard_check->targets.push_back(loop.body.end);
//  guard_check->source_location=jsa_builtin_source_location();
//  const symbol_exprt Ix_prime(
//      as_symbol(st, get_affected_variable(*loop.meta_variables.Ix_prime)));
//  const goto_programt::targett inv_assert=body.insert_after(
//      loop.meta_variables.Ix_prime);
//  inv_assert->type=goto_program_instruction_typet::ASSERT;
//  inv_assert->guard=notequal_exprt(Ix_prime, gen_zero(Ix_prime.type()));
//  inv_assert->source_location=jsa_builtin_source_location();
//}

void add_user_assertion_check(const jsa_programt &prog, goto_programt &body,
    const goto_programt::targett end)
{
//  const goto_programt::targett assrt=insert_before_preserve_labels(body, end);
//  assrt->type=goto_program_instruction_typet::ASSERT;
//  const symbol_tablet &st=prog.st;
//  const symbol_exprt Ax(as_symbol(st, get_affected_variable(*safety.Ax)));
//  assrt->guard=notequal_exprt(Ax, gen_zero(Ax.type()));
//  assrt->source_location=jsa_builtin_source_location();
}
}

void insert_jsa_constraint(jsa_programt &prog)
{
//  goto_functionst &gf=prog.gf;
//  goto_programt &body=get_entry_body(gf);
//  assume_true(prog, body, prog.safety.Ix0);
//  size_t loop_id=0;
//  const invariant_programt::invariant_loopst loops=prog.safety.get_loops();
//  for (const invariant_programt::invariant_loopt * const loop : loops)
//  {
//    assume_true(prog, body, loop->meta_variables.Ix);
//    add_invariant_step_check(prog, body, *loop, loop_id++);
//  }
//  add_user_assertion_check(prog, body, loops.back()->body.end);
//  gf.compute_target_numbers();
}
