#include <goto-programs/goto_trace.h>

#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/verify/extract_counterexample.h>

void extract(const jsa_programt &prog, jsa_counterexamplet &ce,
    const goto_tracet &trace)
{
  assert(!prog.counterexample_locations.empty());
  assert(false);
}
