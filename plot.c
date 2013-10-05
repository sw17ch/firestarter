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
    uint8_t px;
    switch(forest[i]) {
      case tree_healthy: px = 255; break;
      case tree_burning: px = 192; break;
      case tree_invalid:
      case tree_burnt:   px = 0;   break;
    }
    pixels[i] = px;
  }
}

bool draw_forest(enum tree_state * forest, size_t width, size_t height) {
  // MagickCoreGenesis(*argv,MagickTrue);
  MagickCoreGenesis(NULL,MagickTrue);
  {
    uint8_t * pixels = malloc(width * height * sizeof(uint8_t));
    forest_to_intensity(forest, pixels, width * height);

    const char * name = "out.png";
    ExceptionInfo * exception = AcquireExceptionInfo();
    Image * image = ConstituteImage(width,height,"I",CharPixel,pixels,exception);
    ImageInfo * info = AcquireImageInfo();

    strncpy(image->filename, name, sizeof(image->filename));

    return WriteImage(info, image);
  }
  MagickCoreTerminus();
}

