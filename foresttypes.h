#ifndef FORESTTYPES_H
#define FORESTTYPES_H

#include <stdint.h>

enum tree_state {
  tree_invalid = 0,
  tree_healthy = 1,
  tree_burning = 2,
  tree_burnt   = 3,
};

struct neighbors {
  enum tree_state nw;
  enum tree_state n;
  enum tree_state ne;

  enum tree_state w;
  // self
  enum tree_state e;

  enum tree_state sw;
  enum tree_state s;
  enum tree_state se;
};

typedef uint32_t (random_source)(uint32_t);

#endif /* FORESTTYPES_H */
