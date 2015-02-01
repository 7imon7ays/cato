#include "../src/value.h"
#include <assert.h>

int main() {

  Value aVal;
  Value bVal;
  Value sumVal;
  makeValue(&aVal, 0, sizeof(int));
  makeValue(&bVal, 0, sizeof(int));
  makeValue(&sumVal, 0, sizeof(int));

  *((int *) aVal.dataPtr) = 2;
  *((int *) bVal.dataPtr) = 3;
  *((int *) sumVal.dataPtr) = *((int *) aVal.dataPtr) + *((int *) bVal.dataPtr);


  assert(*((int *) sumVal.dataPtr) == 5);
  return 0;
}

