#include "cheney.h"
#include "vertex.h"
#include <string.h>
#include <assert.h>
#include <stdio.h>

#define HEAP_SIZE 8000000

// Copy the root val to the new space and
// increment the new space pointer by the
// size of the root val (header size + data length)
void moveVal(Val val, void** newValSpacePtr) {
  if (val->isObject) {
    printf("val is an object\n");
  } else {
    // Primitive seems to be garbage after the first
    // iteration. Increment must be off.
    printf("val holds the primitive: %c\n", DATA(val, char));
  }

  printf("its length is: %lu\n", val->length);
  int numBytes = sizeof(Val) + val->length;

  printf("copying val with %d bytes \n", numBytes);
  // Crashes here because length is garbage
  memcpy(*newValSpacePtr, val, numBytes);

  *newValSpacePtr += numBytes;
}

void moveChildren(Val parent, void** nextFreeSpacePtr) {
  if (!parent->isObject) {
    printf("reached leaf %c\n", DATA(parent, char));
    return;
  }

  if (parent->length == 0) {
    return;
  }

  void* currentChild = ((void*) parent) + sizeof(Val);
  void* terminalPtr = ((void*) parent) + sizeof(Val) + parent->length;

  while (currentChild != terminalPtr) {
    moveVal(currentChild, nextFreeSpacePtr);
    currentChild += sizeof(Val);
  }
}

// Cheney Collect:
// Allocate a new heap. Copy into it the root
// set of objects, along with any objects they
// refer to directly or indirectly
void cheneyCollect(Val rootSet[], int length) {
  assert(length == 1);
  void* newArena = malloc(HEAP_SIZE);
  void* nextFreeSpace = newArena;

  Val root = rootSet[0];
  moveVal(root, &nextFreeSpace);

  Val currentVal = (Val) newArena;

  while (currentVal != nextFreeSpace) {
    moveChildren(currentVal, &nextFreeSpace);
    currentVal += sizeof(Val) + currentVal->length;
  }
}

