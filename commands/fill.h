#pragma once

#include "../bmp.h"

void fill_region_image24(IMAGE img24, RGB color, int fx, int fy, int lx, int ly){
  for(int y = fy; y <= ly; y++){
    for(int x = fx; x <= lx; x++){
      img24.pixels[y][x] = color;
    }
  }
}
