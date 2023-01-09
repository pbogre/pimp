#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // strcpy, strcat, strcmp

#include "bmp.h"
#include "utils.h"
#include "commands/fill.h"

IMAGE image24_from_data(FILE *fp, int width, int height){
  IMAGE img;
  img.height = height;
  img.width = width;

  // allocate and assign memory to image data
  // loop is backwards because BMP pixels are bottom->up
  img.pixels = (RGB**) malloc(height*sizeof(void*)); // h amount of arrays of pointers
  for(int y = height-1; y >= 0; y--){
    img.pixels[y] = (RGB*) malloc(width*sizeof(RGB)); // each h array of size w
    fread(img.pixels[y], width, sizeof(RGB), fp); // assign to allocated memory
  }

  return img;
}

// 32-bit is supported as input but only output is 24-bit
IMAGE32 image32_from_data(FILE *fp, int width, int height){
  IMAGE32 img;
  img.height = height;
  img.width = width;

  // same logic as for 24-bit
  img.pixels = (RGBA**) malloc(height*sizeof(void*));
  for(int y = height-1; y >= 0; y--){
    img.pixels[y] = (RGBA*) malloc(width*sizeof(RGBA));
    fread(img.pixels[y], width, sizeof(RGBA), fp);
  }

  return img;
}

RGB rgb_from_rgba(RGBA rgba){
  RGB rgb;
  rgb.R = rgba.R;
  rgb.G = rgba.G;
  rgb.B = rgba.B;

  return rgb;
}

IMAGE image24_from_image32(IMAGE32 img32){
  IMAGE img24;
  img24.height = img32.height;
  img24.width = img32.width;

  for(int y = 0; y < img32.height; y++){
    for(int x = 0; x < img32.width; x++){
      img24.pixels[y][x] = rgb_from_rgba(img32.pixels[y][x]);
    }
  }

  return img24;
}

IMAGE image_from_bmp(char * file_name){
  FILE *fp = fopen(file_name, "rb");

  BMPHEADER header;
  DIBHEADER dibheader;

  fread(header.name, 2, 1, fp);
  fread(&header.size, 3*sizeof(uint32_t), 1, fp);
  printf("--- BMP HEADER ---\nFirst 2 bytes: %c%c\nSize: %d\nOffset: %d\n\n", 
         header.name[0], header.name[1], header.size, header.offset);

  if(header.name[0] != 'B' || header.name[1] != 'M'){
    printf("File must be .bmp (BITMAP)\n");
    fclose(fp);
    exit(EXIT_FAILURE); 
  }

  fread(&dibheader.header_size, sizeof(DIBHEADER), 1, fp);
  printf("--- DIB HEADER ---\nHeader size: %d\nWidth: %d\nHeight: %d\nColor Panes: %d\n"
	 "Color Depth: %d\nCompression: %d\nImage Size: %d\nHorizontal Res.: %d\n"
	 "Vertical Res.: %d\nNumber of Colors: %d\nNumber of Important Colors: %d\n\n",
	 dibheader.header_size, dibheader.width, dibheader.height, dibheader.color_panes,
	 dibheader.color_depth, dibheader.compression, dibheader.image_size,
	 dibheader.hres, dibheader.vres, dibheader.number_colors, dibheader.number_important_colors);

  if(dibheader.header_size != 40 || dibheader.compression != 0 || 
     (dibheader.color_depth != 24 && dibheader.color_depth != 32)){
    printf("Bitmap must be 24-bit or 32-bit and use no compression. '%s' is %d-bit and uses compression %d.\n", file_name, dibheader.color_depth, dibheader.compression);
    fclose(fp); 
    exit(EXIT_FAILURE); 
  }

  fseek(fp, header.offset, SEEK_SET); // go to start of image data
  IMAGE img;
  if(dibheader.color_depth == 24) img = image24_from_data(fp, dibheader.width, dibheader.height);
  if(dibheader.color_depth == 32) img = image24_from_image32(image32_from_data(fp, dibheader.width, dibheader.height));  

  fclose(fp);

  return img;
}

void bmp_from_image24(char * file_name, IMAGE img24){
  BMPHEADER header;
  header.name[0] = 'B';
  header.name[1] = 'M';
  header.size = 14 + 40 + (img24.width*img24.height*3);
  header.junk = 0;
  header.offset = 14 + 40;

  DIBHEADER dibheader;
  dibheader.header_size = 40;
  dibheader.width = img24.width;
  dibheader.height = img24.height;
  dibheader.color_panes = 1;
  dibheader.color_depth = 24;
  dibheader.compression = 0;
  dibheader.image_size = img24.width*img24.height*3;
  dibheader.hres = 0;
  dibheader.vres = 0;
  dibheader.number_colors = 0;
  dibheader.number_important_colors = 0;

  FILE * fp = fopen(file_name, "w+");
  fwrite(header.name, 2, 1, fp);
  fwrite(&header.size, 3*sizeof(uint32_t), 1, fp);
  fwrite(&dibheader.header_size, 3*sizeof(uint32_t), 1, fp);
  fwrite(&dibheader.color_panes, 2*sizeof(uint16_t), 1, fp);
  fwrite(&dibheader.compression, 6*sizeof(uint32_t), 1, fp);
 
  // y loop is backward because pixels must be bottom -> up
  for(int y = img24.height-1; y >= 0; y--){
    for(int x = 0; x < img24.width; x++){
      fwrite(&img24.pixels[y][x], sizeof(RGB), 1, fp);
    }
  }

  fclose(fp);
}

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
