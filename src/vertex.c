#include <assert.h>
#include "vertex.h"

void assertVertexContent(ValRef vertex, char expectedPrimitive) {
  ValRef content = DATA(vertex, Vertex).content;

  assert(DATA(content, char) == expectedPrimitive);
}

