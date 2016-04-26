#include <cegis/jsa/value/jsa_genetic_solution.h>
#include <cegis/jsa/converters/translate_to_goto_program.h>
#include <cegis/jsa/converters/solution.h>

jsa_solutiont convert(const jsa_genetic_solutiont &solution,
    const jsa_programt &prog, const pred_op_idst &pred_ops,
    const pred_op_idst &result_pred_ops)
{
  for (const jsa_genetic_solutiont::predicatest::value_type &pred : solution.predicates)
    convert(prog, pred_ops, result_pred_ops, pred);
}
