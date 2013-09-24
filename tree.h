#ifndef tree_h
#define tree_h

#include "condition.h"

#include <stddef.h>

struct tree {
  enum condition condition;
  size_t fuel_remaining;
};

void burn_tree(struct tree * dst, struct tree * src);

#endif /* tree_h */
