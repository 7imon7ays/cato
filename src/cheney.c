#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "cheney.h"
#include "vertex.h"

#define HEAP_SIZE 8000000

// Copy the root val to the new space and increment the new space pointer by
// the size of the root val (header size + data length).
void copyValAndIncrementFreeSpace(ValRef valRef, ValRef* nextEmptyValAddressPtr) {
  size_t numBytes = valSize(valRef);
  memcpy(*nextEmptyValAddressPtr, valRef, numBytes);

  (*nextEmptyValAddressPtr)->wasVisited = false;
  valRef->wasVisited = true;

  *nextEmptyValAddressPtr = nextValRef(*nextEmptyValAddressPtr);
}

void copyChildren(ValRef parentRef, ValRef* nextEmptyValAddressPtr) {
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
      copyValAndIncrementFreeSpace(*currentChild, nextEmptyValAddressPtr);
    } else {
      // Skip null or already-visited children.
    }

    currentChild++;
  }
}

// Cheney Collect:
// Allocate a new heap. Copy into it the root set of objects, along with any
// objects they refer to directly or indirectly.
void cheneyCollect(ValRef rootSet[], int length) {
  assert(length == 1);
  // Allocate the new arena and keep a pointer to its next available space.
  ValRef nextEmptyValAddress = malloc(HEAP_SIZE);
  ValRef currentValRef = nextEmptyValAddress;

  ValRef root = rootSet[0];

  for (int i = 0; i < length; i++) {
    copyValAndIncrementFreeSpace(rootSet[i], &nextEmptyValAddress);
  }

  while (currentValRef != nextEmptyValAddress) {
    copyChildren(currentValRef, &nextEmptyValAddress);
    currentValRef = nextValRef(currentValRef);
  }
}

