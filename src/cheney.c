#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "cheney.h"
#include "vertex.h"

#define HEAP_SIZE 8000000

ValRef toSpace = 0;
ValRef fromSpace = 0;
ValRef currentPos = 0;

// Copy a val to the toSpace and increment the new space pointer by
// the size of that val (header size + data length). Return the val's
// new position.
ValRef copyVal(ValRef valRef) {
  size_t numBytes = valSize(valRef);
  ValRef newValRef = currentPos;
  memcpy(newValRef, valRef, numBytes);
  currentPos = nextValRef(newValRef);

  newValRef->wasVisited = false;
  valRef->wasVisited = true;

  return newValRef;
}

void copyChildren(ValRef parentRef) {
  if (!parentRef->isObject) {
    printf("reached leaf %c\n", DATA(parentRef, char));
    return;
  }

  ValRef* childRefs = ((void*) parentRef) + sizeof(ValueHeader);
  int numChildren = parentRef->length / sizeof(ValRef);

  for (int i = 0; i < numChildren; i++) {
    if (!childRefs[i]) {
      // Skip null reference.
    } else if ((childRefs[i])->wasVisited) {
      // Child was already moved. Update the reference with the
      // forwarding pointer left behind.
      childRefs[i] = (childRefs[i])->newPosition;
    } else {
      // Copy the child and update its reference.
      childRefs[i] = copyVal(childRefs[i]);
    }
  }
}

void initCheneyCollect() {
  toSpace = malloc(HEAP_SIZE);
  fromSpace = malloc(HEAP_SIZE);
  currentPos = fromSpace;
}

void cheneyCollect(ValRef rootSet[], int length) {
  // Reset current position to the start of toSpace; increment it as
  // values are copied over.
  currentPos = toSpace;
  ValRef currentValRef = currentPos;

  for (int i = 0; i < length; i++) {
    rootSet[i] = copyVal(rootSet[i]);
  }

  while (currentValRef != currentPos) {
    copyChildren(currentValRef);
    currentValRef = nextValRef(currentValRef);
  }

  ValRef temp = toSpace;
  toSpace = fromSpace;
  fromSpace = toSpace;
}

ValRef cheneyMalloc(size_t size) {
  void* newBufferPosition = ((void *) currentPos) + size;
  void* heapLimit = ((void *) fromSpace) + HEAP_SIZE;
  // Exit for now when fromSpace runs out.
  if (newBufferPosition > heapLimit) {
    exit(1);
  }

  ValRef valRef = currentPos;
  currentPos = ((void *) currentPos) + size;

  return valRef;
}
