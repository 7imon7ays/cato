#include <assert.h>
#include "../src/value.h"
#include "../src/vertex.h"

int main() {
  // Init four vertices with char as content
  ValRef aVertex = OBJ_VAL(Vertex, (Vertex) {
    .content = PRIM_VAL(char, 'a')
  });

  ValRef bVertex = OBJ_VAL(Vertex, (Vertex) {
    .content = PRIM_VAL(char, 'b')
  });

  ValRef cVertex = OBJ_VAL(Vertex, (Vertex) {
    .content = PRIM_VAL(char, 'c')
  });

  ValRef dVertex = OBJ_VAL(Vertex, (Vertex) {
    .content = PRIM_VAL(char, 'd')
  });

  assertVertexContent(aVertex, 'a');
  assertVertexContent(bVertex, 'b');
  assertVertexContent(cVertex, 'c');
  assertVertexContent(dVertex, 'd');

  return 0;
}
