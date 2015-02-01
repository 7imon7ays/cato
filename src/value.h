#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

// Macro to access a value struct's data
// and cast it to a given type

#define INIT_OBJ_VAL(identifier, type)\
  Value* identifier = malloc(sizeof(Value));\
  makeValue(identifier, 1, sizeof(type));

#define INIT_PRIM_VAL(identifier, type)\
  Value* identifier = malloc(sizeof(Value));\
  makeValue(identifier, 0, sizeof(type));

#define DATA(valPtr, type)\
  (*((type*) (valPtr)->dataPtr))

typedef struct {
  // Points to a primitive or an object (i.e. contiguous value addresses)
  void* dataPtr;
  // Data is object or primitive
  bool isObject;
  // How many bytes dataPtr points to
  size_t length;
} Value;

void makeValue(Value* valuePtr, bool isObject, size_t length);

