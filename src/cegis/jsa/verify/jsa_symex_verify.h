/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_JSA_SYMEX_VERIFY_H_
#define CEGIS_JSA_SYMEX_VERIFY_H_

#include <deque>
#include <cegis/jsa/options/jsa_program.h>
#include <cegis/jsa/value/jsa_solution.h>

/**
 * @brief
 *
 * @details
 */
class jsa_symex_verifyt
{
  const jsa_programt &original_program;
  jsa_programt program;
public:
  /**
   * @brief
   *
   * @details Maps goto program locations to values in order.
   */
  typedef std::map<unsigned, std::vector<exprt> > counterexamplet;
  typedef std::deque<counterexamplet> counterexamplest;
  /**
   * @brief
   *
   * @details Predicates, query-up-to (invariant) and query (postcondition)
   */
  typedef jsa_solutiont candidatet;

  /**
   * @brief
   *
   * @details
   *
   * @param program
   */
  jsa_symex_verifyt(const jsa_programt &program);

  /**
   * @brief
   *
   * @details
   */
  ~jsa_symex_verifyt();

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
  const goto_functionst &get_goto_functions() const;

  /**
   * @brief
   *
   * @details
   *
   * @param counterexamples
   * @param trace
   */
  void convert(counterexamplest &counterexamples,
      const class goto_tracet &trace);
};

#endif /* CEGIS_JSA_SYMEX_VERIFY_H_ */
