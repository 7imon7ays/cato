#ifndef VALUE_H
#define VALUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct ValueHeader {
  // How many bytes of data are stored after isObject.
  size_t length;
  // Data is object or primitive.
  bool isObject;
  bool wasVisited;
} ValueHeader;

typedef ValueHeader* ValRef;

// Access a value header's data and cast it to a given type.
#define DATA(type, valRef)\
  (*((type*) (((void *) valRef) + sizeof(ValueHeader))))

// Initialize and access a value in the same call, using an arbitrary lexical
// block to hide the temporary variable (allowed in gcc).
#define PRIM_VAL(type, data)\
  ({\
    ValRef valRef = makeValue(false, sizeof(type));\
    DATA(type, valRef) = (data);\
    valRef;\
  })

#define OBJ_VAL(type, data)\
  ({\
    ValRef valRef = makeValue(true, sizeof(type));\
    DATA(type, valRef) = (data);\
    valRef;\
  })

#define PRIM_VAR(type, identifier, data)\
  ValRef identifier = PRIM_VAL(type, (data));\
  pushValRef(&(identifier));

#define OBJ_VAR(type, identifier, data)\
  ValRef identifier = OBJ_VAL(type, (data));\
  pushValRef(&(identifier));

// Heap allocate a Value, setting up the ValueHeader and allowing enough space
// for the content.
ValRef makeValue(bool isObject, size_t length);

// Find the copied value after it was moved; return NULL if it wasn't
ValRef forwardingPointer(ValRef valRef);

void setForwardingPointer(ValRef valRef, ValRef newRef);

// Values are type-puns. Their size is sizeof ValueHeader + the length declared
// in their header (lenght is implicitely multiplied by the size of a pointer).
size_t valSize(ValRef valRef);

// Return next available address after a value header and its content.
ValRef nextValRef(ValRef valRef);

#endif /* VALUE_H */

