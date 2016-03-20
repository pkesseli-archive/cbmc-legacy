/*******************************************************************

 Module: Counterexample-Guided Inductive Synthesis

 Author: Daniel Kroening, kroening@kroening.com
         Pascal Kesseli, pascal.kesseil@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_BJC_QUERY_FACTORY_H_
#define CEGIS_BJC_QUERY_FACTORY_H_

#include <cstddef>

/**
 * @brief
 *
 * @details
 *
 * @param prog
 * @param max_size
 * @param num_ops
 */
void add_bjc_query(class bjc_programt &prog, size_t num_vars, size_t num_consts,
    size_t max_sz);

#endif /* CEGIS_BJC_QUERY_FACTORY_H_ */
