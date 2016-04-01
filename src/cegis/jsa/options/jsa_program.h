/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseil@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_JSA_PROGRAM_H_
#define CEGIS_JSA_PROGRAM_H_

#include <cegis/safety/options/safety_program.h>

class jsa_programt
{
public:
  safety_programt safety;

  /**
   * @brief
   *
   * @details
   */
  jsa_programt();

  /**
   * @brief
   *
   * @details
   *
   * @param other
   */
  jsa_programt(const jsa_programt &other);

  /**
   * @brief
   *
   * @details
   *
   * @param st
   * @param gf
   */
  jsa_programt(const symbol_tablet &st, const goto_functionst &gf);

  /**
   * @brief
   *
   * @details
   */
  ~jsa_programt();

  /**
   * @brief
   *
   * @details
   *
   * @param other
   */
  jsa_programt &operator=(const jsa_programt &other);

  /**
   * @brief
   *
   * @details
   *
   * @return
   */
  symbol_tablet &get_st();

  /**
   * @brief
   *
   * @details
   *
   * @return
   */
  const symbol_tablet &get_st() const;

  /**
   * @brief
   *
   * @details
   *
   * @return
   */
  goto_functionst &get_gf();

  /**
   * @brief
   *
   * @details
   *
   * @return
   */
  const goto_functionst &get_gf() const;
};

#endif /* CEGIS_JSA_PROGRAM_H_ */
