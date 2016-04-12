#include <util/options.h>

#include <cegis/facade/cegis.h>
#include <cegis/options/parameters.h>
#include <cegis/seed/null_seed.h>

#include <cegis/jsa/preprocessing/jsa_preprocessing.h>
#include <cegis/jsa/facade/jsa_runner.h>

namespace
{
typedef messaget::mstreamt mstreamt;
}

int run_jsa(optionst &options, mstreamt &result, const symbol_tablet &st,
    const goto_functionst &gf)
{
  jsa_preprocessingt preproc(options, st, gf);
  const size_t max_sz=options.get_unsigned_int_option(CEGIS_MAX_SIZE);
  const null_seedt seed;
  // XXX: Debug
  preproc();
  preproc(1u);
  // XXX: Debug
  //return run_cegis(learn, oracle, preproc, seed, max_sz, result);
  return 10;
}
