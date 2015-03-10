#ifndef VERTEX_H
#define VERTEX_H

#include "../src/value.h"

typedef struct vertex {
  ValRef content;
  ValRef left;
  ValRef right;
} Vertex;

void assertVertexContent(ValRef vertex, char expectedPrimitive);

#endif /* VERTEX_H */
