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
  // XXX: Debug
  preproc();
  preproc(1);
  // XXX: Debug
  return 10;
}
