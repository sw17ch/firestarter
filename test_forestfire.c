#include "greatest.h"

#include "tree.h"
#include "configuration.h"

TEST tree_initializes(void) {
  struct tree t = { .condition = BURNT, .fuel_remaining = 10 };
  struct configuration c = { .initial_fuel = 5 };

  init_tree(&c, &t);

  ASSERT_EQ(HEALTHY, t.condition);
  ASSERT_EQ(5, t.fuel_remaining);

  PASS();
}

TEST tree_burn_is_inert_if_not_burning(void) {
  struct tree t = { .condition = HEALTHY, .fuel_remaining = 10 };
  struct tree n = { .condition = BURNING, .fuel_remaining = 99 };

  burn_tree(&n, &t);

  ASSERT_EQ(HEALTHY, n.condition);
  ASSERT_EQ(10, n.fuel_remaining);

  PASS();
}

TEST tree_loses_fuel_if_burning(void) {
  struct tree t = { .condition = BURNING, .fuel_remaining = 10 };
  struct tree n = { .condition = HEALTHY, .fuel_remaining = 99 };

  burn_tree(&n, &t);

  ASSERT_EQ(BURNING, n.condition);
  ASSERT_EQ(9, n.fuel_remaining);

  PASS();
}

TEST tree_burns_out_when_out_of_fuel(void) {
  struct tree t = { .condition = BURNING, .fuel_remaining = 0 };
  struct tree n = { .condition = HEALTHY, .fuel_remaining = 99 };

  burn_tree(&n, &t);

  ASSERT_EQ(BURNT, n.condition);
  ASSERT_EQ(0, n.fuel_remaining);

  PASS();
}

TEST tree_ignites(void) {
  struct tree t = { .condition = HEALTHY, .fuel_remaining = 10 };
  struct tree n = { .condition = HEALTHY, .fuel_remaining = 0 };

  ignite_tree(&n, &t);

  ASSERT_EQ(BURNING, n.condition);
  ASSERT_EQ(10, n.fuel_remaining);

  PASS();
}

/* Suite definition. */

SUITE(tree) {
  RUN_TEST(tree_initializes);
  RUN_TEST(tree_burn_is_inert_if_not_burning);
  RUN_TEST(tree_loses_fuel_if_burning);
  RUN_TEST(tree_burns_out_when_out_of_fuel);
  RUN_TEST(tree_ignites);
}

GREATEST_MAIN_DEFS();

int main(int argc, char * argv[]) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(tree);
  GREATEST_MAIN_END();
}
