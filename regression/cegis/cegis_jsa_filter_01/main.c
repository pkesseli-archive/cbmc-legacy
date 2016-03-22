
#ifndef __CPROVER
#include "../../../src/ansi-c/library/jsa.c"
#endif

int main(void)
{
  abstract_heapt * const heap=__CPROVER_jsa_create_heap();
}
