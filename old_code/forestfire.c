#include "defines.h"
#include "round_grid.h"

#define WIDTH (10)
#define HEIGHT (10)

struct round_grid round_a;
struct tree trees_a[WIDTH][HEIGHT];

struct round_grid round_b;
struct tree trees_b[WIDTH][HEIGHT];

int main(int argc, char * argv[]) {
  IGNORE(argc);
  IGNORE(argv);

  grid_init(&round_a, WIDTH, HEIGHT, (struct tree *)trees_a);
  grid_init(&round_b, WIDTH, HEIGHT, (struct tree *)trees_b);

  return 0;
}
