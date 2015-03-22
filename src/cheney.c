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

// Track the root set in a virtual stack. This stack contains two kinds of
// values; pointers to the stack's valRefs and, inside each frame, that frame's
// size.
void* rootSetStack = NULL;
void* currentStackPos = NULL;
size_t currentFrameSize = 0;

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
    // For debugging and testing.
    printf("reached leaf %c\n", DATA(char, parentRef));
    return;
  }

  // Point to the value's data and iterate over it as an array of ValRefs.
  // Its length is the size of the parent's data divided by size of a ValRef.
  ValRef* children = &(DATA(ValRef, parentRef));
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

// Allocate toSpace, fromSpace, and a pointer to the start of fromSpace.
// Call this in every function that refers to these values but skip if cheney
// collect has already been initialized.
void initCheney() {
  if (toSpace) {
    return;
  }

  toSpace = malloc(HEAP_SIZE);
  fromSpace = malloc(HEAP_SIZE);
  rootSetStack = malloc(STACK_SIZE);
  currentHeapPos = fromSpace;
  currentStackPos = rootSetStack;
}

void copyStackValues() {
  void* thisStackPos = (void *) currentStackPos;
  size_t thisFrameSize = currentFrameSize;

  while (true) {
    thisStackPos -= thisFrameSize * sizeof(ValRef*);

    for (size_t i = 0; i < thisFrameSize; i++) {
      ValRef* valRefPtr = *(((ValRef**) thisStackPos) + i);
      // If valRef was visited, update the new address. Otherwise, copy the
      // value.
      if ((*valRefPtr)->wasVisited) {
        *valRefPtr = forwardingPointer(*valRefPtr);
      } else {
        *valRefPtr = copyVal(*valRefPtr);
      }
    }

    thisStackPos -= sizeof(size_t);
    if (thisStackPos < rootSetStack) break;
    thisFrameSize = *((size_t*) thisStackPos);
  }
}

void cheneyCollect() {
  printf("Garbarge delenda est.\n");
  initCheney();
  // Reset current position to the start of toSpace; increment it as values are
  // copied over.
  currentHeapPos = toSpace;

  copyStackValues();

  // Keep pointer to valRef whose children (if any) are being copied to
  // toSpace.
  ValRef currentValRef = toSpace;
  while (currentValRef != currentHeapPos) {
    copyChildren(currentValRef);
    currentValRef = nextValRef(currentValRef);
  }

  ValRef temp = toSpace;
  toSpace = fromSpace;
  fromSpace = temp;
}

// Record the current frame size and reset its value to 0.
void pushFrame() {
  initCheney();
  assert(currentStackPos + sizeof(size_t) <= rootSetStack + STACK_SIZE);
  *((int*) currentStackPos) = currentFrameSize;
  currentStackPos += sizeof(size_t);
  currentFrameSize = 0;
}

void pushValRef(ValRef* valRefPtr) {
  initCheney();
  assert(currentStackPos + sizeof(ValRef *) <= rootSetStack + STACK_SIZE);
  *((ValRef **) currentStackPos) = valRefPtr;
  currentStackPos += sizeof(ValRef *);
  currentFrameSize++;
}

// Decrement the stack pointer by the number of valRefs in the current frame.
// The int at its new position is both the size of the previous frame, and
// where we want to push the next valRefs.
void popFrame() {
  initCheney();

  currentStackPos -= currentFrameSize * sizeof(ValRef *);
  // Stack underflow if we've already reached the base of the stack.
  assert(currentStackPos != rootSetStack);
  currentStackPos -= sizeof(size_t);

  currentFrameSize = *((size_t*) currentStackPos);
}

ValRef cheneyMalloc(size_t size) {
  initCheney();
  void* newBufferPosition = ((void*) currentHeapPos) + size;
  void* heapLimit = ((void*) fromSpace) + HEAP_SIZE;
  // Exit for now when fromSpace runs out.
  if (newBufferPosition > heapLimit) {
    cheneyCollect();
    newBufferPosition = ((void*) currentHeapPos) + size;
    heapLimit = ((void*) fromSpace) + HEAP_SIZE;
    if (newBufferPosition > heapLimit) {
      exit(1);
    }
  }

  ValRef valRef = currentHeapPos;
  currentHeapPos = newBufferPosition;

  return valRef;
}

