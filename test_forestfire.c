#include "greatest.h"
#include "tree.h"

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

/* Suite definition. */

SUITE(tree) {
  RUN_TEST(tree_burn_is_inert_if_not_burning);
  RUN_TEST(tree_loses_fuel_if_burning);
  RUN_TEST(tree_burns_out_when_out_of_fuel);
}

GREATEST_MAIN_DEFS();

int main(int argc, char * argv[]) {
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(tree);
  GREATEST_MAIN_END();
}
