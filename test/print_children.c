#include <stdio.h>
#include "../src/cheney.h"
#include "../src/value.h"
#include "../src/vertex.h"

int main() {
  initCheneyCollect();

  OBJ_VAR(Vertex, c, ((Vertex) {
        .content = PRIM_VAL(char, 'c'),
        .left = NULL,
        .right = NULL
      }));

  OBJ_VAR(Vertex, b, ((Vertex) {
        .content = PRIM_VAL(char, 'b'),
        .left = c,
        .right = NULL
      }));

  OBJ_VAR(Vertex, a, ((Vertex) {
        .content = PRIM_VAL(char, 'a'),
        .left = NULL,
        .right = c
      }));

  OBJ_VAR(Vertex, root, ((Vertex) {
        .content = PRIM_VAL(char, 'r'),
        .left = b,
        .right = a
      }));

  // Create a cycle in the graph to test that child values are only copied
  // once.
  DATA(c, Vertex).left = root;
  cheneyCollect();

  return 0;
}
