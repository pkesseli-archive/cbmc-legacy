/*******************************************************************

Module: Counterexample-Guided Inductive Synthesis

Author: Daniel Kroening, kroening@kroening.com
        Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_RANDOM_JSA_CROSS_H_
#define CEGIS_RANDOM_JSA_CROSS_H_

#include <deque>

#include <cegis/jsa/value/jsa_genetic_solution.h>

/**
 * @brief
 *
 * @details
 */
class random_jsa_crosst
{
public:
  typedef jsa_populationt populationt;
  typedef std::deque<populationt::iterator> individualst;

  /**
   * @brief
   *
   * @details
   *
   * @param parents
   * @param children
   */
  void operator()(
      const individualst &parents,
      const individualst &children) const;
};

#endif /* CEGIS_RANDOM_JSA_CROSS_H_ */
