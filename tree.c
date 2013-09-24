#include "tree.h"
#include "defines.h"

void init_tree(struct configuration * c, struct tree * t) {
  t->condition = HEALTHY;
  t->fuel_remaining = c->initial_fuel;
}

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

void ignite_tree(struct tree * dst, struct tree * src) {
  dst->condition = BURNING;
  dst->fuel_remaining = src->fuel_remaining;
}
