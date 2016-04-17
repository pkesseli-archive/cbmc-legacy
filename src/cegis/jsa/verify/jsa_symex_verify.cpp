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
  insert_jsa_constraint(program, false);
  // XXX: Debug
  std::cout << "<jsa_symex_verifyt>" << std::endl;
  const namespacet ns(program.st);
  program.gf.output(ns, std::cout);
  std::cout << "</jsa_symex_verifyt>" << std::endl;
  // XXX: Debug
  if (candidate.postcondition.empty()) return;
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
  // TODO: Implement!
}
