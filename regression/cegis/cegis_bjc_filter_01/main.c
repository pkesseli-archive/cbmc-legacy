#include "bjc.h"

int main(void)
{
  abstract_heapt __CPROVER_h;
  abstract_heapt * const __CPROVER_heap=&__CPROVER_h;
  const ptr_t __CPROVER_list=__CPROVER_bjc_nondet_list(__CPROVER_heap);
  const ptr_t __CPROVER_list_copy=__CPROVER_bjc_clone(__CPROVER_heap, __CPROVER_list);
  const unsigned int limit;

  const ptr_t __CPROVER_other_it=__CPROVER_bjc_iterator(__CPROVER_heap, __CPROVER_list);
  __CPROVER_assert(0 == 1, "__CPROVER_bjc_iterator");
  const _Bool __CPROVER_has_next=__CPROVER_bjc_hasNext(__CPROVER_heap, __CPROVER_other_it);
  __CPROVER_assert(0 == 1, "__CPROVER_bjc_hasNext");
  for (const ptr_t __CPROVER_it=__CPROVER_bjc_iterator(__CPROVER_heap, __CPROVER_list); __CPROVER_bjc_hasNext(__CPROVER_heap, __CPROVER_it);)
  {
    __CPROVER_assert(0 == 1, "__CPROVER_bjc_iterator");
    const data_t __CPROVER_element=__CPROVER_bjc_next(__CPROVER_heap, __CPROVER_it);
    __CPROVER_assert(0 == 1, "__CPROVER_bjc_next");
    if (__CPROVER_element <= limit)
      __CPROVER_bjc_it_remove(__CPROVER_heap, __CPROVER_it);
  }
  return 0;
}
