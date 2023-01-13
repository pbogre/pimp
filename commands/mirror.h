#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "../bmp.h"

// makes a copy of the affected region, then mirrors
// the original image by reading from the copy.
// (otherwise, the mirror would only half work as you are mirroring
// pixels while still reading from them)
void mirror_image24(IMAGE img24, int fx, int fy, int lx, int ly){
  int x_range = lx - fx + 1;
  int y_range = ly - fy + 1;


  IMAGE img24_region_copy;
  img24_region_copy.pixels = (RGB**) malloc(y_range*sizeof(void*));
  for(int y = 0; y < y_range; y++){
    img24_region_copy.pixels[y] = (RGB*) malloc(x_range*sizeof(RGB));
    for(int x = 0; x < x_range; x++){
      int original_x = x + fx;
      int original_y = y + fy;
      img24_region_copy.pixels[y][x] = img24.pixels[original_y][original_x];
    }
  }

  for(int y = fy; y <= ly; y++){
    for(int x = fx; x <= lx; x++){
      int copy_x = x - fx;
      int copy_y = y - fy;

      int opposite_copy_x = (x_range-1)-copy_x;
      img24.pixels[y][x] = img24_region_copy.pixels[copy_y][opposite_copy_x];
    }
  }

  // free memory
  for(int y = 0; y < y_range; y++) free(img24_region_copy.pixels[y]);
  free(img24_region_copy.pixels);
}
