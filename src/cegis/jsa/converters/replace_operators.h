/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_JSA_REPLACE_OPERATORS_H_
#define CEGIS_JSA_REPLACE_OPERATORS_H_

#include <goto-programs/goto_program.h>

#include <cegis/jsa/value/pred_ops.h>

// TODO: Need op vals!

/**
 * @brief
 *
 * @details
 *
 * @param pred
 * @param pred_ops
 * @param result_pred_ops
 */
void replace_pred_ops(
    goto_programt::instructionst &pred,
    const pred_op_idst &pred_ops,
    const pred_op_idst &result_pred_ops);

#endif /* CEGIS_JSA_REPLACE_OPERATORS_H_ */
