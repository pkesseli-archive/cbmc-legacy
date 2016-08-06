#include <algorithm>

#include <cegis/jsa/converters/counterexample.h>

namespace
{
bool is_heap(const jsa_counterexamplet::value_type &assignment)
{
  // TODO: Implement
  return false;
}
}

size_t count_heaps(const jsa_counterexamplet &ce)
{
  return std::count_if(ce.begin(), ce.end(), is_heap);
}

void retrieve_heaps(const jsa_counterexamplet &counterexample,
    __CPROVER_jsa_abstract_heapt *heaps)
{
  // TODO: Implement
}

namespace
{
bool is_word(const jsa_counterexamplet::value_type &assignment)
{
  // TODO: Implement
  return false;
}
}

size_t count_words(const jsa_counterexamplet &ce)
{
  return std::count_if(ce.begin(), ce.end(), is_word);
}

void retrieve_words(const jsa_counterexamplet &counterexample,
    __CPROVER_jsa_word_t *words)
{
  // TODO: Implement
}
