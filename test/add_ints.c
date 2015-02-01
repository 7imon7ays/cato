#include "../src/value.h"
#include <assert.h>

int main() {
  INIT_PRIM_VAL(aVal, int);
  INIT_PRIM_VAL(bVal, int);
  INIT_PRIM_VAL(sumVal, int);

  DATA(&aVal, int) = 2;
  DATA(&bVal, int) = 3;
  DATA(&sumVal, int) = DATA(&aVal, int) + DATA(&bVal, int);

  assert(DATA(&sumVal, int) == 5);
  return 0;
}

