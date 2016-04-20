#ifndef CEGIS_JSA_INSTRUMENT_PRED_OPS_H_
#define CEGIS_JSA_INSTRUMENT_PRED_OPS_H_

#include <goto-programs/goto_program.h>

/**
 * @brief
 *
 * @details
 *
 * @param prog
 * @return
 */
goto_programt::targetst collect_pred_ops(class jsa_programt &prog);

/**
 * @brief
 *
 * @details
 *
 * @param prog
 * @param ops
 */
std::map<size_t, symbol_exprt> instrument_pred_ops(class jsa_programt &prog,
    const goto_programt::targetst &ops);

#endif /* CEGIS_JSA_INSTRUMENT_PRED_OPS_H_ */
