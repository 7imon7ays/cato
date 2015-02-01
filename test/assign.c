#include <assert.h>
#include "../src/value.h"

typedef struct vertex {
  Value* content;
  Value* vp1;
  Value* vp2;
} Vertex;

void assertVertexContent(Value* vertexValuePtr, char expectedPrimitive) {
  Vertex* vertexPtr = &(DATA(vertexValuePtr, Vertex));
  Value* contentValuePtr = vertexPtr->content;
  char content = DATA(contentValuePtr, char);

  assert(content == expectedPrimitive);
}

int main() {
  // Create four Value objects that will hold Vertices
  INIT_OBJ_VAL(aVertexValPtr, Vertex);
  INIT_OBJ_VAL(bVertexValPtr, Vertex);
  INIT_OBJ_VAL(cVertexValPtr, Vertex);
  INIT_OBJ_VAL(dVertexValPtr, Vertex);

  // Create four Value objects that will hold
  // the content of the Vertices, i.e. a char
  INIT_PRIM_VAL(aVertexContentValPtr, char);
  INIT_PRIM_VAL(bVertexContentValPtr, char);
  INIT_PRIM_VAL(cVertexContentValPtr, char);
  INIT_PRIM_VAL(dVertexContentValPtr, char);

  // Point the Verteces' content to the content Value
  DATA(aVertexValPtr, Vertex).content = aVertexContentValPtr;
  DATA(bVertexValPtr, Vertex).content = bVertexContentValPtr;
  DATA(cVertexValPtr, Vertex).content = cVertexContentValPtr;
  DATA(dVertexValPtr, Vertex).content = dVertexContentValPtr;

  // Point the content Values' data pointers to
  // respective chars
  DATA(aVertexContentValPtr, char) = 'a';
  DATA(bVertexContentValPtr, char) = 'b';
  DATA(cVertexContentValPtr, char) = 'c';
  DATA(dVertexContentValPtr, char) = 'd';

  assertVertexContent(aVertexValPtr, 'a');
  assertVertexContent(bVertexValPtr, 'b');
  assertVertexContent(cVertexValPtr, 'c');
  assertVertexContent(dVertexValPtr, 'd');

  return 0;
}

