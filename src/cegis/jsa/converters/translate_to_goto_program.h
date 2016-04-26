/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_JSA_TRANSLATE_TO_GOTO_PROGRAM_H_
#define CEGIS_JSA_TRANSLATE_TO_GOTO_PROGRAM_H_

#include <goto-programs/goto_program.h>
#include <cegis/jsa/value/jsa_genetic_synthesis.h>
#include <cegis/jsa/value/pred_ops.h>

/**
 * @brief
 *
 * @details
 *
 * @param prog
 * @return
 */
goto_programt::instructionst convert(
    const class jsa_programt &prog,
    const pred_op_idst &pred_ops,
    const pred_op_idst &result_pred_ops,
    const std::vector<__CPROVER_jsa_pred_instructiont> &solution);

#endif /* CEGIS_JSA_TRANSLATE_TO_GOTO_PROGRAM_H_ */
