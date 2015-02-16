#include <stdio.h>
#include <stdint.h>
#include "../src/cheney.h"
#include "../src/vertex.h"
#include "../src/value.h"

int main() {
  // for debugging
  Vertex v;

  ValRef c = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(int64_t, 'c'),
        .left = NULL,
        .right = NULL
      }));

  ValRef b = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(int64_t, 'b'),
        .left = c,
        .right = NULL
      }));

  ValRef a = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(int64_t, 'a'),
        .left = NULL,
        .right = NULL
      }));

  ValRef root = OBJ_VAL(Vertex, ((Vertex) {
        .content = PRIM_VAL(int64_t, 'r'),
        .left = b,
        .right = a
      }));


  cheneyCollect(&root, 1);

  return 0;
}

