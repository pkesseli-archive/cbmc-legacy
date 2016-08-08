#include <util/options.h>

#include <cegis/facade/runner_helper.h>
#include <cegis/options/parameters.h>
#include <cegis/seed/null_seed.h>

#include <cegis/symex/cegis_symex_learn.h>
#include <cegis/symex/cegis_symex_verify.h>
#include <cegis/genetic/lazy_fitness.h>
#include <cegis/genetic/ga_learn.h>
#include <cegis/genetic/match_select.h>
#include <cegis/genetic/learn_preprocess_seed.h>
#include <cegis/jsa/value/jsa_genetic_solution.h>
#include <cegis/jsa/genetic/jsa_source_provider.h>
#include <cegis/jsa/genetic/jsa_random.h>
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

template<class oraclet, class prept>
int run_with_ga(const symbol_tablet &st, const optionst &o, mstreamt &result,
    jsa_symex_learnt &l, oraclet &oracle, prept &prep)
{
  jsa_source_providert source_provider(o, l);
  dynamic_jsa_test_runnert test_runner(std::ref(source_provider));
  typedef lazy_fitnesst<jsa_populationt,
                        dynamic_jsa_test_runnert,
                        jsa_counterexamplet> fitnesst;
  fitnesst fitness(test_runner);
  typedef match_selectt<jsa_populationt> selectt;
  const selectt::test_case_datat &test_case_data=fitness.get_test_case_data();
  const size_t rounds=o.get_unsigned_int_option(CEGIS_ROUNDS);
  const selectt select(test_case_data, rounds);
  jsa_randomt rnd(st, l.get_pred_ops_count(), l.get_const_pred_ops_count());
  random_jsa_mutatet mutate(rnd);
  random_jsa_crosst cross(rnd);
  jsa_genetic_convertt convert(l);
  ga_learnt<const selectt,
            random_jsa_mutatet,
            random_jsa_crosst,
            fitnesst,
            jsa_genetic_convertt> learn(o, rnd, select, mutate, cross, fitness, convert);
  learn_preprocess_seedt<jsa_symex_learnt> seed(o, l);
  return run_cegis_with_statistics_wrapper(result, o, learn, oracle, prep, seed);
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
  cegis_symex_verifyt<jsa_symex_verifyt> oracle(o, vcfg);
  return run_with_ga(st, o, result, lcfg, oracle, prep);
  //return run_cegis_with_statistics_wrapper(result, o, learn, oracle, prep);
}
