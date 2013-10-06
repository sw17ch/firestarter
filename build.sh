#!/bin/bash

clang -Wall -Wextra -O3 plot.c forestfire.c `pkg-config --cflags --libs MagickCore` -DWIDTH=800 -DHEIGHT=600 -o forestfire
