int main(void)
{
  int x;
  if (x > 2)
    x = 2;
  0 == 0;

  while (x < 2)
    ++x;
  __CPROVER_assert(x == 2, "A");
  return 0;
}
