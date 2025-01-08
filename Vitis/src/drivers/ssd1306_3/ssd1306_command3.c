/*
 * ssd1306_command.c
 *
 *  Created on: 2024. 9. 25.
 *      Author: HARMAN-18
 */

#include "ssd1306_command3.h"
#include "ssd13063.h"
// Screenbuffer
static uint8_t SSD1306_Buffer3[SSD1306_BUFFER_SIZE];

// Screen object
static SSD1306_t3 SSD13063;




// Send a byte to the command register
void ssd1306_WriteCommand3(uint8_t byte) {
	uint8_t buffer[2] = {0};
		buffer[0] = 0x00;
		buffer[1] = byte;

		XIic_Send(XPAR_IIC_0_BASEADDR, OLED_SLAVE_ADDRESS, buffer, 2, XIIC_STOP);
}

// Send data
void ssd1306_WriteData3(uint8_t* data_buffer, size_t buffer_size) {
//	if(buffer_size > 16) {
//		//xil_printf("oversize!!!\n");
//		return ;
//	}

	uint8_t Buffer[128 + 1]={0};
		Buffer[0] = 0x40;
		for(uint16_t i = 0; i < buffer_size; i++) {
			Buffer[i + 1] = data_buffer[i];
		}

		XIic_Send(XPAR_IIC_0_BASEADDR, OLED_SLAVE_ADDRESS, Buffer, buffer_size+1 , XIIC_STOP);
}

/* Fills the Screenbuffer with values from a given buffer of a fixed length */
SSD1306_Error_t3 ssd1306_FillBuffer3(uint8_t* buf, uint32_t len) {
    SSD1306_Error_t3 ret = SSD1306_ERR3;
    if (len <= SSD1306_BUFFER_SIZE) {
        memcpy(SSD1306_Buffer3,buf,len);
        ret = SSD1306_OK3;
    }
    return ret;
}



