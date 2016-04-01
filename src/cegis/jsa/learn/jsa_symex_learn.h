/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseil@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_JSA_SYMEX_LEARN_H_
#define CEGIS_JSA_SYMEX_LEARN_H_

#include <deque>
#include <util/message.h>
#include <cegis/jsa/options/jsa_program.h>

/**
 * @brief
 *
 * @details
 */
class jsa_symex_learnt
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
  jsa_symex_learnt(const jsa_programt &program);

  /**
   * @brief
   *
   * @details
   */
  ~jsa_symex_learnt();

  /**
   * @brief
   *
   * @details
   *
   * @param counterexamples
   * @param max_solution_size
   */
  void process(const counterexamplest &counterexamples,
      size_t max_solution_size);

  /**
   * @brief Process the goto program using template data.
   *
   * @details Creates template counterexamples and processes the goto
   * program with them. This is useful for GA source code generation.
   *
   * @param max_solution_size
   */
  void process(size_t max_solution_size);

  /**
   * @brief
   *
   * @details
   *
   * @param word_width_in_bits
   */
  void set_word_width(size_t word_width_in_bits);

  /**
   * @brief
   *
   * @details
   *
   * @param current_candidate
   * @param trace
   * @param max_solution_size
   */
  void convert(candidatet &current_candidate,
      const class goto_tracet &trace,
      size_t max_solution_size);

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
   * @param os
   * @param candidate
   */
  void show_candidate(messaget::mstreamt &os,
      const candidatet &candidate);
};

#endif /* CEGIS_JSA_SYMEX_LEARN_H_ */
