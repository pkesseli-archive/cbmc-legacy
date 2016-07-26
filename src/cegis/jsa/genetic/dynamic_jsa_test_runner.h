/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_DYNAMIC_JSA_TEST_RUNNER_H_
#define CEGIS_DYNAMIC_JSA_TEST_RUNNER_H_

#include <functional>

#include <cegis/jsa/value/jsa_genetic_counterexample.h>

/**
 * @brief
 *
 * @details
 */
class dynamic_jsa_test_runnert
{
public:
  typedef jsa_genetic_counterexamplet counterexamplet;
  typedef class jsa_genetic_solutiont individualt;

  /**
   * @brief
   *
   * @details
   *
   * @param individual
   * @param counterexample
   * @param on_complete
   */
  void run_test(
      individualt &individual,
      const counterexamplet &counterexample,
      std::function<void(bool)> on_complete);

  /**
   * @brief
   *
   * @details
   */
  void join();
};

#endif /* CEGIS_DYNAMIC_JSA_TEST_RUNNER_H_ */
