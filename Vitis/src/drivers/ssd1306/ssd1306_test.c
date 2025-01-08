/*
 * ssd1306_test.c
 *
 *  Created on: 2024. 9. 25.
 *      Author: HARMAN-18
 */
#include <string.h>
#include <stdio.h>
//#include "ssd1306_command.h"
#include "ssd1306_test.h"
#include "ssd1306_font.h"
#include <stdbool.h>

void ssd1306_num_write(uint8_t num,SSD1306_Font_t Font, SSD1306_COLOR color);

const uint8_t BPM_animation1[][128] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,4,0,1,137,12,0,1,201,12,0,2,81,10,0,62,113,146,124,0,49,147,128,0,48,145,128,0,32,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,4,0,1,137,12,0,1,201,12,0,2,81,10,0,62,113,146,124,0,49,147,128,0,48,145,128,0,32,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,4,0,1,137,12,0,1,201,12,0,2,81,10,0,62,113,146,124,0,49,147,128,0,48,145,128,0,32,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,4,0,1,137,12,0,1,201,12,0,2,81,10,0,62,113,146,124,0,49,147,128,0,48,145,128,0,32,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,4,0,1,137,12,0,1,201,12,0,2,81,10,0,30,113,146,124,0,49,147,128,0,48,145,128,0,32,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,4,0,1,137,12,0,1,201,12,0,2,81,10,0,2,113,146,124,0,49,147,128,0,48,145,128,0,32,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,9,4,0,0,137,12,0,0,201,12,0,0,81,10,0,0,113,146,124,0,49,147,128,0,48,145,128,0,32,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,14,0,0,0,9,0,0,0,9,12,0,0,9,12,0,0,25,14,0,0,17,26,0,0,17,26,124,0,16,147,192,0,48,145,128,0,48,177,0,0,0,160,0,0,0,224,0,0,0,224,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,14,0,0,0,9,0,0,0,1,12,0,0,1,12,0,0,1,14,0,0,1,26,0,0,1,26,124,0,0,147,192,0,0,145,128,0,0,177,0,0,0,160,0,0,0,224,0,0,0,224,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,2,0,0,0,2,0,0,0,1,0,0,0,1,12,0,0,1,12,0,0,1,14,0,0,1,26,0,0,1,26,124,0,0,147,192,0,0,145,128,0,0,177,0,0,0,160,0,0,0,224,0,0,0,224,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,12,0,0,0,12,0,0,0,10,0,0,0,18,124,0,0,19,128,0,0,17,128,0,0,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,12,0,0,0,12,0,0,0,10,0,0,0,18,124,0,0,19,128,0,0,17,128,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,124,0,0,3,192,0,0,1,128,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,0,0,1,128,0,0,1,0,0,0,2,0,0,0,62,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,0,0,1,128,0,0,1,200,0,0,2,80,0,0,62,112,0,0,0,48,0,0,0,48,0,0,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,4,0,0,0,4,0,0,0,8,0,0,0,8,0,0,0,136,0,0,1,136,0,0,1,200,0,0,2,80,0,0,62,112,0,0,0,48,0,0,0,48,0,0,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,0,0,1,137,0,0,1,201,0,0,2,81,0,0,62,113,128,0,0,49,128,0,0,48,128,0,0,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,14,0,0,0,9,0,0,0,137,0,0,1,137,0,0,1,217,0,0,2,81,0,0,62,81,0,0,0,48,128,0,0,48,128,0,0,48,128,0,0,0,128,0,0,0,224,0,0,0,224,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,14,0,0,0,9,0,0,0,137,0,0,1,137,8,0,1,217,8,0,2,81,24,0,62,81,24,0,0,48,144,0,0,48,144,0,0,48,176,0,0,0,160,0,0,0,224,0,0,0,224,0,0,0,64,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,4,0,1,137,12,0,1,201,12,0,2,81,10,0,62,113,146,0,0,49,147,0,0,48,144,0,0,32,160,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,4,0,1,137,12,0,1,201,12,0,2,81,10,0,62,113,146,64,0,49,147,128,0,48,145,128,0,32,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,4,0,1,137,12,0,1,201,12,0,2,81,10,0,62,113,146,120,0,49,147,128,0,48,145,128,0,32,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,4,0,1,137,12,0,1,201,12,0,2,81,10,0,62,113,146,124,0,49,147,128,0,48,145,128,0,32,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,4,0,1,137,12,0,1,201,12,0,2,81,10,0,62,113,146,124,0,49,147,128,0,48,145,128,0,32,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,6,0,0,0,11,0,0,0,11,0,0,0,137,4,0,1,137,12,0,1,201,12,0,2,81,10,0,62,113,146,124,0,49,147,128,0,48,145,128,0,32,161,0,0,0,160,0,0,0,224,0,0,0,192,0,0,0,192,0,0,0,64,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

