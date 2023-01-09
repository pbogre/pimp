#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // strcpy, strcat, strcmp

#include "bmp.h"
#include "file.h"
#include "utils.h"
#include "commands/fill.h"

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
    if(argc < 6){
      printf("Missing required options: first x, first y, last x, last y.\n");
      exit(EXIT_FAILURE);
    }

    RGB color;
    if(argc < 9) color = make_rgb(0, 0, 0);
    else color = make_rgb(strtol(argv[7], NULL, 10),
			  strtol(argv[8], NULL, 10),
			  strtol(argv[9], NULL, 10));

    printf("--- FILL ---\n"
	   "Color: %d-%d-%d\n"
	   "First Point: (%s, %s)\n"
	   "Last Point: (%s, %s)\n",
	   color.R, color.G, color.B, argv[3], argv[4], argv[5], argv[6]);

    fill_region_image24(img, color, strtol(argv[3], NULL, 10),
				    strtol(argv[4], NULL, 10), 
				    strtol(argv[5], NULL, 10),
				    strtol(argv[6], NULL, 10));
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
