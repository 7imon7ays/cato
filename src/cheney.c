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

// Copy a val to the toSpace and increment the new space pointer by the size of
// that val (header size + data length). Return the val's new position.
ValRef copyVal(ValRef valRef) {
  size_t numBytes = valSize(valRef);
  memcpy(currentPos, valRef, numBytes);

  currentPos->wasVisited = false;
  valRef->wasVisited = true;

  ValRef newValRef = currentPos;
  valRef->newPosition = newValRef;
  currentPos = nextValRef(currentPos);

  return newValRef;
}

void copyChildren(ValRef parentRef) {
  if (!parentRef->isObject) {
    printf("reached leaf %c\n", DATA(parentRef, char));
    return;
  }

  ValRef* currentChildPtr = ((void*) parentRef) + sizeof(ValueHeader);
  ValRef* terminalPtr = ((void*) parentRef) + valSize(parentRef);

  while (currentChildPtr != terminalPtr) {
    if (!(*currentChildPtr)) {
      // Skip pointer to null
    } else if (!(*currentChildPtr)->wasVisited) {
      // Copy the child and update its reference.
      *currentChildPtr = copyVal(*currentChildPtr);
    } else {
      // Update the reference to the child if it was moved.
      *currentChildPtr = (*currentChildPtr)->newPosition;
    }

    currentChildPtr++;
  }
}

void initCheneyCollect() {
  toSpace = malloc(HEAP_SIZE);
  fromSpace = malloc(HEAP_SIZE);
  currentPos = fromSpace;
}

void cheneyCollect(ValRef rootSet[], int length) {
  // Reset current position to the start of toSpace; increment it as values are
  // copied over.
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
  fromSpace = temp;
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

