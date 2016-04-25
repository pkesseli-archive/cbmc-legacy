#include <util/bv_arithmetic.h>
#include <goto-programs/goto_trace.h>

#include <cegis/instrument/meta_variables.h>
#include <cegis/jsa/instrument/jsa_meta_data.h>
#include <cegis/jsa/learn/extract_candidate.h>

namespace
{
typedef std::pair<size_t, array_exprt> encoded_programt;
typedef std::vector<encoded_programt> encoded_programst;

inline bool is_integer(const std::string & s)
{
  if (s.empty() || (!isdigit(s[0]) && s[0] != '-' && s[0] != '+')) return false;
  char *p;
  strtol(s.c_str(), &p, 10);
  return *p == 0;
}

bool is_prog_name(const std::string &var_name, const std::string &prefix)
{
  const std::string::size_type prefix_size=prefix.size();
  if (var_name.substr(0, prefix_size) != prefix) return false;
  const std::string suffix(var_name.substr(prefix_size));
  return suffix.empty() || is_integer(suffix);
}

bool find_prog(encoded_programt &result,
    goto_tracet::stepst::const_iterator &first,
    const goto_tracet::stepst::const_iterator &last, const std::string &name)
{
  const goto_tracet::stepst::const_iterator origin(first);
  const std::string prefix(get_cegis_meta_name(name));
  for (; first != last; ++first)
  {
    if (goto_trace_stept::DECL != first->type) continue;
    const std::string &var_name=id2string(first->lhs_object.get_identifier());
    if (!is_prog_name(var_name, prefix)) continue;
    std::string sz_name(var_name);
    sz_name+= JSA_SIZE_SUFFIX;
    goto_tracet::stepst::const_iterator sz;
    for (sz=first; id2string(sz->lhs_object.get_identifier()) != sz_name; --sz)
      assert(sz != origin);
    const bv_arithmetict bv(sz->full_lhs_value);
    result.first=bv.to_integer().to_ulong();
    result.second=to_array_expr(first++->full_lhs_value);
    return true;
  }
  return false;
}
}

void extract_jsa_candidate(jsa_solutiont &solution, const goto_tracet &trace,
    const size_t max_solution_size, const pred_op_idst &const_pred_ops,
    const pred_op_idst &pred_ops)
{
  goto_tracet::stepst::const_iterator first(trace.steps.begin());
  const goto_tracet::stepst::const_iterator last(trace.steps.end());
  encoded_programst predicates;
  goto_tracet::stepst::const_iterator last_pred;
  encoded_programt tmp;
  while (find_prog(tmp, first, last, JSA_PRED_PREFIX))
  {
    predicates.push_back(tmp);
    last_pred=first;
  }
  first=last_pred;
  encoded_programt query;
  assert(find_prog(query, first, last, JSA_QUERY));
  encoded_programt invariant;
  assert(find_prog(invariant, first, last, JSA_INV));
}
