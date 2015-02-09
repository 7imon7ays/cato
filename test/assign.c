#include <assert.h>
#include "../src/value.h"
#include "../src/vertex.h"

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

