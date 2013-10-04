#ifndef random_h
#define random_h

#include <stdint.h>

typedef int32_t (gen_random)(struct random * r);

struct random {
  unsigned int seed;
  int32_t min;
  int32_t max;

  gen_random * gen;
};

void init_default_random(struct random * r, unsigned int seed, int32_t min, int32_t max);

#endif /* random_h */
