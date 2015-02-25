#include <stdio.h>
#include "../src/cheney.h"
#include "../src/value.h"
#include "../src/vertex.h"

int main() {

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
        .right = NULL
      }));

  ValRef root = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(char, 'r'),
        .left = b,
        .right = a
      }));


  cheneyCollect(&root, 1);

  return 0;
}

