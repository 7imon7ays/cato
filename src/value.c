#include <stdlib.h>
#include <stdbool.h>
#include "value.h"

ValueHeader* makeValue(bool isObject, size_t length) {
  ValueHeader* valuePtr = malloc(sizeof(ValueHeader) + length);
  valuePtr->isObject = isObject;
  valuePtr->length = length;
  valuePtr->wasVisited = false;

  return valuePtr;
};