//------------------------------------------------------------------------------
// Table generated by LCD Assistant
// http://en.radzio.dxp.pl/bitmap_converter/
//------------------------------------------------------------------------------
const unsigned char garfield_128x64 [] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFF, 0xF8, 0x7F, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xCF, 0xFF, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFB, 0xE3, 0xFF, 0xF3, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xC0, 0xF3, 0xFF, 0xF8, 0xE0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00, 0x1F, 0xD9, 0xFC, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x0D, 0x00, 0x0F, 0x00, 0x1E, 0x0C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0C, 0x0C, 0x0E, 0x1F, 0xF8, 0x03, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x03, 0x87, 0xF0, 0x07, 0x00, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x18, 0x3B, 0x80, 0x18, 0x00, 0x30, 0xC3, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFE, 0x00, 0x60, 0x00, 0x18, 0xC3, 0x01, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3F, 0xFC, 0x01, 0x80, 0x00, 0x0F, 0xC3, 0x8F, 0xC0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x07, 0xF0, 0x03, 0x00, 0x00, 0x0C, 0x07, 0xF0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0F, 0xE0, 0x0C, 0x00, 0x00, 0x0C, 0x07, 0xFF, 0xF8, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x38, 0xC0, 0x18, 0x00, 0x00, 0x08, 0x0F, 0xFF, 0xF0, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x71, 0x80, 0x30, 0x00, 0x00, 0x08, 0x0F, 0xFC, 0xFC, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xF7, 0x00, 0x60, 0x00, 0x00, 0x18, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0xFF, 0x00, 0x60, 0x00, 0x00, 0x18, 0x7F, 0xFE, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0xFF, 0x00, 0xC0, 0x00, 0x00, 0x30, 0xFF, 0x1F, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x83, 0xE0, 0xC0, 0x00, 0x00, 0x60, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x07, 0x03, 0x1F, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x03, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0E, 0x01, 0x00, 0xE7, 0xC0, 0x03, 0x80, 0x00, 0x0F, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0x01, 0x80, 0xE0, 0x00, 0x06, 0x00, 0x00, 0xFF, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0x83, 0x7F, 0xF0, 0x00, 0x38, 0x00, 0x26, 0xFF, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xDC, 0x18, 0x1F, 0x87, 0xE0, 0x00, 0x26, 0xEF, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xB8, 0x0E, 0x18, 0x00, 0x30, 0x00, 0x04, 0xCF, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0x30, 0x0F, 0xC0, 0x00, 0x18, 0x00, 0x00, 0x8F, 0x80, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x07, 0x30, 0x38, 0x70, 0x00, 0x18, 0x00, 0x00, 0x0F, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x07, 0x18, 0x00, 0x1F, 0x00, 0x18, 0x3B, 0x80, 0x0E, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x8E, 0x00, 0x03, 0x80, 0x70, 0x1F, 0xF8, 0x1C, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x03, 0xE0, 0x1F, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x7F, 0x86, 0x00, 0x3F, 0x1F, 0x07, 0xFF, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0F, 0xC3, 0x00, 0x00, 0x3F, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x3F, 0xC7, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0xE0, 0x07, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x07, 0xC0, 0x3F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0xA4, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x70, 0x00, 0x00, 0x16, 0x01, 0xC0, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x1E, 0x01, 0xC0, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x01, 0xC0, 0x00, 0x00, 0x0C, 0x01, 0x80, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x00, 0x04, 0x01, 0xF3, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x00, 0x0C, 0x01, 0xEF, 0xF7, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0E, 0x00, 0x00, 0x00, 0x18, 0x00, 0x07, 0xF0, 0x60, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x00, 0x18, 0x00, 0x07, 0x80, 0x70, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x30, 0x00, 0x06, 0x04, 0xF0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00, 0x60, 0x00, 0x0C, 0x1C, 0xF0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0xC0, 0x00, 0x1F, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x01, 0x80, 0x00, 0x01, 0xFD, 0xF0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0xFD, 0xF0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x07, 0x00, 0x00, 0x01, 0xC1, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x07, 0x00, 0x00, 0x03, 0x81, 0xE0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0C, 0x00, 0x00, 0x07, 0x00, 0x00, 0x07, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x39, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0x80, 0x00, 0x01, 0xF0, 0x01, 0xE3, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x1F, 0x03, 0x8D, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x1E, 0x00, 0x00, 0x03, 0xFC, 0x3D, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x03, 0xC0, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xC0, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xF1, 0xC0, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xE0, 0xC0, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xE0, 0xC0, 0x3F, 0x9E, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char github_logo_64x64[] = {
0x00, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0x80, 0x00, 0x00,
0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFC, 0x00, 0x00,
0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00,
0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00,
0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00,
0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00,
0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x03, 0xFE, 0x3F, 0xFF, 0xFF, 0xFC, 0x7F, 0xC0,
0x07, 0xFE, 0x07, 0xFF, 0xFF, 0xE0, 0x7F, 0xE0, 0x07, 0xFE, 0x01, 0xF8, 0x1F, 0xC0, 0x3F, 0xE0,
0x0F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF0, 0x0F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF0,
0x1F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF8, 0x1F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xF8,
0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFC, 0x3F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFC,
0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFC, 0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE,
0x7F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE, 0x7F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFE,
0x7F, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFE, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF,
0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF,
0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF,
0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF,
0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF,
0xFF, 0xF0, 0x00, 0x00, 0x00, 0x00, 0x0F, 0xFF, 0x7F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE,
0x7F, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xFE, 0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFE,
0x7F, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFE, 0x7F, 0xFE, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFC,
0x3F, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFC, 0x3F, 0xFF, 0xC0, 0x00, 0x00, 0x01, 0xFF, 0xFC,
0x1F, 0x9F, 0xE0, 0x00, 0x00, 0x07, 0xFF, 0xF8, 0x1F, 0x87, 0xFC, 0x00, 0x00, 0x3F, 0xFF, 0xF8,
0x0F, 0xC3, 0xFF, 0xC0, 0x01, 0xFF, 0xFF, 0xF0, 0x0F, 0xE1, 0xFF, 0x80, 0x01, 0xFF, 0xFF, 0xF0,
0x07, 0xF1, 0xFF, 0x80, 0x00, 0xFF, 0xFF, 0xE0, 0x07, 0xF0, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xE0,
0x03, 0xF8, 0x3F, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0x01, 0xF8, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x80,
0x00, 0xFC, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0xFE, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00,
0x00, 0x7F, 0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00, 0x00, 0x3F, 0xFF, 0x00, 0x00, 0xFF, 0xFC, 0x00,
0x00, 0x0F, 0xFF, 0x00, 0x00, 0xFF, 0xF0, 0x00, 0x00, 0x07, 0xFF, 0x00, 0x00, 0xFF, 0xE0, 0x00,
0x00, 0x03, 0xFF, 0x00, 0x00, 0xFF, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00,
0x00, 0x00, 0x3F, 0x00, 0x00, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x0F, 0x00, 0x00, 0xF0, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

void ssd1306_progressbar()
{
	ssd1306_Fill(Black);

	ssd1306_SetCursor(30, 2);
	ssd1306_WriteString("BOOTING", Font_7x10, White);

	ssd1306_Line(0,12,128,12, White);

//	ssd1306_DrawRectangle(4,)
//	ssd1306_FillRectangle();
}





void ssd1306_TestBorder() {
    ssd1306_Fill(Black);

    uint8_t x = 0;
    uint8_t y = 0;
    do {
        ssd1306_DrawPixel(x, y, Black);

        if((y == 0) && (x < (SSD1306_WIDTH-1)))
            x++;
        else if((x == (SSD1306_WIDTH-1)) && (y < (SSD1306_HEIGHT-1)))
            y++;
        else if((y == (SSD1306_HEIGHT-1)) && (x > 0))
            x--;
        else
            y--;

        ssd1306_DrawPixel(x, y, White);
        ssd1306_UpdateScreen();

        usleep(5000);
    } while(x > 0 || y > 0);

    usleep(1000000);
}

void ssd1306_TestFonts1() {
    uint8_t y = 0;
    ssd1306_Fill(Black);

    #ifdef SSD1306_INCLUDE_FONT_16x26
    ssd1306_SetCursor(2, y);
    ssd1306_WriteString("Font 16x26", Font_16x26, White);
    y += 26;
    #endif

    #ifdef SSD1306_INCLUDE_FONT_11x18
    ssd1306_SetCursor(2, y);
    ssd1306_WriteString("Font 11x18", Font_11x18, White);
    y += 18;
    #endif

    #ifdef SSD1306_INCLUDE_FONT_7x10
    ssd1306_SetCursor(2, y);
    ssd1306_WriteString("Font 7x10", Font_7x10, White);
    y += 10;
    #endif

    #ifdef SSD1306_INCLUDE_FONT_6x8
    ssd1306_SetCursor(2, y);
    ssd1306_WriteString("Font 6x8", Font_6x8, White);
    #endif

    ssd1306_UpdateScreen();
}

/*
 * This test shows how an 128x64 px OLED can replace a 0802 LCD.
 */
void ssd1306_TestFonts2() {
#ifdef SSD1306_INCLUDE_FONT_16x24
    uint8_t x1, y1, x2, y2;

    ssd1306_Fill(Black);

    ssd1306_SetCursor(0, 4);
    ssd1306_WriteString("18.092.5", Font_16x24, White);
    ssd1306_SetCursor(0, 4+24+8);
    ssd1306_WriteString("RIT+1000", Font_16x24, White);

    // underline
    x1 = 6*16;
    y1 = 4+24+8+24;
    x2 = x1+16;
    y2 = y1+2;
    ssd1306_FillRectangle(x1, y1, x2, y2, White);

    ssd1306_UpdateScreen();
#endif
}

/*
 * Test of proportional (non-monospaced) font.
 */
void ssd1306_TestFonts3() {
    ssd1306_Fill(Black);
#ifdef SSD1306_INCLUDE_FONT_16x15
    ssd1306_SetCursor(4, 4);
    ssd1306_WriteString("Proportional", Font_16x15, White);
    ssd1306_SetCursor(4, 24);
    ssd1306_WriteString("text... Sweet!", Font_16x15, White);
    ssd1306_SetCursor(4, 44);
    ssd1306_WriteString("3.1415  04:20", Font_16x15, White);
#elif defined(SSD1306_INCLUDE_FONT_11x18)
    ssd1306_SetCursor(4, 4);
    ssd1306_WriteString("Skip test", Font_11x18, White);
    ssd1306_SetCursor(4, 24);
    ssd1306_WriteString("Font not", Font_11x18, White);
    ssd1306_SetCursor(4, 44);
    ssd1306_WriteString("included!", Font_11x18, White);
#endif
    ssd1306_UpdateScreen();
}

void ssd1306_TestFPS() {
//    ssd1306_Fill(White);
//
//    //uint32_t start = HAL_GetTick();
//    uint32_t end = start;
//    int fps = 0;
//    char message[] = "ABCDEFGHIJK";
//
//    ssd1306_SetCursor(2,0);
//    ssd1306_WriteString("Testing...", Font_11x18, Black);
//    ssd1306_SetCursor(2, 18*2);
//    ssd1306_WriteString("0123456789A", Font_11x18, Black);
//
//    do {
//        ssd1306_SetCursor(2, 18);
//        ssd1306_WriteString(message, Font_11x18, Black);
//        ssd1306_UpdateScreen();
//
//        char ch = message[0];
//        memmove(message, message+1, sizeof(message)-2);
//        message[sizeof(message)-2] = ch;
//
//        fps++;
//        //end = HAL_GetTick();
//    } while((end - start) < 5000);
//
//    HAL_Delay(5000);
//
//    char buff[64];
//    fps = (float)fps / ((end - start) / 1000.0);
//    snprintf(buff, sizeof(buff), "~%d FPS", fps);
//
//    ssd1306_Fill(White);
//    ssd1306_SetCursor(2, 2);
//    ssd1306_WriteString(buff, Font_11x18, Black);
//    ssd1306_UpdateScreen();
}

void ssd1306_TestLine() {

  ssd1306_Line(1,1,SSD1306_WIDTH - 1,SSD1306_HEIGHT - 1,White);
  ssd1306_Line(SSD1306_WIDTH - 1,1,1,SSD1306_HEIGHT - 1,White);
  ssd1306_UpdateScreen();
  return;
}



void ssd1306_TestRectangle() {
  uint32_t delta;

  for(delta = 0; delta < 5; delta ++) {
    ssd1306_DrawRectangle(1 + (5*delta),1 + (5*delta) ,SSD1306_WIDTH-1 - (5*delta),SSD1306_HEIGHT-1 - (5*delta),White);
  }
  ssd1306_UpdateScreen();
  return;
}

void ssd1306_TestRectangleFill() {
  ssd1306_FillRectangle(31, 1, 65, 35, White);
  ssd1306_FillRectangle(10, 45, 70, 60, White);
  ssd1306_FillRectangle(75, 10, 100, 45, White);
  ssd1306_FillRectangle(55, 30, 80, 55, Black);
  ssd1306_UpdateScreen();
}

void ssd1306_display_BPM_SPO2(){
	ssd1306_SetCursor(2, 1);
	ssd1306_WriteString("ECG", Font_7x10, White);
	ssd1306_SetCursor(2, 11);
	ssd1306_WriteString("BPM", Font_7x10, White);
	ssd1306_SetCursor(66, 1);
	ssd1306_WriteString("SPO2", Font_7x10, White);
	ssd1306_SetCursor(115, 1);
	ssd1306_WriteString("%", Font_7x10, White);
	ssd1306_SetCursor(2, 33);
	ssd1306_WriteString("ECG Graph", Font_7x10, White);
	ssd1306_SetCursor(25, 5);
	ssd1306_WriteString("73", Font_16x26, White);
	ssd1306_SetCursor(25, 5);
	ssd1306_WriteString("73", Font_16x26, White);
	ssd1306_InvertRectangle(0,0,60,29);

	ssd1306_InvertRectangle(66,0,128,29);

	ssd1306_UpdateScreen();

}

void ssd1306_display_step_cnt_UI(int step_count, int distance, int calorie){
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 1);
	ssd1306_WriteString("Activity", Font_7x10, White);
	ssd1306_SetCursor(2, 15);
	ssd1306_WriteString("Count: ", Font_7x10, White);

	ssd1306_SetCursor(51, 15);
	ssd1306_num_write(step_count/100 ,Font_7x10, White);
	ssd1306_SetCursor(58, 15);
	ssd1306_num_write(step_count/10 % 10 ,Font_7x10, White);
	ssd1306_SetCursor(65, 15);
	ssd1306_num_write(step_count % 10 ,Font_7x10, White);

	ssd1306_SetCursor(2, 25);
	ssd1306_WriteString("Distance: ", Font_7x10, White);
	ssd1306_SetCursor(72, 25);
	ssd1306_num_write(distance/10 %10 ,Font_7x10, White);
	ssd1306_SetCursor(79, 25);
	ssd1306_num_write(distance % 10 ,Font_7x10, White);

	ssd1306_SetCursor(2, 35);
	ssd1306_WriteString("Calories: ", Font_7x10, White);
	ssd1306_SetCursor(72, 35);
	ssd1306_num_write(calorie/100 ,Font_7x10, White);
	ssd1306_SetCursor(79, 35);
	ssd1306_num_write(calorie/10 % 10 ,Font_7x10, White);
	ssd1306_SetCursor(86, 35);
	ssd1306_num_write(calorie % 10 ,Font_7x10, White);



	ssd1306_UpdateScreen();

}

