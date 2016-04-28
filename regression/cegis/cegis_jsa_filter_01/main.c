#ifdef __CPROVER
#define __CPROVER_JSA_MAX_CONCRETE_NODES 1u
#define __CPROVER_JSA_MAX_ABSTRACT_NODES 0u
#define __CPROVER_JSA_MAX_ITERATORS 1u
#define __CPROVER_JSA_MAX_LISTS 1u

#define __CPROVER_JSA_MAX_QUERY_SIZE 2u
#define __CPROVER_JSA_MAX_PRED_SIZE 1u
#define __CPROVER_JSA_NUM_PRED_OPS 5u
#define __CPROVER_JSA_NUM_PRED_RESULT_OPS 2u
#endif

//#define JSA_SYNTHESIS_H_
#include "../../../src/ansi-c/library/jsa.h"

int main(void)
{
  __CPROVER_jsa_abstract_heapt heap;
  __CPROVER_jsa_assume_valid_heap(&heap);
  const __CPROVER_jsa_list_id_t __CPROVER_jsa_list_list;
  __CPROVER_jsa_assume_valid_list(&heap, __CPROVER_jsa_list_list);
  const __CPROVER_jsa_data_t limit=3;
  for (const __CPROVER_jsa_iterator_id_t __CPROVER_jsa_iterator_it=__CPROVER_jsa_iterator(&heap, __CPROVER_jsa_list_list);
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
