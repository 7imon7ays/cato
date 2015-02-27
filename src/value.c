#include <stdlib.h>
#include <stdbool.h>
#include "value.h"

ValueHeader* makeValue(bool isObject, size_t length) {
  // Round up the length to multiple of ValueHeader's alignment requirement
  // i.e. 8
  size_t alignmentReq = __alignof(ValueHeader);
  length = ((length + alignmentReq - 1) / alignmentReq) * alignmentReq;

  ValueHeader* valRef = malloc(sizeof(ValueHeader) + length);
  valRef->isObject = isObject;
  valRef->length = length;
  valRef->wasVisited = false;

  return valRef;
};

void* data(ValRef valRef) {
  return ((void *) valRef) + sizeof(ValueHeader);
}

size_t valSize(ValRef valRef) {
  return sizeof(ValueHeader) + valRef->length;
}

ValRef nextValRef(ValRef valRef) {
  return ((ValRef) ((void *) valRef) + valSize(valRef));
}
