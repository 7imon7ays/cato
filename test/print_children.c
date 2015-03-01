#include <stdio.h>
#include "../src/cheney.h"
#include "../src/value.h"
#include "../src/vertex.h"

int main() {
  initCheneyCollect();

  ValRef c = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(char, 'c'),
        .left = NULL,
        .right = NULL
      }));

  ValRef b = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(char, 'b'),
        .left = c,
        .right = NULL
      }));

  ValRef a = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(char, 'a'),
        .left = NULL,
        .right = c
      }));

  ValRef root = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(char, 'r'),
        .left = b,
        .right = a
      }));

  // Create a cycle in the graph to test that child values are only copied
  // once.
  DATA(c, Vertex).left = root;
  ValRef* rootAddress = &root;
  cheneyCollect(&rootAddress, 1);

  return 0;
}

