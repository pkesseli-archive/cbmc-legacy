#include <cegis/invariant/util/copy_instructions.h>
#include <cegis/jsa/value/jsa_solution.h>

jsa_solutiont::jsa_solutiont() :
    max_size(0), num_pred_ops(0)
{
}

namespace
{
jsa_solutiont &copy_instrs(jsa_solutiont &lhs, const jsa_solutiont &rhs)
{
  lhs.predicates.resize(rhs.predicates.size());
  for (size_t i=0; i < lhs.predicates.size(); ++i)
    copy_instructions(lhs.predicates[i], rhs.predicates[i]);
  copy_instructions(lhs.query, rhs.query);
  copy_instructions(lhs.invariant, rhs.invariant);
}
}

jsa_solutiont::jsa_solutiont(const jsa_solutiont &other) :
    max_size(other.max_size), num_pred_ops(other.num_pred_ops)
{
  copy_instrs(*this, other);
}

jsa_solutiont &jsa_solutiont::operator =(const jsa_solutiont &other)
{
  max_size=other.max_size;
  num_pred_ops=other.num_pred_ops;
  return copy_instrs(*this, other);
}
