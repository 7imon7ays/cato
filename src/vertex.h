#include "../src/value.h"

typedef struct vertex {
  ValRef content;
  ValRef left;
  ValRef right;
} Vertex;

void assertVertexContent(ValRef vertexRef, char expectedPrimitive);

