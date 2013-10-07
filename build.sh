#!/bin/bash

CFILES="plot.c forestfire.c util.c"
CFLAGS="-Wall -Wextra -O3 "
IMAGEMAGIC_FLAGS=`pkg-config --cflags --libs MagickCore`
WIDTH="256"
HEIGHT="256"

PROG="forestfire"

clang ${CFLAGS} ${CFILES} ${IMAGEMAGIC_FLAGS} \
  -DWIDTH=${WIDTH} \
  -DHEIGHT=${HEIGHT} \
  -DDRAW_IMAGES \
  -DNOISY \
  -o ${PROG}
