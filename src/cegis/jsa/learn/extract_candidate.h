/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_JSA_EXTRACT_CANDIDATE_H_
#define CEGIS_JSA_EXTRACT_CANDIDATE_H_

#include <cegis/jsa/value/jsa_solution.h>
#include <cegis/jsa/learn/instrument_pred_ops.h>

/**
 * @brief
 *
 * @details
 *
 * @param solution
 * @param trace
 * @param max_solution_size
 * @param const_pred_ops
 * @param pred_ops
 */
void extract_jsa_candidate(
    jsa_solutiont &solution,
    const class goto_tracet &trace,
    const size_t max_solution_size,
    const pred_op_idst &const_pred_ops,
    const pred_op_idst &pred_ops);

#endif /* CEGIS_JSA_EXTRACT_CANDIDATE_H_ */
