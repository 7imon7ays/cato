#include <assert.h>
#include "vertex.h"

void assertVertexContent(Val vertex, char expectedPrimitive) {
  Val content = DATA(vertex, Vertex).content;

  assert(DATA(content, char) == expectedPrimitive);
}