char buffer[100]; // 충분한 크기의 버퍼를 선언

void ssd1306_num_write(uint8_t num,SSD1306_Font_t Font, SSD1306_COLOR color){
	    char buffer[2]; // 숫자 하나와 널 문자를 위한 배열
	    if (num <= 9) {
	        buffer[0] = '0' + num; // 숫자를 문자로 변환
	        buffer[1] = '\0';      // 널 문자 추가
	        ssd1306_WriteString(buffer, Font, color); // 숫자 출력
	    }
	}
//	switch(num){
//	case 0: ssd1306_WriteString("0", Font, White); break;
//	case 1: ssd1306_WriteString("1", Font, White); break;
//	case 2: ssd1306_WriteString("2", Font, White); break;
//	case 3: ssd1306_WriteString("3", Font, White); break;
//	case 4: ssd1306_WriteString("4", Font, White); break;
//	case 5: ssd1306_WriteString("5", Font, White); break;
//	case 6: ssd1306_WriteString("6", Font, White); break;
//	case 7: ssd1306_WriteString("7", Font, White); break;
//	case 8: ssd1306_WriteString("8", Font, White); break;
//	case 9: ssd1306_WriteString("9", Font, White); break;
//	default : break;
//}
//}

extern int temp_amb_x100;
extern double temp_amb;

