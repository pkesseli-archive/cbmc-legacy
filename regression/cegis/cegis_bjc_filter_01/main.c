#include "bjc.h"

int main(void)
{
  abstract_heapt * const __CPROVER_heap;
  const ptr_t __CPROVER_list=__CPROVER_bjc_new_list(__CPROVER_heap);

  for (const ptr_t __CPROVER_it=__CPROVER_bjc_iterator(__CPROVER_heap, __CPROVER_list); __CPROVER_bjc_hasNext(__CPROVER_heap, __CPROVER_it);)
  {
    const data_t __CPROVER_element=__CPROVER_bjc_next(__CPROVER_heap, __CPROVER_it);
    if (__CPROVER_element <= 3)
      __CPROVER_bjc_it_remove(__CPROVER_heap, __CPROVER_it);
  }
  return 0;
}
