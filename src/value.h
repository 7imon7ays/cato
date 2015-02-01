#include <stdbool.h>
#include <stddef.h>

// Macro to access a value struct's data
// and cast it to a given type
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

