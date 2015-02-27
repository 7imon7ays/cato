#ifndef VALUE_H
#define VALUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct ValueHeader {
  // Where to find the copied value after it was moved.
  struct ValueHeader* newPosition;
  // How many bytes of data are stored after isObject.
  size_t length;
  // Data is object or primitive.
  bool isObject;
  bool wasVisited;
} ValueHeader;

typedef ValueHeader* ValRef;

// Access a value header's data and cast it to a given type.
#define DATA(valRef, type)                                      \
  (*((type*) (((void *) valRef) + sizeof(ValueHeader))))

// Initialize and access a value in the same call, using an arbitrary
// lexical block to hide the temporary variable (allowed in gcc).
#define PRIM_VAL(type, data)                            \
  ({                                                    \
    ValRef valRef = makeValue(false, sizeof(type));     \
    DATA(valRef, type) = (data);                        \
    valRef;                                             \
  })

#define OBJ_VAL(type, data)                             \
  ({                                                    \
    ValRef valRef = makeValue(true, sizeof(type));      \
    DATA(valRef , type) = (data);                       \
    valRef;                                             \
  })

// Heap allocate a Value, setting up the ValueHeader and allowing
// enough space for the content.
ValueHeader* makeValue(bool isObject, size_t length);

// Values are type-puns. Their size is sizeof ValueHeader + the length
// declared in their header (length is implicitly multiplied by the
// size of a pointer).
size_t valSize(ValRef valRef);

// Return next available address after a value header and its content.
ValRef nextValRef(ValRef valRef);

// Allocate valRefs on fromSpace and increment pointer to next space.
ValRef cheneyMalloc(size_t size);

#endif /* VALUE_H */
