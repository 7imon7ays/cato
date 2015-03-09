#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cheney.h"
#include "value.h"

ValueRef makeValue(bool isObject, size_t length) {
  // Round up the length to multiple of ValueHeader's alignment
  // requirement i.e. 8
  size_t alignmentReq = __alignof(ValueHeader);
  length = ((length + alignmentReq - 1) / alignmentReq) * alignmentReq;

  ValueRef valRef = cheneyMalloc(sizeof(ValueHeader) + length);
  valRef->isObject = isObject;
  valRef->length = length;
  valRef->wasVisited = false;

  return valRef;
}

ValRef forwardingPointer(ValRef valRef) {
  return (valRef->wasVisited ? DATA(valRef, ValRef) : NULL);
}

void setForwardingPointer(ValRef valRef, ValRef newRef) {
  assert(!valRef->wasVisited);
  valRef->wasVisited = true;
  DATA(valRef, ValRef) = newRef;
}

size_t valSize(ValRef valRef) {
  return sizeof(ValueHeader) + valRef->length;
}

ValRef nextValRef(ValRef valRef) {
  return ((ValRef) ((void *) valRef) + valSize(valRef));
}
