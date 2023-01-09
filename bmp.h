#pragma once
#include <stdint.h>

// https://en.wikipedia.org/wiki/BMP_file_format
typedef struct{
  char name[2];    // 1+1 Bytes
  uint32_t size;   // 4 Bytes
  int32_t junk;    // 2+2 Bytes
  uint32_t offset; // 4 Bytes
} BMPHEADER;

typedef struct{
  uint32_t header_size;   		// 4 Bytes
  int32_t width;          		// 4 Bytes
  int32_t height;         		// 4 Bytes
  uint16_t color_panes;   		// 2 Bytes
  uint16_t color_depth;   		// 2 Bytes
  uint32_t compression;   		// 4 Bytes
  uint32_t image_size;			// 4 Bytes
  int32_t hres;				// 4 Bytes
  int32_t vres;				// 4 Bytes
  uint32_t number_colors;		// 4 Bytes
  uint32_t number_important_colors;	// 4 Bytes
} DIBHEADER;

// unsigned char is 8 bits (0-255)
typedef struct{
  unsigned char B; 
  unsigned char G; 
  unsigned char R; 
} RGB;

typedef struct{
  unsigned char B;
  unsigned char G;
  unsigned char R;
  unsigned char A;
} RGBA;

typedef struct{
  RGB ** pixels;
  int32_t width;
  int32_t height;
} IMAGE;

typedef struct{
  RGBA ** pixels;
  int32_t width;
  int32_t height;
} IMAGE32;