void ssd1306_display_BodyTemperature(){
	ssd1306_Fill(Black);
	static int temp_amb_low0;
	static int temp_amb_low1;
	temp_amb_low0 = temp_amb_x100 % 10;
	temp_amb_low1 = temp_amb_x100 / 10 % 10;
	static int temp_amb_high0;
	temp_amb_high0 = (int)temp_amb % 10;
	static int temp_amb_high1;
	temp_amb_high1 = (int)temp_amb / 10;

	ssd1306_SetCursor(13, 4);
	ssd1306_WriteString("Body Temp", Font_11x18, White);


	ssd1306_SetCursor(31, 32);
	ssd1306_num_write( temp_amb_high1,Font_11x18, White);
	ssd1306_SetCursor(42, 32);
	ssd1306_num_write(temp_amb_high0 ,Font_11x18, White);
	ssd1306_SetCursor(53, 32);
	ssd1306_WriteString(".", Font_11x18, White);
	ssd1306_SetCursor(64, 32);
	ssd1306_num_write(temp_amb_low1 ,Font_11x18, White);
	ssd1306_SetCursor(75, 32);
	ssd1306_num_write(temp_amb_low0,Font_11x18, White);
	ssd1306_SetCursor(86, 32);
	ssd1306_WriteString("'C", Font_11x18, White);

	ssd1306_UpdateScreen();

}
void ssd1306_display_PatienInfo_UI(){
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 1);
	ssd1306_WriteString("Patient Info", Font_7x10, White);
	ssd1306_SetCursor(5, 15);
	ssd1306_WriteString("NAME : Eric", Font_7x10, White);
	ssd1306_SetCursor(5, 25);
	ssd1306_WriteString("ROOM : 101", Font_7x10, White);
	ssd1306_SetCursor(5, 35);
	ssd1306_WriteString("Disease :CANCER", Font_7x10, White);
	ssd1306_SetCursor(5, 45);
	ssd1306_WriteString("Blood Type :RH+ B", Font_7x10, White);


	ssd1306_UpdateScreen();

}

