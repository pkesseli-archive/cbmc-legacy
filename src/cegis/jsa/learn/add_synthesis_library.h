/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_JSA_ADD_SYNTHESIS_LIBRARY_H_
#define CEGIS_JSA_ADD_SYNTHESIS_LIBRARY_H_

#include <cstddef>

/**
 * @brief
 *
 * @details
 *
 * @param prog
 * @param max_sz
 * @param num_pred_ops
 */
void add_jsa_synthesis_library(
    class jsa_programt &prog,
    size_t max_sz,
    size_t num_pred_ops);

#endif /* CEGIS_JSA_ADD_SYNTHESIS_LIBRARY_H_ */
