#include <goto-programs/goto_trace.h>

#include <cegis/instrument/meta_variables.h>
#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/learn/extract_candidate.h>

// XXX: Debug
#include <iostream>
// XXX: Debug

namespace
{
array_exprt find_query(const goto_tracet &trace)
{
  const std::string query_name(get_cegis_meta_name(JSA_QUERY));
  for (const goto_trace_stept &step : trace.steps)
  {
    if (goto_trace_stept::ASSIGNMENT != step.type) continue;
    if (query_name != id2string(step.lhs_object.get_identifier())) continue;
    // XXX: Debug
    const symbol_tablet st;
    const namespacet ns(st);
    step.output(ns, std::cout);
    std::cout << "<value>" << step.full_lhs_value.to_string() << "</value>" << std::endl;
    // XXX: Debug
    return to_array_expr(step.full_lhs_value);
  }
  assert(!"JSA query not found.");
}
}

void extract_jsa_candidate(jsa_solutiont &solution, const goto_tracet &trace,
    const size_t max_solution_size, const pred_op_idst &const_pred_ops,
    const pred_op_idst &pred_ops)
{
  find_query(trace);
}
