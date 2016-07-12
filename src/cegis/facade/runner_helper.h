/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_FACADE_RUNNER_HELPER_H_
#define CEGIS_FACADE_RUNNER_HELPER_H_

#include <util/message.h>

/**
 * @brief
 *
 * @details
 *
 * @param os
 * @param opt
 * @paral learn
 * @param verify
 * @param preproc
 */
template<class learnt, class verifyt, class preproct>
int run_cegis_with_statistics_wrapper(
    messaget::mstreamt &os,
    const optionst &opt,
    learnt &learn,
    verifyt &verify,
    preproct &preproc);

#include "runner_helper.inc"

#endif /* CEGIS_FACADE_RUNNER_HELPER_H_ */
