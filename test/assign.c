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
  INIT_OBJ_VAL(aVertexVal, Vertex);
  INIT_OBJ_VAL(bVertexVal, Vertex);
  INIT_OBJ_VAL(cVertexVal, Vertex);
  INIT_OBJ_VAL(dVertexVal, Vertex);

  // Create four Value objects that will hold
  // the content of the Vertices, i.e. a char
  INIT_PRIM_VAL(aVertexContentVal, char);
  INIT_PRIM_VAL(bVertexContentVal, char);
  INIT_PRIM_VAL(cVertexContentVal, char);
  INIT_PRIM_VAL(dVertexContentVal, char);

  // Point the Verteces' content to the content Value
  DATA(&aVertexVal, Vertex).content = &aVertexContentVal;
  DATA(&bVertexVal, Vertex).content = &bVertexContentVal;
  DATA(&cVertexVal, Vertex).content = &cVertexContentVal;
  DATA(&dVertexVal, Vertex).content = &dVertexContentVal;

  // Point the content Values' data pointers to
  // respective chars
  DATA(&aVertexContentVal, char) = 'a';
  DATA(&bVertexContentVal, char) = 'b';
  DATA(&cVertexContentVal, char) = 'c';
  DATA(&dVertexContentVal, char) = 'd';

  assertVertexContent(&aVertexVal, 'a');
  assertVertexContent(&bVertexVal, 'b');
  assertVertexContent(&cVertexVal, 'c');
  assertVertexContent(&dVertexVal, 'd');

  return 0;
}

