#ifndef tree_h
#define tree_h

#include "condition.h"
#include "configuration.h"

#include <stddef.h>
#include <stdint.h>

struct tree {
  enum condition condition;
  uint32_t fuel_remaining;
};

void init_tree(struct configuration * c, struct tree * t);
void burn_tree(struct tree * dst, struct tree * src);
void ignite_tree(struct tree * dst, struct tree * src);

#endif /* tree_h */
