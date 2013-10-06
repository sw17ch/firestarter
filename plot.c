#include <magick/MagickCore.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "plot.h"

#include "macros.h"

#include <stdbool.h>

void forest_to_intensity(enum tree_state * forest, uint8_t * pixels,
                         size_t size)
{
  for (size_t i = 0; i < size; i++) {
    uint8_t * pxs = &pixels[i * 4];

    // Now, with all these magic values, color appears.
    switch(forest[i]) {
      case tree_healthy:
        // greenish
        pxs[0] = 30; pxs[1] = 70; pxs[2] = 10;
        break;
      case tree_burning:
        // orangeish
        pxs[0] = 245; pxs[1] = 190; pxs[2] = 10;
        break;
      case tree_burnt:
        // brownish
        pxs[0] = 30; pxs[1] = 30; pxs[2] = 30;
        break;
      case tree_invalid:
        // blue. just blue.
        pxs[0] = 0; pxs[1] = 0; pxs[2] = 255;
        break;
    }
  }
}

bool draw_forest(enum tree_state * forest, size_t width, size_t height) {
  static uint32_t counter = 0;
  bool ret = false;

  MagickCoreGenesis(NULL,MagickTrue);
  {
    uint8_t * pixels = malloc(
        width *
        height *
        sizeof(uint8_t) *
        4); // channel count

    forest_to_intensity(forest, pixels, width * height);

    const char name[128];
    sprintf((char *)name, "out_%04d.gif", counter);
    ExceptionInfo * exception = AcquireExceptionInfo();
    Image * image = ConstituteImage(width,height,"RGBP",CharPixel,pixels,exception);
    ImageInfo * info = AcquireImageInfo();

    strncpy(image->filename, name, sizeof(image->filename));

    ret = WriteImage(info, image);

    DestroyImage(image);
    DestroyExceptionInfo(exception);
    DestroyImageInfo(info);
    free(pixels);
  }

  counter++;
  MagickCoreTerminus();

  return ret;
}

