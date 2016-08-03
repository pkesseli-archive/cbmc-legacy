/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_DYNAMIC_JSA_TEST_RUNNER_H_
#define CEGIS_DYNAMIC_JSA_TEST_RUNNER_H_

#include <functional>

#include <util/tempfile.h>

#include <cegis/jsa/value/jsa_counterexample.h>

/**
 * @brief
 *
 * @details
 */
class dynamic_jsa_test_runnert
{
  typedef void *lib_handlet;
public:
  typedef jsa_counterexamplet counterexamplet;
  typedef class jsa_genetic_solutiont individualt;
private:
  typedef int (*fitness_testert)(const individualt &);
  const std::function<std::string(void)> source_code_provider;
  const temporary_filet shared_library;
  lib_handlet handle;
  fitness_testert fitness_tester;
public:
  /**
   * @brief
   *
   * @details
   *
   * @param source_code_provider
   */
  dynamic_jsa_test_runnert(
      const std::function<std::string(void)> &source_code_provider);

  /**
   * @brief
   *
   * @details
   */
  ~dynamic_jsa_test_runnert();

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
