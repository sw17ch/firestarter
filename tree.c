#include "tree.h"
#include "defines.h"

void burn_tree(struct tree * dst, struct tree * src) {
  if (BURNING == src->condition) {
    if (src->fuel_remaining == 0) {
      dst->fuel_remaining = 0;
      dst->condition = BURNT;
    } else {
      dst->fuel_remaining = src->fuel_remaining - 1;
      dst->condition = BURNING;
    }
  } else {
    dst->condition = src->condition;
    dst->fuel_remaining = src->fuel_remaining;
  }
}
