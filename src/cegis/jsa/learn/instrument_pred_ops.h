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

typedef std::map<size_t, symbol_exprt> pred_op_idst;

/**
 * @brief
 *
 * @details
 *
 * @param prog
 * @param ops
 * @param op_ids
 * @param const_op_ids
 */
void instrument_pred_ops(
    class jsa_programt &prog,
    const goto_programt::targetst &ops,
    pred_op_idst &op_ids,
    pred_op_idst &const_op_ids);

#endif /* CEGIS_JSA_INSTRUMENT_PRED_OPS_H_ */
