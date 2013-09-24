#ifndef round_grid_h
#define round_grid_h

#include <stddef.h>

struct round_grid {
  size_t width;
  size_t height;
  struct tree * trees;
};

#endif /* round_grid_h */
