#pragma once

#include "bmp.h"

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
