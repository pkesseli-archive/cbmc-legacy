/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_GENETIC_JSA_RANDOM_H_
#define CEGIS_GENETIC_JSA_RANDOM_H_

/**
 * @brief
 *
 * @details
 */
class jsa_randomt
{
public:
  /**
   * @brief
   *
   * @details
   *
   * @param individual
   */
  void havoc(class jsa_genetic_solutiont &individual) const;
};

#endif /* CEGIS_GENETIC_JSA_RANDOM_H_ */
