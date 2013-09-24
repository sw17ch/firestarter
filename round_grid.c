#include "round_grid.h"
#include "defines.h"

void grid_init(struct round_grid * r, size_t w, size_t h, struct tree * ts) {
  r->width = w;
  r->height = h;
  r->trees = ts;
}
