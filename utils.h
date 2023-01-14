#pragma once

#include "bmp.h"
#include "stdlib.h"

RGB make_rgb(uint32_t red, uint32_t green, uint32_t blue){
  RGB rgb;
  rgb.R = red;
  rgb.G = green;
  rgb.B = blue;

  return rgb;
}

RGB make_rgb_mono(uint32_t color){
  RGB rgb = make_rgb(color, color, color);

  return rgb;
}

// different ways to convert to grayscale
// but taking the average magnitude of each
// value is probably the simplest
int brightness_from_rgb(RGB rgb){
  int brightness = (rgb.R + rgb.G + rgb.B) / 3;
  return brightness;
}

RGB** deep_region_copy_img24(IMAGE img24, int fx, int fy, int lx, int ly){
  int x_range = lx - fx + 1;
  int y_range = ly - fy + 1;

  RGB** deep_region_copy;
  deep_region_copy = (RGB**) malloc(y_range*sizeof(void*));
  for(int y = 0; y < y_range; y++){
    deep_region_copy[y] = (RGB*) malloc(x_range*sizeof(RGB));
    for(int x = 0; x < x_range; x++){
      int original_x = x + fx;
      int original_y = y + fy;
      deep_region_copy[y][x] = img24.pixels[original_y][original_x];
    }
  }

  return deep_region_copy;
}
