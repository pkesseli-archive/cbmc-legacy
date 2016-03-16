/*******************************************************************

 Module: Counterexample-Guided Inductive Synthesis

 Author: Daniel Kroening, kroening@kroening.com
         Pascal Kesseli, pascal.kesseil@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_BJC_PROGRAM_H_
#define CEGIS_BJC_PROGRAM_H_

#include <goto-programs/goto_functions.h>

/**
 * @brief
 *
 * @details
 */
class bjc_programt
{
public:
  symbol_tablet st;
  goto_functionst gf;

  goto_programt::targetst ce_targets;
  goto_programt::targett query_decl;

  /**
   * @brief
   *
   * @details
   */
  bjc_programt();

  /**
   * @brief
   *
   * @details
   *
   * @param st
   * @param gf
   */
  bjc_programt(const symbol_tablet &st, const goto_functionst &gf);

  /**
   * @brief
   *
   * @details
   *
   * @param other
   */
  bjc_programt(const bjc_programt &other);

  /**
   * @brief
   *
   * @details
   */
  ~bjc_programt();

  /**
   * @brief
   *
   * @details
   *
   * @param other
   * @return
   */
  bjc_programt &operator=(const bjc_programt &other);
};

#endif /* CEGIS_BJC_PROGRAM_H_ */
