#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // strcpy, strcat, strcmp

#include "bmp.h"
#include "file.h"
#include "utils.h"

#include "commands/fill.h"
#include "commands/bw.h"
#include "commands/mirror.h"

int main(int argc, char ** argv){
  char * file_name;
  char * command;
  if(argc > 2){
    file_name = argv[1];
    command = argv[2];
  }
  else { printf("usage: pimp <file> { fill | mirror | bw | crop | gblur | blur } ...\n"); exit(EXIT_FAILURE); }

  IMAGE img = image_from_bmp(file_name);

  if(strcmp(command, "fill") == 0){
    if(argc <= 6){
      printf("Missing required arguments: first x, first y, last x, last y.\n");
      exit(EXIT_FAILURE);
    }

    // should i check if the coordinates are valid? e.g. x < img.width?
    // nah...
    int fx = strtol(argv[3], NULL, 10);
    int lx = strtol(argv[5], NULL, 10);
    int fy = strtol(argv[4], NULL, 10);
    int ly = strtol(argv[6], NULL, 10);

    RGB color;
    if(argc <= 9) color = make_rgb_mono(0);
    else color = make_rgb(strtol(argv[7], NULL, 10),
			  strtol(argv[8], NULL, 10),
			  strtol(argv[9], NULL, 10));

    printf("--- FILL ---\n"
	   "Color: %d-%d-%d\n"
	   "First Point: (%d, %d)\n"
	   "Last Point: (%d, %d)\n"
	   "Region Size: (%d, %d)\n",
	   color.R, color.G, color.B, fx, fy, lx, ly, 
	   lx-fx+1, ly-fy+1);

    fill_region_image24(img, color, fx, fy, lx, ly);
  }

  else if (strcmp(command, "bw") == 0){
    int fx = 0;
    int fy = 0;
    int lx = img.width-1;
    int ly = img.height-1;
    if(argc > 3){
      fx = strtol(argv[3], NULL, 10);
      fy = strtol(argv[4], NULL, 10);
      lx = strtol(argv[5], NULL, 10);
      ly = strtol(argv[6], NULL, 10);
    }

    printf("--- BLACK & WHITE ---\n"
	   "First Pixel: (%d, %d)\n"
	   "Last Pixel: (%d, %d)\n"
	   "Region Size: (%d, %d)\n",
	   fx, fy, lx, ly, lx-fx+1, ly-fy+1);

    black_white_image24(img, fx, fy, lx, ly); 
  }


  else if (strcmp(command, "mirror") == 0){
    int fx = 0;
    int fy = 0;
    int lx = img.width-1;
    int ly = img.height-1;
    if(argc > 3){
      fx = strtol(argv[3], NULL, 10);
      fy = strtol(argv[4], NULL, 10);
      lx = strtol(argv[5], NULL, 10);
      ly = strtol(argv[6], NULL, 10);
    }

    printf("--- MIRROR ---\n"
	   "First Pixel: (%d, %d)\n"
	   "Last Pixel: (%d, %d)\n"
	   "Region Size: (%d, %d)\n",
	   fx, fy, lx, ly, lx-fx+1, ly-fy+1);

    mirror_image24(img, fx, fy, lx, ly); 
  }

  char * new_file_name = malloc(4+sizeof(file_name)+1);
  strcpy(new_file_name, "new-");
  strcat(new_file_name, file_name);
  bmp_from_image24(new_file_name, img);

  // free memory
  for(int i = 0; i < img.height; i++) free(img.pixels[i]);
  free(img.pixels);
  free(new_file_name);

  return EXIT_SUCCESS;
}
