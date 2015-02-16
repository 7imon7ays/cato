#include <stdio.h>
#include "../src/cheney.h"
#include "../src/vertex.h"
#include "../src/value.h"

int main() {
  Val c = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(char, 'c'),
        .left = NULL,
        .right = NULL
      }));

  Val b = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(char, 'b'),
        .left = c,
        .right = NULL
      }));

  Val a = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(char, 'a'),
        .left = NULL,
        .right = NULL
      }));

  Val root = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(char, 'r'),
        .left = b,
        .right = a
      }));


  cheneyCollect(&root, 1);

  return 0;
}

