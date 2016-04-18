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
  __CPROVER_jsa_abstract_heapt heap;
  __CPROVER_jsa_assume_valid_heap(&heap);
  const __CPROVER_jsa_list_id_t __CPROVER_jsa_list_list=__CPROVER_jsa_create_list(&heap);
  const __CPROVER_jsa_data_t limit;
  for (__CPROVER_jsa_iterator_id_t __CPROVER_jsa_iterator_it=__CPROVER_jsa_iterator(&heap, __CPROVER_jsa_list_list);
      __CPROVER_jsa_hasNext(&heap, __CPROVER_jsa_iterator_it);)
  {
    const __CPROVER_jsa_data_t value=__CPROVER_jsa_next(&heap, __CPROVER_jsa_iterator_it);
    if (value <= limit)
    {
      __CPROVER_jsa_remove(&heap, __CPROVER_jsa_iterator_it);
    }
  }

  return 0;
}
