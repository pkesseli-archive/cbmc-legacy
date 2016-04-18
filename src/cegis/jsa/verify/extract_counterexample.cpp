#include <util/expr_util.h>

#include <goto-programs/goto_trace.h>

#include <cegis/cegis-util/program_helper.h>
#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/verify/extract_counterexample.h>

namespace
{
const typet &get_type(const symbol_tablet &st,
    const goto_programt::targett &pos)
{
  return st.lookup(get_affected_variable(*pos)).type;
}
}

void extract(const jsa_programt &prog, jsa_counterexamplet &ce,
    const goto_tracet &trace)
{
  const symbol_tablet &st=prog.st;
  const goto_programt::targetst &ce_locs=prog.counterexample_locations;
  const goto_tracet::stepst &steps=trace.steps;
  goto_tracet::stepst::const_iterator step=steps.begin();
  goto_programt::targetst::const_iterator ce_loc=ce_locs.begin();
  while (step != steps.end() && ce_loc != ce_locs.end())
  {
    const goto_trace_stept &trace_val=*step;
    const goto_programt::targett &ce_val=*ce_loc;
    const unsigned lhs_loc=trace_val.pc->location_number;
    const unsigned rhs_loc=ce_val->location_number;
    if (lhs_loc == rhs_loc)
    {
      ce.insert(std::make_pair(rhs_loc, trace_val.full_lhs_value));
      ++step;
      ++ce_loc;
    } else if (lhs_loc < rhs_loc) ++step;
    else
    {
      ce.insert(std::make_pair(rhs_loc, gen_zero(get_type(st, ce_val))));
      ++ce_loc;
    }
  }
  assert(ce.size() == prog.counterexample_locations.size());
}