extern int r_value_oled;
extern int beatAvg;
extern uint8_t bpm_state;
int first_update = 1;      // 처음 한 번만 화면을 업데이트하기 위한 플래그

void ssd1306_display_BPM_UI(){

	ssd1306_Fill(Black);
	ssd1306_SetCursor(10, 5);
	ssd1306_WriteString("BPM", Font_7x10, White);

	ssd1306_SetCursor(10, 20);
	ssd1306_num_write( (beatAvg -15)/10 ,Font_16x26, White);
	ssd1306_SetCursor(26, 20);
	ssd1306_num_write( (beatAvg -15)%10 ,Font_16x26, White);

	ssd1306_SetCursor(66, 5);
	ssd1306_WriteString("SPO2", Font_7x10, White);

	ssd1306_SetCursor(66, 20);
	ssd1306_num_write( r_value_oled/10 ,Font_16x26, White);
	ssd1306_SetCursor(82, 20);
	ssd1306_num_write( r_value_oled%10 ,Font_16x26, White);

	ssd1306_SetCursor(100, 40);
	ssd1306_WriteString("%", Font_7x10, White);

	ssd1306_UpdateScreen();
}


void ssd1306_BPM_graph_animation(){

	static uint8_t frame;
	ssd1306_DrawBitmap(48, 32, BPM_animation1[frame], 32, 32, 1);
	ssd1306_Line(0,49,128,49,White);
	//ssd1306_Line(79,49,128,49,White);
	frame = (frame + 1) % FRAME_COUNT;

}

