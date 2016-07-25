#include <util/options.h>

#include <cegis/facade/runner_helper.h>
#include <cegis/options/parameters.h>
#include <cegis/seed/null_seed.h>

#include <cegis/symex/cegis_symex_learn.h>
#include <cegis/symex/cegis_symex_verify.h>
#include <cegis/genetic/lazy_fitness.h>
#include <cegis/genetic/match_select.h>
#include <cegis/jsa/value/jsa_genetic_solution.h>
#include <cegis/jsa/preprocessing/jsa_preprocessing.h>
#include <cegis/jsa/learn/jsa_symex_learn.h>
#include <cegis/jsa/verify/jsa_symex_verify.h>
#include <cegis/jsa/facade/jsa_runner.h>

namespace
{
typedef messaget::mstreamt mstreamt;

void run_with_ga(const optionst &o, mstreamt &result)
{
  //lazy_fitnesst
  const size_t rounds=o.get_unsigned_int_option(CEGIS_ROUNDS);
  const match_selectt<jsa_populationt>::test_case_datat test_case_data;
  const match_selectt<jsa_populationt> selectt(test_case_data, ::rand, rounds);
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
  return run_cegis_with_statistics_wrapper(result, o, learn, oracle, prep);
}
