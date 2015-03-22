#include "../src/value.h"
#include "../src/cheney.h"
#include <assert.h>

/* Oscar: create a lot of garbage */

int main() {
  pushFrame();
  PRIM_VAR(char, myVar, 'a');

  for (int i = 0; i < 100000000; i++) {
    pushFrame();
    PRIM_VAR(char, myOtherVar, 'b');
    popFrame();
  }

  assert(DATA(myVar, char) == 'a');
  popFrame();

  return 0;
}

