#include <goto-programs/goto_functions.h>

#include <cegis/jsa/instrument/jsa_meta_data.h>

source_locationt jsa_builtin_source_location()
{
  source_locationt loc;
  loc.set_file(JSA_MODULE);
  loc.set_function(goto_functionst::entry_point());
  return loc;
}
