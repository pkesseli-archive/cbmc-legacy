#include <cegis/jsa/constraint/jsa_constraint_factory.h>
#include <cegis/jsa/preprocessing/add_synthesis_library.h>
#include <cegis/jsa/verify/extract_counterexample.h>
#include <cegis/jsa/verify/insert_solution.h>
#include <cegis/jsa/verify/renondet_inputs.h>
#include <cegis/jsa/verify/jsa_symex_verify.h>

jsa_symex_verifyt::jsa_symex_verifyt(const jsa_programt &program) :
    original_program(program)
{
}

void jsa_symex_verifyt::process(const candidatet &cand)
{
  program=original_program;
  add_jsa_verification_library(program, cand.max_size, cand.num_pred_ops);
  insert_jsa_constraint(program, false);
  assume_renondet_inputs_valid(program);

  if (cand.invariant.empty()) return;
  insert_jsa_solution(program, cand);
}

const symbol_tablet &jsa_symex_verifyt::get_symbol_table() const
{
  return program.st;
}

const goto_functionst &jsa_symex_verifyt::get_goto_functions() const
{
  return program.gf;
}

void jsa_symex_verifyt::convert(counterexamplest &counterexamples,
    const goto_tracet &trace)
{
  counterexamples.push_back(counterexamplet());
  extract(program, counterexamples.back(), trace);
}
