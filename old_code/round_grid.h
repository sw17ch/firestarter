#ifndef round_grid_h
#define round_grid_h

#include <stddef.h>
#include "condition.h"
#include "tree.h"

struct round_grid {
  size_t width;
  size_t height;
  struct tree * trees;
};

void grid_init(struct round_grid * r, size_t w, size_t h, struct tree * ts);
enum condition grid_burn_cell(struct round_grid * r, size_t x, size_t y);

#endif /* round_grid_h */
