#include <cegis/constant/default_cegis_constant_strategy.h>
#include <cegis/danger/preprocess/store_nondet_choices.h> // XXX: Move to invariant directory
#include <cegis/safety/meta/meta_variable_names.h>
#include <cegis/invariant/preprocess/add_invariants_and_temp_variables.h>
#include <cegis/invariant/preprocess/remove_loops_and_assertion.h>
#include <cegis/jsa/preprocessing/inline_user_program.h>
#include <cegis/jsa/preprocessing/jsa_preprocessing.h>

// XXX: Debug
#include <iostream>
// XXX: Debug

jsa_preprocessingt::jsa_preprocessingt(const optionst &options,
    const symbol_tablet &st, const goto_functionst &gf) :
    options(options), original_program(st, gf)
{
}

jsa_preprocessingt::~jsa_preprocessingt()
{
}

void jsa_preprocessingt::operator()()
{
  goto_functionst &gf=original_program.get_gf();
  inline_jsa_user_program(original_program.get_st(), gf);
  invariant_remove_loops_and_assertion(original_program.safety);
  store_skolem_choices(original_program.safety);
  gf.update();
  current_program=original_program;
}

void jsa_preprocessingt::operator()(const size_t max_length)
{
  current_program=original_program;
  safety_programt &safety=current_program.safety;
  default_cegis_constant_strategy(safety.st, safety.gf);
  store_x0_choices(safety);
  create_tmp_variables(safety, max_length);
  add_invariant_variables(safety, get_Ix0(), get_Ix, get_Ix_prime);
  safety.gf.update();
  // XXX: Debug
  const namespacet ns(safety.st);
  std::cout << "<jsa_preprocessing>" << std::endl;
  safety.gf.output(ns, std::cout);
  std::cout << "</jsa_preprocessing>" << std::endl;
  // XXX: Debug
}

size_t jsa_preprocessingt::get_min_solution_size() const
{
  return 1u;
}

const jsa_programt &jsa_preprocessingt::get_jsa_program() const
{
  return current_program;
}
