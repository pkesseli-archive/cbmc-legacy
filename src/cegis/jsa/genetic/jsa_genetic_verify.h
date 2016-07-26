/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_CONVERTING_VERIFY_H_
#define CEGIS_CONVERTING_VERIFY_H_

#include <deque>

#include <util/message.h>

/**
 * @brief
 *
 * @details
 */
class jsa_genetic_verifyt
{
  class jsa_symex_verifyt &verify;
public:
  typedef class jsa_genetic_counterexamplet counterexamplet;
  typedef std::deque<counterexamplet> counterexamplest;
  typedef class jsa_genetic_solutiont candidatet;

  /**
   * @brief
   *
   * @details
   *
   * @param verify
   */
  jsa_genetic_verifyt(jsa_symex_verifyt &verify);


  /**
   * @brief
   *
   * @details
   *
   * @param candidate
   */
  void process(const candidatet &candidate);

  /**
   * @brief
   *
   * @details
   *
   * @return
   */
  const symbol_tablet &get_symbol_table() const;

  /**
   * @brief
   *
   * @details
   *
   * @return
   */
  const class goto_functionst &get_goto_functions() const;

  /**
   * @brief
   *
   * @details
   *
   * @param counterexamples
   * @param trace
   */
  void convert(
      counterexamplest &counterexamples,
      const class goto_tracet &trace);

  /**
   * @brief
   *
   * @details
   *
   * @param os
   * @param counterexample
   */
  void show_counterexample(
      messaget::mstreamt &os,
      const counterexamplet &counterexample) const;
};

#endif /* CEGIS_CONVERTING_VERIFY_H_ */
