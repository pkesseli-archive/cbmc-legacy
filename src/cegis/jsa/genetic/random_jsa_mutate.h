/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_RANDOM_JSA_MUTATE_H_
#define CEGIS_RANDOM_JSA_MUTATE_H_

/**
 * @brief
 *
 * @details
 */
class random_jsa_mutatet
{
public:
  typedef class jsa_genetic_solutiont individualt;

  /**
   * @brief
   *
   * @details
   *
   * @param lhs
   * @param rhs
   */
  void operator()(individualt &lhs, const individualt &rhs) const;

  /**
   * @brief
   *
   * @details
   *
   * @param lhs
   */
  void havoc(individualt &ind) const;

  /**
   * @brief
   *
   * @details
   *
   * @param ind
   */
  void post_process(individualt &ind) const;
};

#endif /* CEGIS_RANDOM_JSA_MUTATE_H_ */
