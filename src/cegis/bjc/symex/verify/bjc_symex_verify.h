/*******************************************************************

 Module: Counterexample-Guided Inductive Synthesis

 Author: Daniel Kroening, kroening@kroening.com
         Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_BJC_SYMEX_VERIFY_H_
#define CEGIS_BJC_SYMEX_VERIFY_H_

#include <deque>
#include <util/std_expr.h>
#include <cegis/bjc/options/bjc_program.h>

/**
 * @brief
 *
 * @details
 */
class bjc_symex_verifyt
{
  const bjc_programt &original_program;
  bjc_programt program;
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
   * @details __CPROVER_cegis_instructiont array
   */
  typedef array_exprt candidatet;

  /**
   * @brief
   *
   * @details
   *
   * @param program
   */
  bjc_symex_verifyt(const bjc_programt &program);

  /**
   * @brief
   *
   * @details
   */
  ~bjc_symex_verifyt();

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

#endif /* CEGIS_BJC_SYMEX_VERIFY_H_ */
