#ifndef __CPROVER
#include "../../../src/ansi-c/library/jsa.c"
#endif

int main(void)
{
  abstract_heapt * const heap=__CPROVER_jsa_create_heap();
  const list_t list=__CPROVER_jsa_create_nondet_list(heap);
  const unsigned int limit;
  for (const iterator_t it=__CPROVER_jsa_iterator(heap, list);
      __CPROVER_jsa_hasNext(heap, it);)
  {
    const data_t value=__CPROVER_jsa_next(heap, it);
    if (data <= limit)
    {
      __CPROVER_jsa_remove(heap, it);
    }
  }
}
