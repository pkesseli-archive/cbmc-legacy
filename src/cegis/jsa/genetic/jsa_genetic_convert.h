/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_JSA_GENETIC_CONVERT_H_
#define CEGIS_JSA_GENETIC_CONVERT_H_

/**
 * @brief
 *
 * @details
 */
class jsa_genetic_convertt
{
public:
  typedef class jsa_solutiont candidatet;
  typedef class jsa_genetic_solutiont individualt;

  /**
   * @brief
   *
   * @details
   *
   * @param candidate
   * @param individual
   */
  void convert(candidatet &candidate, const individualt &individual) const;
};

#endif /* CEGIS_JSA_GENETIC_CONVERT_H_ */
