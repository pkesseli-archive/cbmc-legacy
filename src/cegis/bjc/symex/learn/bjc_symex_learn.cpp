#include <cegis/bjc/symex/learn/bjc_symex_learn.h>

bjc_symex_learnt::bjc_symex_learnt(const bjc_programt &program) :
    original_program(program)
{
}

bjc_symex_learnt::~bjc_symex_learnt()
{
}

void bjc_symex_learnt::process(const counterexamplest &counterexamples,
    const size_t max_solution_size)
{
  // TODO: Add counterexamples loop
  // TODO: Add counterexample array declarations
  // TODO: Add counterexample value retrieval at each prog.ce_target
}

void bjc_symex_learnt::process(size_t max_solution_size)
{
  // TODO: Add empty counterexample (for genetic source code)
}

void bjc_symex_learnt::set_word_width(size_t word_width_in_bits)
{
  // TODO: Implement
}

void bjc_symex_learnt::convert(candidatet &current_candidate,
    const class goto_tracet &trace, const size_t max_solution_size)
{
}

const symbol_tablet &bjc_symex_learnt::get_symbol_table() const
{
  return program.st;
}

const goto_functionst &bjc_symex_learnt::get_goto_functions() const
{
  return program.gf;
}

void bjc_symex_learnt::show_candidate(messaget::mstreamt &os,
    const candidatet &candidate)
{
  // TODO: Implement (Java 8 Stream query formatter?)
}
