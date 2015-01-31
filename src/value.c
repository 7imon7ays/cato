#include <stdlib.h>
#include "value.h"

void makeValue(Value* valuePtr, bool isObject, size_t length) {
  valuePtr->isObject = isObject;
  valuePtr->length = length;
  valuePtr->dataPtr = malloc(length);
};

