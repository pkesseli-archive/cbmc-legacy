#include <cstdlib>

#include <cegis/jsa/options/jsa_program_info.h>
#include <cegis/jsa/genetic/jsa_random.h>

jsa_randomt::jsa_randomt(const symbol_tablet &st,
    std::function<size_t()> pred_ops_count,
    std::function<size_t()> const_pred_ops_count) :
    st(st), pred_ops_count(pred_ops_count), const_pred_ops_count(
        const_pred_ops_count)
{
}

void jsa_randomt::havoc(jsa_genetic_solutiont &individual) const
{
  individual.fitness=0;
  havoc(individual.invariant);
  havoc(individual.predicates);
  havoc(individual.query);
}

namespace
{
template<class containert>
void havoc_size(containert &container, const size_t max_size)
{
  container.resize(rand() % (max_size + 1));
}
}

void jsa_randomt::havoc(jsa_genetic_solutiont::predicatest &predicates) const
{
  predicates.resize(get_num_jsa_preds(st));
  for (jsa_genetic_solutiont::predicatet &predicate : predicates)
    havoc(predicate);
}

void jsa_randomt::havoc(jsa_genetic_solutiont::predicatet &predicate) const
{
  havoc_size(predicate, get_max_pred_size(st));
  for (jsa_genetic_solutiont::predicatet::value_type &instr : predicate)
    havoc(instr);
}

void jsa_randomt::havoc(
    jsa_genetic_solutiont::predicatet::value_type &instr) const
{
  instr.opcode=rand() % get_pred_instruction_set_size();
  instr.op0=rand() % const_pred_ops_count();
  instr.op1=rand() % const_pred_ops_count();
  instr.result_op=rand() % pred_ops_count();
}

void jsa_randomt::havoc(jsa_genetic_solutiont::invariantt &invariant) const
{
  // TODO: Implement!
}

void jsa_randomt::havoc(
    jsa_genetic_solutiont::invariantt::value_type &instr) const
{
  // TODO: Implement!
}

void jsa_randomt::havoc(jsa_genetic_solutiont::queryt &query) const
{
  // TODO: Implement!
}

void jsa_randomt::havoc(jsa_genetic_solutiont::queryt::value_type &instr) const
{
// TODO: Implement!
}

unsigned int jsa_randomt::rand() const
{
  return ::rand();
}
