#pragma once

#include <stdlib.h>

#include "../bmp.h"
#include "../utils.h"

// makes a copy of the affected region, then mirrors
// the original image by reading from the copy.
// (otherwise, the mirror would only half work as you are mirroring
// pixels while still reading from them)
void mirror_image24(IMAGE img24, int fx, int fy, int lx, int ly){
  int x_range = lx - fx + 1;
  int y_range = ly - fy + 1;
 
  RGB** deep_region_copy = deep_region_copy_img24(img24, fx, fy, lx, ly);

  for(int y = fy; y <= ly; y++){
    for(int x = fx; x <= lx; x++){
      int copy_x = x - fx;
      int copy_y = y - fy;

      int opposite_copy_x = (x_range-1)-copy_x;
      img24.pixels[y][x] = deep_region_copy[copy_y][opposite_copy_x];
    }
  }

  // free memory
  for(int y = 0; y < y_range; y++) free(deep_region_copy[y]);
  free(deep_region_copy);
}
