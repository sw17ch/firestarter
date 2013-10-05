#ifndef PLOT_H
#define PLOT_H

#include <stddef.h>
#include <stdbool.h>

#include "foresttypes.h"

bool draw_forest(enum tree_state * forest, size_t width, size_t height);

#endif /* PLOT_H */
