#ifndef VALUE_H
#define VALUE_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

// Initialize object value header

#define MAKE_OBJ_VAL(type)\
  makeValue(true, sizeof(type));

// Initialize primitive value header

#define MAKE_PRIM_VAL(type)\
  makeValue(false, sizeof(type));

// Access a value header's data
// and cast it to a given type

#define DATA(valRef, type)\
  (*((type*) (((void *) valRef) + sizeof(ValueHeader))))

// Initialize and access a value in the same
// call, using an arbitrary lexical block
// to hide the temporary variable
// (allowed in gcc)

#define PRIM_VAL(type, data)\
  ({\
    ValRef valRef = MAKE_PRIM_VAL(type);\
    DATA(valRef, type) = (data);\
    valRef;\
  })

#define OBJ_VAL(type, data)\
  ({\
    ValRef valRef = MAKE_OBJ_VAL(type);\
    DATA(valRef , type) = (data);\
    valRef;\
  })

typedef struct {
  // How many bytes of data are stored after isObject
  size_t length;
  // Data is object or primitive
  bool isObject;
  bool wasVisited;
} ValueHeader;

typedef ValueHeader* ValRef;

ValueHeader* makeValue(bool isObject, size_t length);

size_t valSize(ValRef v);

ValRef nextValRef(ValRef v);

// for debugging
void* data(ValRef valRef);

#endif

