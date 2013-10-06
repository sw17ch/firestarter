#!/bin/bash

CFILES="plot.c forestfire.c util.c"
CFLAGS="-Wall -Wextra -O3 "
IMAGEMAGIC_FLAGS=`pkg-config --cflags --libs MagickCore`

PROG="forestfire"

clang ${CFLAGS} ${CFILES} ${IMAGEMAGIC_FLAGS} \
  -DWIDTH=800 \
  -DHEIGHT=600 \
  -DDRAW_IMAGES \
  -DNOISY \
  -o ${PROG}
