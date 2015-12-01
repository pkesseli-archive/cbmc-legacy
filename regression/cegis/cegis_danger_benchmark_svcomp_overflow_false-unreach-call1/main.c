// Adapted version of overflow_true-unreach-call1 in SVCOMP.

int main(void) {
  unsigned int x;

  x = 10;

  while (x >= 10) {
    x += 2;
  }

  __CPROVER_assert(x % 2, "A");
  return 0;
}
