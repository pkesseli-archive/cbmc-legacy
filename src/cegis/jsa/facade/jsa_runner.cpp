#include <util/options.h>

#include <cegis/facade/runner_helper.h>
#include <cegis/options/parameters.h>
#include <cegis/seed/null_seed.h>

#include <cegis/symex/cegis_symex_learn.h>
#include <cegis/symex/cegis_symex_verify.h>
#include <cegis/genetic/lazy_fitness.h>
#include <cegis/genetic/ga_learn.h>
#include <cegis/genetic/match_select.h>
#include <cegis/jsa/value/jsa_genetic_solution.h>
#include <cegis/jsa/genetic/jsa_source_provider.h>
#include <cegis/jsa/genetic/jsa_random.h>
#include <cegis/jsa/genetic/jsa_genetic_verify.h>
#include <cegis/jsa/genetic/random_jsa_cross.h>
#include <cegis/jsa/genetic/random_jsa_mutate.h>
#include <cegis/jsa/genetic/jsa_genetic_convert.h>
#include <cegis/jsa/genetic/dynamic_jsa_test_runner.h>
#include <cegis/jsa/preprocessing/jsa_preprocessing.h>
#include <cegis/jsa/learn/jsa_symex_learn.h>
#include <cegis/jsa/verify/jsa_symex_verify.h>
#include <cegis/jsa/facade/jsa_runner.h>

namespace
{
typedef messaget::mstreamt mstreamt;

template<class verifyt, class prept>
int run_with_ga(const optionst &o, mstreamt &result, verifyt &verify,
    prept &prep)
{
  dynamic_jsa_test_runnert test_runner;
  typedef lazy_fitnesst<jsa_populationt,
                        dynamic_jsa_test_runnert,
                        jsa_genetic_counterexamplet> fitnesst;
  fitnesst fitness(test_runner);
  typedef match_selectt<jsa_populationt> selectt;
  const selectt::test_case_datat &test_case_data=fitness.get_test_case_data();
  const size_t rounds=o.get_unsigned_int_option(CEGIS_ROUNDS);
  const selectt select(test_case_data, rounds);
  jsa_randomt random;
  random_jsa_mutatet mutate;
  random_jsa_crosst cross;
  jsa_genetic_convertt convert;
  ga_learnt<const selectt,
            random_jsa_mutatet,
            random_jsa_crosst,
            fitnesst,
            jsa_genetic_convertt> learn(o, random, select, mutate,
                                        cross, fitness, convert);
  jsa_genetic_verifyt genetic_verify(verify);
  cegis_symex_verifyt<jsa_genetic_verifyt> oracle(o, genetic_verify);
  return run_cegis_with_statistics_wrapper(result, o, learn, oracle, prep);
}
}

int run_jsa(optionst &o, mstreamt &result, const symbol_tablet &st,
    const goto_functionst &gf)
{
  jsa_preprocessingt prep(o, st, gf);
  const jsa_programt &prog=prep.get_jsa_program();
  jsa_symex_learnt lcfg(prog);
  cegis_symex_learnt<jsa_preprocessingt, jsa_symex_learnt> learn(o, prep, lcfg);
  jsa_symex_verifyt vcfg(prog);
  return run_with_ga(o, result, vcfg, prep);
  cegis_symex_verifyt<jsa_symex_verifyt> oracle(o, vcfg);
  //return run_cegis_with_statistics_wrapper(result, o, learn, oracle, prep);
}
