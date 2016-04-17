/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_JSA_SOLUTION_H_
#define CEGIS_JSA_SOLUTION_H_

#include <goto-programs/goto_program.h>

/**
 * @brief
 *
 * @details
 */
class jsa_solutiont
{
public:
  typedef std::vector<goto_programt> predicatest;

  /**
   * @brief
   *
   * @details
   */
  predicatest predicates;

  /**
   * @brief
   *
   * @details
   */
  goto_programt invariant;

  /**
   * @brief
   *
   * @details
   */
  goto_programt postcondition;
};

#endif /* CEGIS_JSA_SOLUTION_H_ */
