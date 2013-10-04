#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define IGNORE(V) (void)(V)
#define IX(X,Y,WIDTH) ((X) + ((WIDTH) * (Y)))

#define DIR_IX_NW(X,Y,WIDTH) IX((X) - 1, (Y) - 1, (WIDTH))
#define DIR_IX_N(X,Y,WIDTH)  IX((X)    , (Y) - 1, (WIDTH))
#define DIR_IX_NE(X,Y,WIDTH) IX((X) + 1, (Y) - 1, (WIDTH))

#define DIR_IX_W(X,Y,WIDTH)  IX((X) - 1, (Y)    , (WIDTH))
#define DIR_IX_E(X,Y,WIDTH)  IX((X) + 1, (Y)    , (WIDTH))

#define DIR_IX_SW(X,Y,WIDTH) IX((X) - 1, (Y) + 1, (WIDTH))
#define DIR_IX_S(X,Y,WIDTH)  IX((X)    , (Y) + 1, (WIDTH))
#define DIR_IX_SE(X,Y,WIDTH) IX((X) + 1, (Y) + 1, (WIDTH))

#define ONE_IF_EQ(T,E) ((T) == (E) ? 1 : 0)

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

  for (size_t x = 0; x < width; x++) {
    for (size_t y = 0; y < height; y++) {
      size_t ix = IX(x,y,width);

      if (0 == x || 0 == y) {
        ns.nw = tree_invalid;
      } else {
        ns.nw = forest_src[DIR_IX_NW(x,y,width)];
      }
      if (0 == y) {
        ns.n = tree_invalid;
      } else {
        ns.n = forest_src[DIR_IX_N(x,y,width)];
      }
      if ((width - 1) == x || 0 == y) {
        ns.ne = tree_invalid;
      } else {
        ns.ne = forest_src[DIR_IX_NE(x,y,width)];
      }

      if (0 == x) {
        ns.w = tree_invalid;
      } else {
        ns.w = forest_src[DIR_IX_W(x,y,width)];
      }
      if ((width - 1) == x) {
        ns.e = tree_invalid;
      } else {
        ns.e = forest_src[DIR_IX_E(x,y,width)];
      }

      if (0 == x || (height - 1) == y) {
        ns.sw = tree_invalid;
      } else {
        ns.sw = forest_src[DIR_IX_SW(x,y,width)];
      }
      if ((height - 1) == y) {
        ns.s = tree_invalid;
      } else {
        ns.s = forest_src[DIR_IX_S(x,y,width)];
      }
      if ((width - 1) == x || (height - 1) == y) {
        ns.se = tree_invalid;
      } else {
        ns.se = forest_src[DIR_IX_SE(x,y,width)];
      }

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

  for (size_t x = 0; x < width; x++) {
    for (size_t y = 0; y < height; y++) {
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
          const uint32_t roll = fn(10);

          if (roll < burn_count) {
            *tree_dst = tree_burning;
          }
        }
      }
      break;
    case tree_burning:
      /* If the tree is burning, we have a 1/3 chance to burn out. */
      if (fn(4) == 0) {
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

#ifndef WIDTH
  #define WIDTH (100)
#endif

#ifndef HEIGHT
  #define HEIGHT (100)
#endif

static enum tree_state ForestA[WIDTH][HEIGHT];
static enum tree_state ForestB[WIDTH][HEIGHT];

int main(int argc, char * argv[]) {
  IGNORE(argc);
  IGNORE(argv);

  /* Setup both buffers. */
  init_forest((enum tree_state *)ForestA, WIDTH, HEIGHT, tree_healthy);
  init_forest((enum tree_state *)ForestB, WIDTH, HEIGHT, tree_invalid);

  /* Light a tree in buffer A on fire. */
  ForestA[WIDTH / 2][HEIGHT / 2] = tree_burning;

  enum tree_state * current = (enum tree_state *)ForestA;
  enum tree_state * next = (enum tree_state *)ForestB;
  uint32_t count = 0;

  do {
    simulate_forest(next, current, WIDTH, HEIGHT, gen_rand);
    count = count_state(next, WIDTH, HEIGHT, tree_burning);
    printf("Burning: %u\n", count);

    enum tree_state * t = current;
    current = next;
    next = t;
  } while (count > 0);

  printf("Healthy: %u\n", count_state(next, WIDTH, HEIGHT, tree_healthy));

  return 0;
}
