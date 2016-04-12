#ifdef __CPROVER
#define __CPROVER_JSA_MAX_CONCRETE_NODES 1u
#define __CPROVER_JSA_MAX_ABSTRACT_NODES 0u
#define __CPROVER_JSA_MAX_ITERATORS 1u
#define __CPROVER_JSA_MAX_LISTS 1u
#endif

// XXX: Debug
#define JSA_SYNTHESIS_H_
// XXX: Debug

#include "../../../src/ansi-c/library/jsa.c"

int main(void)
{
  abstract_heapt * const heap=__CPROVER_jsa_create_heap();
  const __CPROVER_jsa_list_id_t list=__CPROVER_jsa_create_list(heap);
  const unsigned int limit;
  for (const __CPROVER_jsa_iterator_id_t it=__CPROVER_jsa_iterator(heap, list);
      __CPROVER_jsa_hasNext(heap, it);)
  {
    const __CPROVER_jsa_data_t value=__CPROVER_jsa_next(heap, it);
    if (value <= limit)
    {
      __CPROVER_jsa_remove(heap, it);
    }
  }
  __CPROVER_assert(0 == 1, "");

  return 0;
}
