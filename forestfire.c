/*
 * Usage:
 *   clang -pedantic -std=c99 -Weverything -Werror -O3 -DWIDTH=500 -DHEIGHT=500 forestfire.c -o forestfire
 *   ./forestfire
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#include "macros.h"
#include "foresttypes.h"
#include "plot.h"

#ifndef BURNOUT_FACTOR 
  #define BURNOUT_FACTOR (4)
#endif

#ifndef IGNITE_FACTOR 
  #define IGNITE_FACTOR (10)
#endif

#ifndef WIDTH
  #define WIDTH (100)
#endif

#ifndef HEIGHT
  #define HEIGHT (100)
#endif

/* #define DRAW_IMAGES */
/* #define NOISY */

void print_neighbors(struct neighbors * ns);

static void init_forest(enum tree_state * forest, size_t width, size_t height, enum tree_state state);
static void simulate_forest(enum tree_state * forest_dst,
                            const enum tree_state * forest_src,
                            const size_t width, const size_t height,
                            random_source * fn);
static uint32_t count_state(enum tree_state * forset,
                              size_t width,
                              size_t height,
                              enum tree_state state);
static void simulate_tree(enum tree_state * tree_dst,
                          const enum tree_state * tree_src,
                          struct neighbors * ns,
                          random_source * fn);
static uint32_t gen_rand(uint32_t max);
static uint32_t neighbors_burning(struct neighbors * ns);


static void init_forest(enum tree_state * forest, size_t width, size_t height, enum tree_state state) {
  for (size_t x = 0; x < width; x++) {
    for (size_t y = 0; y < height; y++) {
      size_t ix = x + (width * y);
      forest[ix] = state;
    }
  }
}

static void simulate_forest(enum tree_state * forest_dst,
                            const enum tree_state * forest_src,
                            const size_t width, const size_t height,
                            random_source * fn) {

  struct neighbors ns;

  /* Leave a 1px border to avoid having to boundscheck each pixel. */
  for (size_t x = 1; x < (width - 1); x++) {
    for (size_t y = 1; y < (height - 1); y++) {
      size_t ix = IX(x,y,width);

      ns.nw = forest_src[DIR_IX_NW(x,y,width)];
      ns.n = forest_src[DIR_IX_N(x,y,width)];
      ns.ne = forest_src[DIR_IX_NE(x,y,width)];

      ns.w = forest_src[DIR_IX_W(x,y,width)];
      ns.e = forest_src[DIR_IX_E(x,y,width)];

      ns.sw = forest_src[DIR_IX_SW(x,y,width)];
      ns.s = forest_src[DIR_IX_S(x,y,width)];
      ns.se = forest_src[DIR_IX_SE(x,y,width)];

      simulate_tree(
          &forest_dst[ix],
          &forest_src[ix],
          &ns,
          fn);
    }
  }
}

static uint32_t count_state(enum tree_state * forest, size_t width, size_t height, enum tree_state state) {
  uint32_t sum = 0;

  /* Only count the state of the interior cells; not the border cells. */
  for (size_t x = 1; x < (width - 1); x++) {
    for (size_t y = 1; y < (height - 1); y++) {
      size_t ix = IX(x,y,width);
      if (forest[ix] == state) {
        sum += 1;
      }
    }
  }

  return sum;
}

static void simulate_tree(enum tree_state * tree_dst,
                          const enum tree_state * tree_src,
                          struct neighbors * ns,
                          random_source * fn) {
  /* If not healthy or burning, just copy the tree. */
  *tree_dst = *tree_src;

  switch (*tree_src) {
    case tree_healthy:
      {
        /* A maximum of 8 neightbors can be burning. If we roll a value higher
         * than the number of burning neighbors, we don't catch on fire. The
         * maximum number of neighbors that can be burning is 8, so we use a
         * maximum roll of 9. */
        const uint32_t burn_count = neighbors_burning(ns);
        if (burn_count > 0) {
          /* This tree might catch fire! */
          const uint32_t roll = fn(IGNITE_FACTOR);

          if (roll < burn_count) {
            *tree_dst = tree_burning;
          }
        }
      }
      break;
    case tree_burning:
      /* If the tree is burning, we have a 1/3 chance to burn out. */
      if (fn(BURNOUT_FACTOR) == 0) {
        *tree_dst = tree_burnt;
      }
      break;
    case tree_invalid:
    case tree_burnt:
      break;
  }
}

static uint32_t gen_rand(uint32_t max) {
  return arc4random_uniform(max);
}

void print_neighbors(struct neighbors * ns) {
  printf(
      "<%d><%d><%d>\n"
      "<%d><!><%d>\n"
      "<%d><%d><%d>\n",
      ns->nw, ns->n, ns->ne,
      ns->w, ns->e,
      ns->sw, ns->s, ns->se);
}

static uint32_t neighbors_burning(struct neighbors * ns) {
  return (
      ONE_IF_EQ(ns->nw, tree_burning) +
      ONE_IF_EQ(ns->n, tree_burning) +
      ONE_IF_EQ(ns->ne, tree_burning) +
      ONE_IF_EQ(ns->w, tree_burning) +
      ONE_IF_EQ(ns->e, tree_burning) +
      ONE_IF_EQ(ns->sw, tree_burning) +
      ONE_IF_EQ(ns->s, tree_burning) +
      ONE_IF_EQ(ns->se, tree_burning));
}

/* Aaand, go! */

static enum tree_state ForestA[WIDTH][HEIGHT];
static enum tree_state ForestB[WIDTH][HEIGHT];

int main(int argc, char * argv[]) {
  IGNORE(argc);
  IGNORE(argv);

  enum tree_state * current = (enum tree_state *)ForestA;
  enum tree_state * next = (enum tree_state *)ForestB;

  /* Setup both buffers. */
  init_forest(current, WIDTH, HEIGHT, tree_healthy);
  init_forest(next, WIDTH, HEIGHT, tree_healthy);

  /* Light a tree in buffer A on fire. */
  current[IX(WIDTH / 2, HEIGHT / 2, WIDTH)] = tree_burning;

  uint32_t count = 0;

  do {
    simulate_forest(next, current, WIDTH, HEIGHT, gen_rand);
    count = count_state(next, WIDTH, HEIGHT, tree_burning);

#ifdef DRAW_IMAGES
    draw_forest(next, WIDTH, HEIGHT);
#endif

#ifdef NOISY
    printf("Burning: %u\n", count);
#endif

    enum tree_state * t = current;
    current = next;
    next = t;
  } while (count > 0);

  printf("Healthy: %u\n", count_state(next, WIDTH, HEIGHT, tree_healthy));

  return 0;
}
