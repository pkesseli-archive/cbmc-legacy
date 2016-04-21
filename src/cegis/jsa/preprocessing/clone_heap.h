/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_JSA_CLONE_HEAP_H_
#define CEGIS_JSA_CLONE_HEAP_H_

/**
 * @brief
 *
 * @details
 *
 * @param gf
 * @return
 */
const class symbol_exprt &get_user_heap_variable(const class goto_functionst &gf);

/**
 * @brief
 *
 * @details
 *
 * @param st
 * @return
 */
symbol_exprt get_cloned_heap_variable(const class symbol_tablet &st);

/**
 * @brief
 *
 * @details
 *
 * @param prog
 */
void clone_heap(class jsa_programt &prog);

#endif /* CEGIS_JSA_CLONE_HEAP_H_ */
