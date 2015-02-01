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
  Value aVertexVal;
  Value bVertexVal;
  Value cVertexVal;
  Value dVertexVal;

  // Create four Value objects whose data is a Vertex object
  makeValue(&aVertexVal, 1, sizeof(Vertex));
  makeValue(&bVertexVal, 1, sizeof(Vertex));
  makeValue(&cVertexVal, 1, sizeof(Vertex));
  makeValue(&dVertexVal, 1, sizeof(Vertex));

  // Create four Value objects that will hold
  // the content of the Vertices
  Value aVertexContentVal;
  Value bVertexContentVal;
  Value cVertexContentVal;
  Value dVertexContentVal;

  // Allocate a char of memory for the content
  // Values' data pointers to point to
  makeValue(&aVertexContentVal, 1, sizeof(char));
  makeValue(&bVertexContentVal, 1, sizeof(char));
  makeValue(&cVertexContentVal, 1, sizeof(char));
  makeValue(&dVertexContentVal, 1, sizeof(char));

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

