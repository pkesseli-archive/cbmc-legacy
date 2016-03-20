#include <cegis/facade/cegis.h>
#include <cegis/options/parameters.h>
#include <cegis/seed/null_seed.h>
#include <cegis/symex/cegis_symex_learn.h>
#include <cegis/symex/cegis_symex_verify.h>
#include <cegis/bjc/preprocessing/bjc_preprocessing.h>
#include <cegis/bjc/symex/learn/bjc_symex_learn.h>
#include <cegis/bjc/symex/verify/bjc_symex_verify.h>
#include <cegis/bjc/facade/bjc_runner.h>

namespace
{
typedef messaget::mstreamt mstreamt;
}

int run_bjc(optionst &options, mstreamt &result, const symbol_tablet &st,
    const goto_functionst &gf)
{
  bjc_preprocessingt preproc(options, st, gf);
  const bjc_programt &prog=preproc.get_bjc_program();
  bjc_symex_learnt learn_cfg(prog);
  cegis_symex_learnt<bjc_preprocessingt, bjc_symex_learnt> learn(options,
      preproc, learn_cfg);
  bjc_symex_verifyt oracle_cfg(prog);
  cegis_symex_verifyt<bjc_symex_verifyt> oracle(options, oracle_cfg);
  null_seedt seed;
  const size_t max_size=options.get_unsigned_int_option(CEGIS_MAX_SIZE);
  return run_cegis(learn, oracle, preproc, seed, max_size, result);
}
