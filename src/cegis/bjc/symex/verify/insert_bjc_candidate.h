/*******************************************************************

 Module: Counterexample-Guided Inductive Synthesis

 Author: Daniel Kroening, kroening@kroening.com
         Pascal Kesseli, pascal.kesseil@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_INSERT_BJC_CANDIDATE_H_
#define CEGIS_INSERT_BJC_CANDIDATE_H_

#include <util/std_expr.h>

typedef array_exprt candidatet;

/**
 * @brief
 *
 * @details
 *
 * @param prog
 * @param candidate
 */
void insert_bjc_candidate(class bjc_programt &prog,
    const candidatet &candidate);

#endif /* CEGIS_INSERT_BJC_CANDIDATE_H_ */
