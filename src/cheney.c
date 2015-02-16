#include "cheney.h"
#include "vertex.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define HEAP_SIZE 8000000

// Copy the root val to the new space and
// increment the new space pointer by the
// size of the root val (header size + data length)
void copyValAndIncrementFreeSpace(ValRef valRef, ValRef* newValSpacePtr) {
  size_t numBytes = valSize(valRef);

  memcpy(*newValSpacePtr, valRef, numBytes);
  *newValSpacePtr = nextValRef(*newValSpacePtr);
}

void copyChildren(ValRef parentRef, ValRef* newValSpacePtr) {
  if (!parentRef->isObject) {
    printf("reached leaf %c\n", DATA(parentRef, char));
    return;
  }

  ValRef* currentChild = ((void*) parentRef) + sizeof(ValueHeader);
  ValRef* terminalPtr = ((void*) parentRef) + valSize(parentRef);

  while (currentChild != terminalPtr) {
    if (*currentChild) {
      copyValAndIncrementFreeSpace(*currentChild, newValSpacePtr);
    } else {
      // Skip null children
    }

    currentChild++;
  }
}

// Cheney Collect:
// Allocate a new heap. Copy into it the root
// set of objects, along with any objects they
// refer to directly or indirectly
void cheneyCollect(ValRef rootSet[], int length) {
  assert(length == 1);
  // Allocate the new arena and
  // keep a pointer to its next
  // available space
  ValRef newValSpace = malloc(HEAP_SIZE);
  ValRef currentValRef = (ValRef) newValSpace;

  ValRef root = rootSet[0];
  copyValAndIncrementFreeSpace(root, &newValSpace);

  while (currentValRef != newValSpace) {
    copyChildren(currentValRef, &newValSpace);
    currentValRef = nextValRef(currentValRef);
  }
}

