#include <stdlib.h>
#include "value.h"

ValueHeader* makeValue(bool isObject, size_t length) {
  ValueHeader* valuePtr = malloc(sizeof(ValueHeader) + length);
  valuePtr->isObject = isObject;
  valuePtr->length = length;

  return valuePtr;
};

