#pragma once

#include <stdlib.h>
#include <string.h>

#include "../bmp.h"

// 1. shift all pixels in range fx->lx to start from x=0
// 2. shift all pixels in range fy->ly to start from y=0 
// 3. free memory of leftover image (only leftover y, as 
//    the rest will be taken care of when freeing the whole image in pimp.c) 
// 4. update image width & height
void crop_image24(IMAGE *img24, int fx, int fy, int lx, int ly){
  int x_range = lx-fx;
  int y_range = ly-fy;

  for(int y = fy; y <= ly; y++){
    memmove(&img24->pixels[y][0], &img24->pixels[y][fx], sizeof(RGB)*(img24->width-fx));
  }
  memmove(&img24->pixels[0], &img24->pixels[fy], sizeof(RGB*)*img24->width);

  for(int y = y_range+2; y < img24->height; y++) free(img24->pixels[y]);

  img24->width = x_range+1;
  img24->height = y_range+1;
}