/* Initialize the oled screen */
void ssd1306_Init3(void) {
    // Reset OLED
    //ssd1306_Reset();

    // Wait for the screen to boot
    usleep(200000);

    // Init OLED
    ssd1306_SetDisplayOn3(0); //display off

    ssd1306_WriteCommand3(0x20); //Set Memory Addressing Mode
    ssd1306_WriteCommand3(0x00); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode;
                                // 10b,Page Addressing Mode (RESET); 11b,Invalid

    ssd1306_WriteCommand3(0xB0); //Set Page Start Address for Page Addressing Mode,0-7

#ifdef SSD1306_MIRROR_VERT
    ssd1306_WriteCommand3(0xC0); // Mirror vertically
#else
    ssd1306_WriteCommand3(0xC8); //Set COM Output Scan Direction
#endif

    ssd1306_WriteCommand3(0x00); //---set low column address
    ssd1306_WriteCommand3(0x10); //---set high column address

    ssd1306_WriteCommand3(0x40); //--set start line address - CHECK

    ssd1306_SetContrast3(0xFF);

#ifdef SSD1306_MIRROR_HORIZ
    ssd1306_WriteCommand3(0xA0); // Mirror horizontally
#else
    ssd1306_WriteCommand3(0xA1); //--set segment re-map 0 to 127 - CHECK
#endif

#ifdef SSD1306_INVERSE_COLOR
    ssd1306_WriteCommand3(0xA7); //--set inverse color
#else
    ssd1306_WriteCommand3(0xA6); //--set normal color
#endif

// Set multiplex ratio.
#if (SSD1306_HEIGHT == 128)
    // Found in the Luma Python lib for SH1106.
    ssd1306_WriteCommand3(0xFF);
#else
    ssd1306_WriteCommand3(0xA8); //--set multiplex ratio(1 to 64) - CHECK
#endif

#if (SSD1306_HEIGHT == 32)
    ssd1306_WriteCommand3(0x1F); //
#elif (SSD1306_HEIGHT == 64)
    ssd1306_WriteCommand3(0x3F); //
#elif (SSD1306_HEIGHT == 128)
    ssd1306_WriteCommand3(0x3F); // Seems to work for 128px high displays too.
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

    ssd1306_WriteCommand3(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content

    ssd1306_WriteCommand3(0xD3); //-set display offset - CHECK
    ssd1306_WriteCommand3(0x00); //-not offset

    ssd1306_WriteCommand3(0xD5); //--set display clock divide ratio/oscillator frequency
    ssd1306_WriteCommand3(0xF0); //--set divide ratio

    ssd1306_WriteCommand3(0xD9); //--set pre-charge period
    ssd1306_WriteCommand3(0x22); //

    ssd1306_WriteCommand3(0xDA); //--set com pins hardware configuration - CHECK
#if (SSD1306_HEIGHT == 32)
    ssd1306_WriteCommand3(0x02);
#elif (SSD1306_HEIGHT == 64)
    ssd1306_WriteCommand3(0x12);
#elif (SSD1306_HEIGHT == 128)
    ssd1306_WriteCommand3(0x12);
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

    ssd1306_WriteCommand3(0xDB); //--set vcomh
    ssd1306_WriteCommand3(0x20); //0x20,0.77xVcc

    ssd1306_WriteCommand3(0x8D); //--set DC-DC enable
    ssd1306_WriteCommand3(0x14); //
    ssd1306_SetDisplayOn3(1); //--turn on SSD1306 panel

    // Clear screen
    ssd1306_Fill3(Black3);
   // ssd1306_Fill2(White2);
    // Flush buffer to screen
    ssd1306_UpdateScreen3();
   // sleep(1);
    // Set default values for screen object
    SSD13063.CurrentX3 = 0;
    SSD13063.CurrentY3 = 0;

    SSD13063.Initialized3 = 1;
}

/* Fill the whole screen with the given color */
void ssd1306_Fill3(SSD1306_COLOR3 color) {
	memset(SSD1306_Buffer3, (color == Black3) ? 0x00 : 0xFF, sizeof(SSD1306_Buffer3));
//	uint16_t bufferSize = 128 * 64 / 8;  // 8비트 버퍼 크기 계산
//	uint8_t fillValue = (color == Black) ? 0x00 : 0xFF;
//
//	for (uint16_t i = 0; i < bufferSize; i++) {
//		SSD1306_Buffer[i] = fillValue;
//	}
}

/* Write the screenbuffer with changed to the screen */
void ssd1306_UpdateScreen3(void) {
    // Write data to each page of RAM. Number of pages
    // depends on the screen height:
    //
    //  * 32px   ==  4 pages
    //  * 64px   ==  8 pages
    //  * 128px  ==  16 pages
    for(uint8_t i = 0; i < SSD1306_HEIGHT/8; i++) {

        ssd1306_WriteCommand3(0xB0 + i); // Set the current RAM page address.

        ssd1306_WriteCommand3(0x00 + SSD1306_X_OFFSET_LOWER);
        ssd1306_WriteCommand3(0x10 + SSD1306_X_OFFSET_UPPER);
//      ssd1306_WriteData(&SSD1306_Buffer[SSD1306_WIDTH*i],SSD1306_WIDTH);
//        for(uint8_t j = 0; j < 16;j++){
			ssd1306_WriteData3(&SSD1306_Buffer3[SSD1306_WIDTH * i], 128);
 //       }

    }
}

/*
 * Draw one pixel in the screenbuffer
 * X => X Coordinate
 * Y => Y Coordinate
 * color => Pixel color
 */
void ssd1306_DrawPixel3(uint8_t x, uint8_t y, SSD1306_COLOR3 color) {
    if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {
        // Don't write outside the buffer
        return;
    }

    // Draw in the right color
    if(color == White3) {
        SSD1306_Buffer3[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
    } else {
        SSD1306_Buffer3[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}

/*
 * Draw 1 char to the screen buffer
 * ch       => char om weg te schrijven
 * Font     => Font waarmee we gaan schrijven
 * color    => Black or White
 */
char ssd1306_WriteChar3(char ch, SSD1306_Font_t3 Font, SSD1306_COLOR3 color) {
    uint32_t i, b, j;

    // Check if character is valid
    if (ch < 32 || ch > 126)
        return 0;

    // Check remaining space on current line
    if (SSD1306_WIDTH < (SSD13063.CurrentX3 + Font.width3) ||
        SSD1306_HEIGHT < (SSD13063.CurrentY3 + Font.height3))
    {
        // Not enough space on current line
        return 0;
    }

    // Use the font to write
    for(i = 0; i < Font.height3; i++) {
        b = Font.data3[(ch - 32) * Font.height3 + i];
        for(j = 0; j < Font.width3; j++) {
            if((b << j) & 0x8000)  {
                ssd1306_DrawPixel3(SSD13063.CurrentX3 + j, (SSD13063.CurrentY3 + i), (SSD1306_COLOR3) color);
            } else {
                ssd1306_DrawPixel3(SSD13063.CurrentX3 + j, (SSD13063.CurrentY3 + i), (SSD1306_COLOR3)!color);
            }
        }
    }

    // The current space is now taken
    SSD13063.CurrentX3 += Font.char_width3 ? Font.char_width3[ch - 32] : Font.width3;

    // Return written char for validation
    return ch;
}

/* Write full string to screenbuffer */
char ssd1306_WriteString3(char* str, SSD1306_Font_t3 Font, SSD1306_COLOR3 color) {
    while (*str) {
        if (ssd1306_WriteChar3(*str, Font, color) != *str) {
            // Char could not be written
            return *str;
        }
        str++;
    }

    // Everything ok
    return *str;
}

/* Position the cursor */
void ssd1306_SetCursor3(uint8_t x, uint8_t y) {
    SSD13063.CurrentX3 = x;
    SSD13063.CurrentY3 = y;
}

///* Draw a bitmap */
//void ssd1306_DrawBitmap2(uint8_t x, uint8_t y, const unsigned char* bitmap, uint8_t w, uint8_t h, SSD1306_COLOR2 color) {
//    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
//    uint8_t byte = 0;
//
//    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {
//        return;
//    }
//
//    for (uint8_t j = 0; j < h; j++, y++) {
//        for (uint8_t i = 0; i < w; i++) {
//            if (i & 7) {
//                byte <<= 1;
//            } else {
//                byte = (*(const unsigned char *)(&bitmap[j * byteWidth + i / 8]));
//            }
//
//            if (byte & 0x80) {
//                ssd1306_DrawPixel2(x + i, y, color);
//            }
//        }
//    }
//    return;
//}

void ssd1306_SetContrast3(const uint8_t value) {
    const uint8_t kSetContrastControlRegister = 0x81;
    ssd1306_WriteCommand3(kSetContrastControlRegister);
    ssd1306_WriteCommand3(value);
}

void ssd1306_SetDisplayOn3(const uint8_t on) {
    uint8_t value;
    if (on) {
        value = 0xAF;   // Display on
        SSD13063.DisplayOn3 = 1;
    } else {
        value = 0xAE;   // Display off
        SSD13063.DisplayOn3 = 0;
    }
    ssd1306_WriteCommand3(value);
}
