#include <stdbool.h>
#include <stddef.h>

typedef struct {
  // Points to a primitive or an object (i.e. contiguous value addresses)
  void* dataPtr;
  // Data is object or primitive
  bool isObject;
  // How many bytes dataPtr points to
  size_t length;
} Value;

void makeValue(Value* valuePtr, bool isObject, size_t length);

