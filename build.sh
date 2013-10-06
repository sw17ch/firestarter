#!/bin/bash

clang -Wall -Wextra -O3 plot.c forestfire.c `pkg-config --cflags --libs MagickCore` -DWIDTH=200 -DHEIGHT=200 -o forestfire
