#ifndef CHENEY_H
#define CHENEY_H

#include "value.h"

// Cheney Collect:
// Allocate a new heap. Copy into it the root set of objects, along with any
// objects they refer to directly or indirectly.
void cheneyCollect();

// Allocate toSpace, fromSpace, and a pointer to the start of fromSpace.
void initCheneyCollect();

// Record previous frame size and init with frame of size 0.
void pushFrame();

// Push ValRef address onto stack and increment current frame size.
void pushValRef(ValRef* valRefPtr);

// Decrement current stack position by the frame size and reassign the current
// frame size to the last element of the previous stack frame.
void popFrame();

// Allocate valRefs on fromSpace and increment pointer to next space.
ValRef cheneyMalloc(size_t size);

#endif /* CHENEY_H */
