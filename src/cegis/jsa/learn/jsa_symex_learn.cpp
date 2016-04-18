#include <cegis/jsa/learn/jsa_symex_learn.h>

jsa_symex_learnt::jsa_symex_learnt(const jsa_programt &program) :
    original_program(program)
{
}

jsa_symex_learnt::~jsa_symex_learnt()
{
}

void jsa_symex_learnt::process(const counterexamplest &counterexamples,
    const size_t max_solution_size)
{
  assert(false);
  // TODO: Add counterexamples loop
  // TODO: Add counterexample array declarations
  // TODO: Add counterexample value retrieval at each prog.ce_target
}

void jsa_symex_learnt::set_word_width(const size_t word_width_in_bits)
{
  // XXX: Unsupported
}

void jsa_symex_learnt::convert(candidatet &current_candidate,
    const goto_tracet &trace, const size_t max_solution_size)
{
}

const symbol_tablet &jsa_symex_learnt::get_symbol_table() const
{
  return program.st;
}

const goto_functionst &jsa_symex_learnt::get_goto_functions() const
{
  return program.gf;
}

void jsa_symex_learnt::show_candidate(messaget::mstreamt &os,
    const candidatet &candidate)
{
  // TODO: Implement (Java 8 Stream query formatter?)
}
