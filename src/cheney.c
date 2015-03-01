#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "cheney.h"
#include "vertex.h"

#define HEAP_SIZE 8000000
#define STACK_SIZE 1000000

ValRef toSpace = NULL;
ValRef fromSpace = NULL;
ValRef currentHeapPos = NULL;
void* rootSetStack = NULL;
void* currentStackPos = NULL;
int currentFrameSize = 0;

// Copy a val to the toSpace and increment the new space pointer by the size of
// that val (header size + data length). Return the val's new position.
ValRef copyVal(ValRef valRef) {
  size_t numBytes = valSize(valRef);
  memcpy(currentHeapPos, valRef, numBytes);

  ValRef newValRef = currentHeapPos;
  setForwardingPointer(valRef, newValRef);
  currentHeapPos = nextValRef(currentHeapPos);

  return newValRef;
}

void copyChildren(ValRef parentRef) {
  if (!parentRef->isObject) {
    printf("reached leaf %c\n", DATA(parentRef, char));
    return;
  }

  // Point to the value's data and iterate over it as an array of ValRefs.
  // Its length is the size of the parent's data divided by size of a ValRef.
  ValRef* children = &(DATA(parentRef, ValRef));
  int numChildren = parentRef->length / sizeof(ValRef);

  for (int i = 0; i < numChildren; i++) {
    if (!(children[i])) {
      // Skip pointer to null
    } else if (!(children[i])->wasVisited) {
      // Copy the child and update its reference.
      children[i] = copyVal(children[i]);
    } else {
      // Update the reference to the child if it was moved.
      children[i] = forwardingPointer(children[i]);
    }
  }
}

void initCheneyCollect() {
  toSpace = malloc(HEAP_SIZE);
  fromSpace = malloc(HEAP_SIZE);
  rootSetStack = malloc(STACK_SIZE);
  currentHeapPos = fromSpace;
  currentStackPos = rootSetStack;
}

void cheneyCollect(ValRef rootSet[], int length) {
  // Reset current position to the start of toSpace; increment it as values are
  // copied over.
  currentHeapPos = toSpace;
  ValRef currentValRef = currentHeapPos;

  for (int i = 0; i < length; i++) {
    rootSet[i] = copyVal(rootSet[i]);
  }

  while (currentValRef != currentHeapPos) {
    copyChildren(currentValRef);
    currentValRef = nextValRef(currentValRef);
  }

  ValRef temp = toSpace;
  toSpace = fromSpace;
  fromSpace = temp;
}

void pushFrame() {
  *((int *) currentStackPos) = currentFrameSize;
  currentStackPos += sizeof(int);
  currentFrameSize = 0;
}

void pushValRef(ValRef* valRefPtr) {
  *((ValRef **) currentStackPos) = valRefPtr;
  currentStackPos += sizeof(ValRef *);
  currentFrameSize++;
}

void popFrame() {
  currentStackPos -= currentFrameSize * sizeof(ValRef *);
  currentStackPos -= sizeof(int);
  currentFrameSize = *((int *) currentStackPos);
}

ValRef cheneyMalloc(size_t size) {
  void* newBufferPosition = ((void *) currentHeapPos) + size;
  void* heapLimit = ((void *) fromSpace) + HEAP_SIZE;
  // Exit for now when fromSpace runs out.
  if (newBufferPosition > heapLimit) {
    exit(1);
  }

  ValRef valRef = currentHeapPos;
  currentHeapPos = ((void *) currentHeapPos) + size;

  return valRef;
}

