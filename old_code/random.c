#include "random.h"
#include <stdlib.h>

static uint32_t default_generator(struct random * r);

void init_default_random(struct random * r, unsigned int seed, int32_t min, int32_t max) {
  r->seed = seed;
  r->min = min;
  r->max = max;
  r->gen = default_generator;
}

static int32_t default_generator(struct random * r) {
  uint32_t r = arc4random_uniform(r->max);
}
