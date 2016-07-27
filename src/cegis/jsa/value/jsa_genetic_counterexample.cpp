#include <cegis/jsa/value/jsa_genetic_counterexample.h>

bool jsa_genetic_counterexamplet::operator==(
    const jsa_genetic_counterexamplet &other)
{
  /*return init_org == other.init_org && inductive_org == other.inductive_org
      && inductive_body_result == other.inductive_body_result
      && assignments_per_program_location
          == other.assignments_per_program_location;*/
  return false;
}
