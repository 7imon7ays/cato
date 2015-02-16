#include "cheney.h"
#include "vertex.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define HEAP_SIZE 8000000

size_t valSize(Val v) {
  return sizeof(ValueHeader) + v->length;
}

// Copy the root val to the new space and
// increment the new space pointer by the
// size of the root val (header size + data length)
void copyValAndIncrementFreeSpace(Val val, Val** newValSpacePtr) {
  printf("\n");
  if (val->isObject) {
    printf("val is an object\n");
  } else {
    // Primitive seems to be garbage after the first
    // iteration. Increment must be off.
    printf("val holds the primitive: %c\n", DATA(val, char));
  }

  printf("its length is: %lu\n", val->length);
  size_t numBytes = valSize(val);

  printf("copying val with %lu bytes \n", numBytes);
  // Crashes here because length is garbage
  memcpy(*newValSpacePtr, val, numBytes);
  printf("success\n");

  *newValSpacePtr = ((void*) *newValSpacePtr) + numBytes;
}

void copyChildren(Val parent, Val** newValSpacePtr) {
  if (!parent->isObject) {
    printf("reached leaf %c\n", DATA(parent, char));
    return;
  }

  Val* currentChild = ((void*) parent) + sizeof(ValueHeader);
  Val* terminalPtr = ((void*) parent) + valSize(parent);

  while (currentChild != terminalPtr) {
    // Skip null children
    if (!*currentChild) {
      continue;
    }

    copyValAndIncrementFreeSpace(*currentChild, newValSpacePtr);
    currentChild += sizeof(Val);
  }
}

// Cheney Collect:
// Allocate a new heap. Copy into it the root
// set of objects, along with any objects they
// refer to directly or indirectly
void cheneyCollect(Val rootSet[], int length) {
  assert(length == 1);
  // Allocate the new arena and
  // keep a pointer to its next
  // available space
  Val* newValSpace = malloc(HEAP_SIZE);
  Val* currentValPtr = newValSpace;

  Val root = rootSet[0];
  printf("starting root at address %p\n", root);
  copyValAndIncrementFreeSpace(root, &newValSpace);
  printf("newValSpace after root is %p\n", newValSpace);

  while (currentValPtr != newValSpace) {
    copyChildren(*currentValPtr, &newValSpace);
    currentValPtr++;
  }
}

