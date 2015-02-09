#include "../src/value.h"

typedef struct vertex {
  Val content;
  Val left;
  Val right;
} Vertex;

void assertVertexContent(Val vertex, char expectedPrimitive);

