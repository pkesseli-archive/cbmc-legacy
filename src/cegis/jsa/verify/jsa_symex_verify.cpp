#include <cegis/jsa/constraint/jsa_constraint_factory.h>
#include <cegis/jsa/verify/jsa_symex_verify.h>

// XXX: Debug
#include <iostream>
// XXX: Debug

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
  insert_jsa_constraint(program);
  // XXX: Debug
  std::cout << "<jsa_symex_verifyt>" << std::endl;
  const namespacet ns(program.get_st());
  program.get_gf().output(ns, std::cout);
  std::cout << "</jsa_symex_verifyt>" << std::endl;
  // XXX: Debug
  if (candidate.constraints.empty()) return;
  // TODO: Implement!
  assert(false);
}

const symbol_tablet &jsa_symex_verifyt::get_symbol_table() const
{
  return program.get_st();
}

const goto_functionst &jsa_symex_verifyt::get_goto_functions() const
{
  return program.get_gf();
}

void jsa_symex_verifyt::convert(counterexamplest &counterexamples,
    const goto_tracet &trace)
{
  // TODO: Implement!
}
