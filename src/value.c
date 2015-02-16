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

void* data(ValRef valRef) {
  return ((void *) valRef) + sizeof(ValueHeader);
}

size_t valSize(ValRef v) {
  return sizeof(ValueHeader) + v->length;
}

// Return next available address
// after a value header and its content
ValRef nextValRef(ValRef v) {
  return ((ValRef) ((void *) v) + valSize(v));
}