void ssd1306_BPM_sensor()
{
	ssd1306_SetCursor(11, 32);
	ssd1306_WriteString("put your finger", Font_7x10, White);
	ssd1306_SetCursor(30, 42);
	ssd1306_WriteString("on sensor", Font_7x10, White);


}

void ssd1306_TestRectangleInvert() {
#ifdef SSD1306_INCLUDE_FONT_11x18
  ssd1306_SetCursor(2, 0);
  ssd1306_WriteString("Black", Font_11x18, White);
  ssd1306_SetCursor(2, 20);
  ssd1306_WriteString("on", Font_11x18, White);
  ssd1306_SetCursor(2, 40);
  ssd1306_WriteString("White", Font_11x18, White);
  ssd1306_SetCursor(66, 0);
  ssd1306_WriteString("White", Font_11x18, White);
  ssd1306_SetCursor(66, 20);
  ssd1306_WriteString("on", Font_11x18, White);
  ssd1306_SetCursor(66, 40);
  ssd1306_WriteString("Black", Font_11x18, White);
#else
  ssd1306_FillCircle(32, 32, 20, White);
  ssd1306_FillCircle(96, 32, 20, White);
#endif
  ssd1306_InvertRectangle(0,0,63,63);
  /* Test rectangle lies on one 8px page */
  ssd1306_InvertRectangle(2,58,125,60);
  ssd1306_UpdateScreen();
}

