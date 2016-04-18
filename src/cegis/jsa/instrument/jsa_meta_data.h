/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#include <util/cprover_prefix.h>
#include <util/source_location.h>

#ifndef CEGIS_JSA_META_DATA_H_
#define CEGIS_JSA_META_DATA_H_

#define JSA_MODULE "<builtin-library-jsa>"
#define JSA_PREFIX CPROVER_PREFIX "jsa_"
#define JSA_BASE_CASE JSA_PREFIX "base_case"
#define JSA_IND_ASSUME JSA_PREFIX "inductive_assume"
#define JSA_IND_STEP JSA_PREFIX "inductive_step"
#define JSA_PROP_ENTAIL JSA_PREFIX "property_entailment"
#define JSA_TMP_PREFIX JSA_PREFIX "tmp_"

/**
 * @brief
 *
 * @details
 *
 * @param type
 *
 * @return
 */
bool is_jsa_heap(const typet &type);

/**
 * @brief
 *
 * @details
 *
 * @param id
 *
 * @return
 */
bool is_jsa_iterator(const irep_idt &id);

/**
 * @brief
 *
 * @details
 *
 * @param id
 *
 * @return
 */
bool is_jsa_list(const irep_idt &id);

/**
 * @brief
 *
 * @details
 *
 * @return
 */
source_locationt jsa_builtin_source_location();

#endif /* CEGIS_JSA_META_DATA_H_ */
