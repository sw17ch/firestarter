#include "util.h"
#include <stdio.h>

void print_neighbors(struct neighbors * ns) {
  printf(
      "<%d><%d><%d>\n"
      "<%d><!><%d>\n"
      "<%d><%d><%d>\n",
      ns->nw, ns->n, ns->ne,
      ns->w, ns->e,
      ns->sw, ns->s, ns->se);
}

