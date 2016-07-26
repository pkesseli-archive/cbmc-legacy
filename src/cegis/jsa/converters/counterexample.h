/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_JSA_CONVERT_COUNTEREXAMPLE_H_
#define CEGIS_JSA_CONVERT_COUNTEREXAMPLE_H_

#include <cegis/jsa/value/jsa_counterexample.h>
#include <cegis/jsa/value/jsa_genetic_counterexample.h>

// TODO: Extract CE from trace

/**
 * @brief
 *
 * @details
 *
 * @param ce
 *
 * @return
 */
jsa_genetic_counterexamplet convert(
    const jsa_counterexamplet &ce);

/**
 * @brief
 *
 * @details
 *
 * @param st
 * @param ce
 *
 * @return
 */
jsa_counterexamplet convert(
    const class symbol_tablet &st,
    const jsa_genetic_counterexamplet &ce);

#endif /* CEGIS_JSA_CONVERT_COUNTEREXAMPLE_H_ */
