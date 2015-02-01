#include "../src/value.h"
#include <assert.h>

int main() {

  Value aVal;
  Value bVal;
  Value sumVal;
  makeValue(&aVal, 0, sizeof(int));
  makeValue(&bVal, 0, sizeof(int));
  makeValue(&sumVal, 0, sizeof(int));

  DATA(&aVal, int) = 2;
  DATA(&bVal, int) = 3;
  DATA(&sumVal, int) = DATA(&aVal, int) + DATA(&bVal, int);

  assert(DATA(&sumVal, int) == 5);
  return 0;
}

