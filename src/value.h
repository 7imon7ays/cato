#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

// Initialize object value header

#define MAKE_OBJ_VAL(type)\
  makeValue(1, sizeof(type));

// Initialize primitive value header

#define MAKE_PRIM_VAL(type)\
  makeValue(0, sizeof(type));

// Access a value header's data
// and cast it to a given type

#define DATA(valPtr, type)\
  (*((type*) (((void *) valPtr) + sizeof(ValueHeader))))

// Initialize and access a type
// in one call
// Use an arbitrary lexical block
// (allowed in GCC)

#define PRIM_VAL(type, data)\
  ({\
    Val val = MAKE_PRIM_VAL(type);\
    DATA(val, type) = data;\
    val;\
  })

#define OBJ_VAL(type, data)\
  ({\
    Val val = MAKE_OBJ_VAL(type);\
    DATA(val, type) = data;\
    val;\
  })

typedef struct {
  // How many bytes of data are stored after isObject
  size_t length;
  // Data is object or primitive
  bool isObject;
} ValueHeader;

typedef ValueHeader* Val;

ValueHeader* makeValue(bool isObject, size_t length);

