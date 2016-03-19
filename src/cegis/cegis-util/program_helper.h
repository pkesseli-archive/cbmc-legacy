/*******************************************************************

 Module: Counterexample-Guided Inductive Synthesis

 Author: Daniel Kroening, kroening@kroening.com
         Pascal Kesseli, pascal.kesseil@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_PROGRAM_HELPER_H_
#define CEGIS_PROGRAM_HELPER_H_

#include <goto-programs/goto_program.h>

/**
 * @brief
 *
 * @details
 *
 * @param gf
 *
 * @return
 */
class goto_programt &get_entry_body(class goto_functionst &gf);

/**
 * @brief
 *
 * @details
 *
 * @param gf
 *
 * @return
 */
const goto_programt &get_entry_body(const goto_functionst &gf);

/**
 * @brief
 *
 * @details
 *
 * @param target
 * @param end
 *
 * @return
 */
bool is_nondet(
    const goto_programt::targett &target,
    const goto_programt::targett &end);

/**
 * @brief
 *
 * @details
 *
 * @param body
 * @return
 */
goto_programt::targetst find_nondet_instructions(goto_programt &body);

/**
 * @brief
 *
 * @details
 *
 * @param instr
 *
 * @return
 */
const irep_idt &get_affected_variable(const goto_programt::instructiont &instr);


/**
 * @brief
 *
 * @details
 *
 * @param name
 * @param type
 *
 * @return
 */
bool is_global_const(const irep_idt &name, const typet &type);


/**
 * @brief
 *
 * @details
 *
 * @param body
 * @param from
 * @param to
 */
void move_labels(goto_programt &body, const goto_programt::targett &from,
    const goto_programt::targett &to);

#endif /* CEGIS_PROGRAM_HELPER_H_ */
