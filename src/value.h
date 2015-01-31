#include <stdbool.h>
#include <stddef.h>

typedef struct {
  bool isObject;
  size_t length;
  void* dataPtr;
} Value;

void makeValue(Value* valuePtr, bool isObject, size_t length);

