#include <assert.h>
#include "vertex.h"

void assertVertexContent(ValRef vertex, char expectedPrimitive) {
  ValRef content = DATA(Vertex, vertex).content;

  assert(DATA(char, content) == expectedPrimitive);
}

