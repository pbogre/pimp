#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../bmp.h"
#include "../utils.h"

void box_blur_image24(IMAGE img24, int length, int fx, int fy, int lx, int ly){
  RGB** deep_region_copy = deep_region_copy_img24(img24, fx, fy, lx, ly);
  int offset = length-2;
  int area = pow(length,2);

  for(int y = fy + offset; y <= ly; y+=length){
    for(int x = fx + offset; x <= lx; x+=length){

      // put pixels in range of offset in an array 
      RGB* sample_region = (RGB*) malloc(area*sizeof(int));
      int total = area;
      for(int i = 0, j = -offset; i < length; i++, j++){
	int copy_y = y + j - fy;
	int copy_first_x = x - offset - fx;
	if(copy_y < 0 || copy_y >= ly || copy_first_x < 0 || copy_first_x >= lx){
	    total--;
	    continue;
	}

	memcpy(&sample_region[length*i], &deep_region_copy[copy_y][copy_first_x], length*sizeof(int));
      }

      // sum of R,G,B and average
      int sum[3] = {0};
      for(int i = 0; i < area; i++){
	sum[0] += sample_region[i].R;
	sum[1] += sample_region[i].G;
	sum[2] += sample_region[i].B;
      }
      RGB average_rgb = make_rgb(sum[0]/total, sum[1]/total, sum[2]/total);

      // fill box with average rgb
      // if length of boxes don't fit perfectly,
      // stretch final boxes by leftover pixels (both vertical and horizontal)
      int row_length = length;
      if(x + length >= lx) row_length += (lx-fx) % length;

      RGB* box_rgb = (RGB*) malloc(row_length*sizeof(RGB));
      for(int i = 0; i < row_length; i++) 
	box_rgb[i] = average_rgb;
    
      int y_increase = offset;
      if(y + length >= lx) y_increase += (ly-fy) % length;
      for(int i = y-offset; i <= y+y_increase; i++){
	if(i < 0 || i >= ly) continue;
	memcpy(&img24.pixels[i][x-offset], &box_rgb[0], row_length*sizeof(RGB));
      }

      // remember to free memory
      free(sample_region);
    }
  }

  // free memory
  for(int y = 0; y <= ly-fy; y++) free(deep_region_copy[y]);
  free(deep_region_copy);
}
