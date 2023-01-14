#pragma once

#include "../bmp.h"
#include "../utils.h"

void black_white_image24(IMAGE img24, int fx, int fy, int lx, int ly){
  for(int y = fy; y <= ly; y++){
    for(int x = fx; x <= lx; x++){
      // grayscale by average magnitude of RGB
      uint16_t brightness = brightness_from_rgb(img24.pixels[y][x]);
      img24.pixels[y][x] = make_rgb_mono(brightness);
    }
  }
}
