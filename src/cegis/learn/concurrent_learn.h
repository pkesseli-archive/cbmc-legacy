/*******************************************************************

 Module: Counterexample-Guided Inductive Synthesis

 Author: Daniel Kroening, kroening@kroening.com
         Pascal Kesseli, pascal.kesseli@cs.ox.ac.uk

\*******************************************************************/

#ifndef CEGIS_CONCURRENT_LEARN_H_
#define CEGIS_CONCURRENT_LEARN_H_

#include <functional>

#include <util/irep.h>

#include <cegis/cegis-util/task_pool.h>

/**
 * @brief
 *
 * @details
 */
template<class learner1t, class learner2t>
class concurrent_learnt
{
public:
  typedef typename learner1t::candidatet candidatet;
  typedef typename learner1t::paragont learner2_candidatet;
  typedef typename learner1t::counterexamplet counterexamplet;
  typedef typename learner1t::counterexamplest counterexamplest;
  typedef std::function<void(irept &, const candidatet &)> learner2_serialisert;
  typedef std::function<void(candidatet &, const irept &)> learner1_deserialisert;
  typedef std::function<void(learner2_candidatet &, const irept &)> learner2_deserialisert;
private:
  learner1t &learner1;
  learner2t &learner2;
  task_poolt task_pool;
  const learner2_serialisert learner2_serialiser;
  const learner1_deserialisert learner1_deserialiser;
  const learner2_deserialisert learner2_deserialiser;
  bool is_decoded_candidate;
  candidatet decoded_candidate;
  size_t num_ces;
  const size_t num_symex_ces;
public:
  /**
   * @brief
   *
   * @details
   *
   * @param learner1
   * @param learner2
   * @param serialiser
   * @param deserialiser
   * @param encoded_deserialiser
   * @param learner1_head_start
   */
  concurrent_learnt(learner1t &learner1, learner2t &learner2,
      learner2_serialisert serialiser, learner1_deserialisert deserialiser,
      learner2_deserialisert encoded_deserialiser, size_t learner1_head_start);

  /**
   * @brief
   *
   * @details
   *
   * @param learner1
   * @param learner2
   * @param serialiser
   * @param learner1_head_start
   */
  template<class serialisert>
  concurrent_learnt(learner1t &learner1, learner2t &learner2,
      const serialisert &serialiser, size_t learner1_head_start);

  /**
   * @brief
   *
   * @details
   */
  ~concurrent_learnt();

  template<class seedt>
  void seed(seedt &seed);

  const candidatet &next_candidate() const;

  template<class itert>
  bool learn(itert first, const itert &last);

  void show_candidate(messaget::mstreamt &os) const;

  void set_solution_size_range(size_t min, size_t max);
};

#include "concurrent_learn.inc"

#endif /* CEGIS_CONCURRENT_LEARN_H_ */
