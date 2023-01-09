#pragma once

#include "bmp.h"

RGB make_rgb(uint32_t red, uint32_t green, uint32_t blue){ // util
  RGB rgb;
  rgb.R = red;
  rgb.G = green;
  rgb.B = blue;

  return rgb;
}
