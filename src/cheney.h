#ifndef CHENEY_H
#define CHENEY_H

#include "value.h"

// Cheney Collect:
// Allocate a new heap. Copy into it the root set of objects, along with any
// objects they refer to directly or indirectly.
void cheneyCollect(ValRef rootSet[], int length);

// Allocate toSpace, fromSpace, and a pointer to the start of fromSpace.
void initCheneyCollect();

// Allocate valRefs on fromSpace and increment pointer to next space.
ValRef cheneyMalloc(size_t size);

#endif /* CHENEY_H */

