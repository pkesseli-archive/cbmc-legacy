/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#include <util/source_location.h>

#ifndef CEGIS_JSA_META_DATA_H_
#define CEGIS_JSA_META_DATA_H_

#define JSA_MODULE "<builtin-library-jsa>"
#define JSA_BASE_CASE "__CPROVER_jsa_base_case"
#define JSA_IND_ASSUME "__CPROVER_jsa_inductive_assume"
#define JSA_IND_STEP "__CPROVER_jsa_inductive_step"
#define JSA_PROP_ENTAIL "__CPROVER_jsa_property_entailment"

/**
 * @brief
 *
 * @details
 *
 * @return
 */
source_locationt jsa_builtin_source_location();

#endif /* CEGIS_JSA_META_DATA_H_ */
