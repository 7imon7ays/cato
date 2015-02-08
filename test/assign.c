#include <assert.h>
#include "../src/value.h"

typedef struct vertex {
  Val content;
  Val vertex1;
  Val vertex2;
} Vertex;

void assertVertexContent(Val vertex, char expectedPrimitive) {
  Val content = DATA(vertex, Vertex).content;

  assert(DATA(content, char) == expectedPrimitive);
}

int main() {
  // Init four vertices with char as content
  Val aVertex = OBJ_VAL(Vertex, (Vertex) {
    .content = PRIM_VAL(char, 'a')
  });

  Val bVertex = OBJ_VAL(Vertex, (Vertex) {
    .content = PRIM_VAL(char, 'b')
  });

  Val cVertex = OBJ_VAL(Vertex, (Vertex) {
    .content = PRIM_VAL(char, 'c')
  });

  Val dVertex = OBJ_VAL(Vertex, (Vertex) {
    .content = PRIM_VAL(char, 'd')
  });

  assertVertexContent(aVertex, 'a');
  assertVertexContent(bVertex, 'b');
  assertVertexContent(cVertex, 'c');
  assertVertexContent(dVertex, 'd');

  return 0;
}

