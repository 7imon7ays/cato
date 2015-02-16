#include <assert.h>
#include "vertex.h"

void assertVertexContent(ValRef vertexRef, char expectedPrimitive) {
  ValRef content = DATA(vertexRef, Vertex).content;

  assert(DATA(content, char) == expectedPrimitive);
}

