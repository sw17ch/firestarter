#include "round_grid.h"
#include "defines.h"

#include <assert.h>

#define ASSERT_GRID(G) \
  assert(NULL != (G)); \
  assert(NULL != (G)->trees); \
  assert(0 < (G)->width); \
  assert(0 < (G)->height)

void grid_init(struct round_grid * r, size_t w, size_t h, struct tree * ts) {
  assert(NULL != r);

  r->width = w;
  r->height = h;
  r->trees = ts;
}

enum condition grid_burn_cell(struct round_grid * r, size_t x, size_t y) {
  assert(NULL != r);
  assert(NULL != r->trees);
  assert(0 < r->width);
  assert(0 < r->height);
  assert(x < r->width);
  assert(y < r->height);

  return INVALID;
}

