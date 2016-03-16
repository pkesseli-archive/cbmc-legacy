/*******************************************************************

 Module: Counterexample-Guided Inductive Synthesis

 Author: Daniel Kroening, kroening@kroening.com
         Pascal Kesseli, pascal.kesseil@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_BJC_PREPROCESSING_H_
#define CEGIS_BJC_PREPROCESSING_H_

#include <cegis/bjc/options/bjc_program.h>

/**
 * @brief
 *
 * @details
 */
class bjc_preprocessingt
{
  const class optionst &options;
  bjc_programt original_program;
  bjc_programt current_program;
public:
  /**
   * @brief
   *
   * @details
   *
   * @param options
   * @param st
   * @param gf
   */
  bjc_preprocessingt(
      const optionst &options,
      const symbol_tablet &st,
      const goto_functionst &gf);

  /**
   * @brief
   *
   * @details
   */
  ~bjc_preprocessingt();

  /**
   * @brief
   *
   * @details
   */
  void operator()();

  /**
   * @brief
   *
   * @details
   *
   * @param max_length
   */
  void operator()(size_t max_length);

  /**
   * @brief
   *
   * @details
   *
   * @return
   */
  size_t get_min_solution_size() const;

  /**
   * @brief
   *
   * @details
   *
   * @return
   */
  const bjc_programt &get_bjc_program() const;
};

#endif /* CEGIS_BJC_PREPROCESSING_H_ */
