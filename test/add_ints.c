#include "../src/value.h"
#include <assert.h>

int main() {
  INIT_PRIM_VAL(aValPtr, int);
  INIT_PRIM_VAL(bValPtr, int);
  INIT_PRIM_VAL(sumValPtr, int);

  DATA(aValPtr, int) = 2;
  DATA(bValPtr, int) = 3;
  DATA(sumValPtr, int) = DATA(aValPtr, int) + DATA(bValPtr, int);

  assert(DATA(sumValPtr, int) == 5);
  return 0;
}

