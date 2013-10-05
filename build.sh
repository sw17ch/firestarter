#!/bin/bash

clang -Wall -Wextra -O3 plot.c forestfire.c `pkg-config --cflags --libs MagickCore` -DWIDTH=500 -DHEIGHT=500 -o forestfire