void ssd1306_TestCircle() {
  uint32_t delta;

  for(delta = 0; delta < 5; delta ++) {
    ssd1306_DrawCircle(20*delta+30, 15, 10, White);
  }

  for(delta = 0; delta < 5; delta ++) {
    ssd1306_FillCircle(23*delta+15, 40, 10, White);
  }

  ssd1306_UpdateScreen();
  return;
}

void ssd1306_TestArc() {
  ssd1306_DrawArc(30, 30, 30, 20, 270, Black);
  ssd1306_DrawArcWithRadiusLine(80, 55, 10, 30, 270, Black);
  ssd1306_UpdateScreen();
  return;
}

void ssd1306_TestPolyline() {
  SSD1306_VERTEX loc_vertex[] =
  {
      {35,40},
      {40,20},
      {45,28},
      {50,10},
      {45,16},
      {50,10},
      {53,16}
  };

  ssd1306_Polyline(loc_vertex,sizeof(loc_vertex)/sizeof(loc_vertex[0]),White);
  ssd1306_UpdateScreen();
  return;
}

void ssd1306_TestDrawBitmap()
{
    ssd1306_Fill(White);
    ssd1306_DrawBitmap(0,0,garfield_128x64,128,64,Black);
    ssd1306_UpdateScreen();
    usleep(3000000);
    ssd1306_Fill(Black);
    ssd1306_DrawBitmap(32,0,github_logo_64x64,64,64,White);
    ssd1306_UpdateScreen();
    usleep(3000000);
    ssd1306_Fill(White);
    ssd1306_DrawBitmap(32,0,github_logo_64x64,64,64,Black);
    ssd1306_UpdateScreen();
}

void ssd1306_TestAll() {
//   ssd1306_Init();

    //ssd1306_TestFPS();
    usleep(3000000);
    ssd1306_TestBorder();
    ssd1306_TestFonts1();
    usleep(3000000);

    ssd1306_TestFonts2();
    usleep(3000000);
    ssd1306_TestFonts3();
    usleep(3000000);
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();
    ssd1306_TestRectangle();
    ssd1306_TestLine();
    usleep(3000000);
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();
    ssd1306_TestRectangleFill();
    usleep(3000000);
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();
    ssd1306_TestRectangleInvert();
    usleep(3000000);
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();
    ssd1306_TestPolyline();
    usleep(3000000);
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();
    ssd1306_TestArc();
    usleep(3000000);
    ssd1306_Fill(Black);
    ssd1306_UpdateScreen();
    ssd1306_TestCircle();
    usleep(3000000);
    ssd1306_TestDrawBitmap();
    usleep(3000000);
}



