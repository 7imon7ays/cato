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

// Copy the root val to the new space and increment the new space pointer by
// the size of the root val (header size + data length).
void copyVal(ValRef valRef) {
  size_t numBytes = valSize(valRef);
  memcpy(currentPos, valRef, numBytes);

  currentPos->wasVisited = false;
  valRef->wasVisited = true;

  currentPos = nextValRef(currentPos);
}

void copyChildren(ValRef parentRef) {
  if (!parentRef->isObject) {
    printf("reached leaf %c\n", DATA(parentRef, char));
    return;
  }

  ValRef* currentChild = ((void*) parentRef) + sizeof(ValueHeader);
  ValRef* terminalPtr = ((void*) parentRef) + valSize(parentRef);
  bool currentChildExistsAndIsNotVisited;

  while (currentChild != terminalPtr) {
    currentChildExistsAndIsNotVisited = *currentChild && !(*currentChild)->wasVisited;
    if (currentChildExistsAndIsNotVisited) {
      copyVal(*currentChild);
    } else {
      // Skip null or already-visited children.
    }

    currentChild++;
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
    copyVal(rootSet[i]);
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
    // Exit for now
    exit(1);
  }

  ValRef valRef = currentPos;
  currentPos = ((void *) currentPos) + size;

  return valRef;
}

