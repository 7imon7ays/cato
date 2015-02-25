#include "../src/value.h"
#include <assert.h>

int main() {
  ValRef twoVal = PRIM_VAL(int, 2);
  ValRef threeVal = PRIM_VAL(int, 3);
  ValRef sumVal = PRIM_VAL(int, 0);

  DATA(sumVal, int) = DATA(twoVal, int) + DATA(threeVal, int);

  assert(DATA(sumVal, int) == 5);
  return 0;
}

