#include <cegis/jsa/constraint/jsa_constraint_factory.h>
#include <cegis/jsa/verify/extract_counterexample.h>
#include <cegis/jsa/verify/renondet_inputs.h>
#include <cegis/jsa/verify/jsa_symex_verify.h>

jsa_symex_verifyt::jsa_symex_verifyt(const jsa_programt &program) :
    original_program(program)
{
}

jsa_symex_verifyt::~jsa_symex_verifyt()
{
}

void jsa_symex_verifyt::process(const candidatet &candidate)
{
  program=original_program;
  insert_jsa_constraint(program, false);
  assume_renondet_inputs_valid(program);

  if (candidate.query.empty()) return;
  // TODO: Implement!
  assert(false);
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
