/* Oscar: create a lot of garbarge */

#include "../src/value.h"
#include "../src/cheney.h"

int main() {
  for (int i = 0; i < 100000000; i++) {
    pushFrame();
    PRIM_VAR(char, myVar, 'a');
    popFrame();
  }

  return 0;
}

