#include "bjc.h"

int main(void)
{
  abstract_heapt * const heap;
  const ptr_t list=__CPROVER_bjc_new_list(heap);

  for (const ptr_t it=__CPROVER_bjc_iterator(heap, list); __CPROVER_bjc_hasNext(heap, it);)
  {
    const data_t element=__CPROVER_bjc_next(heap, it);
    if (element <= 3)
      __CPROVER_bjc_it_remove(heap, it);
  }
  return 0;
}
