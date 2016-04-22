#include <cegis/jsa/learn/add_synthesis_library.h>
#include <cegis/jsa/learn/insert_counterexample.h>
#include <cegis/jsa/learn/insert_predicates_and_queries.h>
#include <cegis/jsa/learn/execute_jsa_programs.h>
#include <cegis/jsa/learn/extract_candidate.h>
#include <cegis/jsa/learn/jsa_symex_learn.h>

// XXX: Debug
#include <iostream>
// XXX: Debug

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
  program=original_program;
  const goto_programt::targetst pred_ops(collect_pred_ops(program));
  add_jsa_synthesis_library(program, max_solution_size, pred_ops.size());
  instrument_pred_ops(program, pred_ops, op_ids, const_op_ids);
  insert_counterexamples(program, counterexamples);
  declare_jsa_predicates(program, max_solution_size);
  declare_jsa_query(program, max_solution_size);
  declare_jsa_invariant(program, max_solution_size);
  execute_jsa_learn_programs(program);
  program.gf.update();
}

void jsa_symex_learnt::set_word_width(const size_t word_width_in_bits)
{
  // XXX: Unsupported
}

void jsa_symex_learnt::convert(candidatet &current_candidate,
    const goto_tracet &trace, const size_t max_sz)
{
  extract_jsa_candidate(current_candidate, trace, max_sz, op_ids, const_op_ids);

  // XXX: Debug
  std::cout << "<jsa_symex_verifyt>" << std::endl;
  const namespacet ns(program.st);
  program.gf.output(ns, std::cout);
  std::cout << "</jsa_symex_verifyt>" << std::endl;
  assert(false);
  // XXX: Debug
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
  os << "TODO: print candidate" << messaget::mstreamt::end;
}
