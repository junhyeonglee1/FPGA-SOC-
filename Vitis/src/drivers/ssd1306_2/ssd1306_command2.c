/*
 * ssd1306_command.c
 *
 *  Created on: 2024. 9. 25.
 *      Author: HARMAN-18
 */

#include "ssd1306_command2.h"
#include "bitmap_12.h"
#include "ssd13062.h"
// Screenbuffer
static uint8_t SSD1306_Buffer2[SSD1306_BUFFER_SIZE];

// Screen object
static SSD1306_t2 SSD13062;

// Send a byte to the command register
void ssd1306_WriteCommand2(uint8_t byte) {
	uint8_t buffer[2] = {0};
		buffer[0] = 0x00;
		buffer[1] = byte;

		XIic_Send(XPAR_IIC_2_BASEADDR, OLED_SLAVE_ADDRESS, buffer, 2, XIIC_STOP);
}

// Send data
void ssd1306_WriteData2(uint8_t* data_buffer, size_t buffer_size) {
//	if(buffer_size > 16) {
//		//xil_printf("oversize!!!\n");
//		return ;
//	}

	uint8_t Buffer[128 + 1]={0};
		Buffer[0] = 0x40;
		for(uint16_t i = 0; i < buffer_size; i++) {
			Buffer[i + 1] = data_buffer[i];
		}

		XIic_Send(XPAR_IIC_2_BASEADDR, OLED_SLAVE_ADDRESS, Buffer, buffer_size+1 , XIIC_STOP);
}

/* Fills the Screenbuffer with values from a given buffer of a fixed length */
SSD1306_Error_t2 ssd1306_FillBuffer2(uint8_t* buf, uint32_t len) {
    SSD1306_Error_t2 ret = SSD1306_ERR2;
    if (len <= SSD1306_BUFFER_SIZE) {
        memcpy(SSD1306_Buffer2,buf,len);
        ret = SSD1306_OK2;
    }
    return ret;
}

//void ssd1306_Init(void){
//
//	ssd1306_WriteCommand(0xA8);
//	ssd1306_WriteCommand(0x3f);
//
//	ssd1306_WriteCommand(0xd3);
//	ssd1306_WriteCommand(0x00);
//
//	ssd1306_WriteCommand(0x40);
//
//	ssd1306_WriteCommand(0xA1);
//
//	ssd1306_WriteCommand(0xc8);
//
//	ssd1306_WriteCommand(0xda);
//	ssd1306_WriteCommand(0x02);
//
//	ssd1306_WriteCommand(0x81);
//	ssd1306_WriteCommand(0x7f);
//
//	ssd1306_WriteCommand(0xa4);
//
//	ssd1306_WriteCommand(0xa6);
//
//	ssd1306_WriteCommand(0xd5);
//	ssd1306_WriteCommand(0x80);
//
//	ssd1306_WriteCommand(0x8d);
//	ssd1306_WriteCommand(0x14);
//
//	ssd1306_WriteCommand(0xaf);
//
//}

/* Initialize the oled screen */
void ssd1306_Init2(void) {
    // Reset OLED
    //ssd1306_Reset();

    // Wait for the screen to boot
    usleep(200000);

    // Init OLED
    ssd1306_SetDisplayOn2(0); //display off

    ssd1306_WriteCommand2(0x20); //Set Memory Addressing Mode
    ssd1306_WriteCommand2(0x00); // 00b,Horizontal Addressing Mode; 01b,Vertical Addressing Mode;
                                // 10b,Page Addressing Mode (RESET); 11b,Invalid

    ssd1306_WriteCommand2(0xB0); //Set Page Start Address for Page Addressing Mode,0-7

#ifdef SSD1306_MIRROR_VERT
    ssd1306_WriteCommand2(0xC0); // Mirror vertically
#else
    ssd1306_WriteCommand2(0xC8); //Set COM Output Scan Direction
#endif

    ssd1306_WriteCommand2(0x00); //---set low column address
    ssd1306_WriteCommand2(0x10); //---set high column address

    ssd1306_WriteCommand2(0x40); //--set start line address - CHECK

    ssd1306_SetContrast2(0xFF);

#ifdef SSD1306_MIRROR_HORIZ
    ssd1306_WriteCommand(0xA0); // Mirror horizontally
#else
    ssd1306_WriteCommand2(0xA1); //--set segment re-map 0 to 127 - CHECK
#endif

#ifdef SSD1306_INVERSE_COLOR
    ssd1306_WriteCommand(0xA7); //--set inverse color
#else
    ssd1306_WriteCommand2(0xA6); //--set normal color
#endif

// Set multiplex ratio.
#if (SSD1306_HEIGHT == 128)
    // Found in the Luma Python lib for SH1106.
    ssd1306_WriteCommand(0xFF);
#else
    ssd1306_WriteCommand2(0xA8); //--set multiplex ratio(1 to 64) - CHECK
#endif

#if (SSD1306_HEIGHT == 32)
    ssd1306_WriteCommand(0x1F); //
#elif (SSD1306_HEIGHT == 64)
    ssd1306_WriteCommand2(0x3F); //
#elif (SSD1306_HEIGHT == 128)
    ssd1306_WriteCommand(0x3F); // Seems to work for 128px high displays too.
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

    ssd1306_WriteCommand2(0xA4); //0xa4,Output follows RAM content;0xa5,Output ignores RAM content

    ssd1306_WriteCommand2(0xD3); //-set display offset - CHECK
    ssd1306_WriteCommand2(0x00); //-not offset

    ssd1306_WriteCommand2(0xD5); //--set display clock divide ratio/oscillator frequency
    ssd1306_WriteCommand2(0xF0); //--set divide ratio

    ssd1306_WriteCommand2(0xD9); //--set pre-charge period
    ssd1306_WriteCommand2(0x22); //

    ssd1306_WriteCommand2(0xDA); //--set com pins hardware configuration - CHECK
#if (SSD1306_HEIGHT == 32)
    ssd1306_WriteCommand(0x02);
#elif (SSD1306_HEIGHT == 64)
    ssd1306_WriteCommand2(0x12);
#elif (SSD1306_HEIGHT == 128)
    ssd1306_WriteCommand(0x12);
#else
#error "Only 32, 64, or 128 lines of height are supported!"
#endif

    ssd1306_WriteCommand2(0xDB); //--set vcomh
    ssd1306_WriteCommand2(0x20); //0x20,0.77xVcc

    ssd1306_WriteCommand2(0x8D); //--set DC-DC enable
    ssd1306_WriteCommand2(0x14); //
    ssd1306_SetDisplayOn2(1); //--turn on SSD1306 panel

    // Clear screen
    ssd1306_Fill2(Black2);
   // ssd1306_Fill2(White2);
    // Flush buffer to screen
    ssd1306_UpdateScreen2();
   // sleep(1);
    // Set default values for screen object
    SSD13062.CurrentX2 = 0;
    SSD13062.CurrentY2 = 0;

    SSD13062.Initialized2 = 1;
}

/* Fill the whole screen with the given color */
void ssd1306_Fill2(SSD1306_COLOR2 color) {
	memset(SSD1306_Buffer2, (color == Black2) ? 0x00 : 0xFF, sizeof(SSD1306_Buffer2));
//	uint16_t bufferSize = 128 * 64 / 8;  // 8비트 버퍼 크기 계산
//	uint8_t fillValue = (color == Black) ? 0x00 : 0xFF;
//
//	for (uint16_t i = 0; i < bufferSize; i++) {
//		SSD1306_Buffer[i] = fillValue;
//	}
}

/* Write the screenbuffer with changed to the screen */
void ssd1306_UpdateScreen2(void) {
    // Write data to each page of RAM. Number of pages
    // depends on the screen height:
    //
    //  * 32px   ==  4 pages
    //  * 64px   ==  8 pages
    //  * 128px  ==  16 pages
    for(uint8_t i = 0; i < SSD1306_HEIGHT/8; i++) {

        ssd1306_WriteCommand2(0xB0 + i); // Set the current RAM page address.

        ssd1306_WriteCommand2(0x00 + SSD1306_X_OFFSET_LOWER);
        ssd1306_WriteCommand2(0x10 + SSD1306_X_OFFSET_UPPER);
//      ssd1306_WriteData(&SSD1306_Buffer[SSD1306_WIDTH*i],SSD1306_WIDTH);
//        for(uint8_t j = 0; j < 16;j++){
			ssd1306_WriteData2(&SSD1306_Buffer2[SSD1306_WIDTH * i], 128);
 //       }

    }
}

/*
 * Draw one pixel in the screenbuffer
 * X => X Coordinate
 * Y => Y Coordinate
 * color => Pixel color
 */
void ssd1306_DrawPixel2(uint8_t x, uint8_t y, SSD1306_COLOR2 color) {
    if(x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {
        // Don't write outside the buffer
        return;
    }

    // Draw in the right color
    if(color == White2) {
        SSD1306_Buffer2[x + (y / 8) * SSD1306_WIDTH] |= 1 << (y % 8);
    } else {
        SSD1306_Buffer2[x + (y / 8) * SSD1306_WIDTH] &= ~(1 << (y % 8));
    }
}

/*
 * Draw 1 char to the screen buffer
 * ch       => char om weg te schrijven
 * Font     => Font waarmee we gaan schrijven
 * color    => Black or White
 */
char ssd1306_WriteChar2(char ch, SSD1306_Font_t2 Font, SSD1306_COLOR2 color) {
    uint32_t i, b, j;

    // Check if character is valid
    if (ch < 32 || ch > 126)
        return 0;

    // Check remaining space on current line
    if (SSD1306_WIDTH < (SSD13062.CurrentX2 + Font.width2) ||
        SSD1306_HEIGHT < (SSD13062.CurrentY2 + Font.height2))
    {
        // Not enough space on current line
        return 0;
    }

    // Use the font to write
    for(i = 0; i < Font.height2; i++) {
        b = Font.data2[(ch - 32) * Font.height2 + i];
        for(j = 0; j < Font.width2; j++) {
            if((b << j) & 0x8000)  {
                ssd1306_DrawPixel2(SSD13062.CurrentX2 + j, (SSD13062.CurrentY2 + i), (SSD1306_COLOR2) color);
            } else {
                ssd1306_DrawPixel2(SSD13062.CurrentX2 + j, (SSD13062.CurrentY2 + i), (SSD1306_COLOR2)!color);
            }
        }
    }

    // The current space is now taken
    SSD13062.CurrentX2 += Font.char_width2 ? Font.char_width2[ch - 32] : Font.width2;

    // Return written char for validation
    return ch;
}

/* Write full string to screenbuffer */
char ssd1306_WriteString2(char* str, SSD1306_Font_t2 Font, SSD1306_COLOR2 color) {
    while (*str) {
        if (ssd1306_WriteChar2(*str, Font, color) != *str) {
            // Char could not be written
            return *str;
        }
        str++;
    }

    // Everything ok
    return *str;
}

/* Position the cursor */
void ssd1306_SetCursor2(uint8_t x, uint8_t y) {
    SSD13062.CurrentX2 = x;
    SSD13062.CurrentY2 = y;
}

/* Draw a bitmap */
void ssd1306_DrawBitmap2(uint8_t x, uint8_t y, const unsigned char* bitmap, uint8_t w, uint8_t h, SSD1306_COLOR2 color) {
    int16_t byteWidth = (w + 7) / 8; // Bitmap scanline pad = whole byte
    uint8_t byte = 0;

    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) {
        return;
    }

    for (uint8_t j = 0; j < h; j++, y++) {
        for (uint8_t i = 0; i < w; i++) {
            if (i & 7) {
                byte <<= 1;
            } else {
                byte = (*(const unsigned char *)(&bitmap[j * byteWidth + i / 8]));
            }

            if (byte & 0x80) {
                ssd1306_DrawPixel2(x + i, y, color);
            }
        }
    }
    return;
}

void ssd1306_SetContrast2(const uint8_t value) {
    const uint8_t kSetContrastControlRegister = 0x81;
    ssd1306_WriteCommand2(kSetContrastControlRegister);
    ssd1306_WriteCommand2(value);
}

void ssd1306_SetDisplayOn2(const uint8_t on) {
    uint8_t value;
    if (on) {
        value = 0xAF;   // Display on
        SSD13062.DisplayOn2 = 1;
    } else {
        value = 0xAE;   // Display off
        SSD13062.DisplayOn2 = 0;
    }
    ssd1306_WriteCommand2(value);
}



#define FRAME_DELAY (42)
#define FRAME_WIDTH (64)
#define FRAME_HEIGHT (64)

#define FRAME_COUNT0 (sizeof(BPM) / sizeof(BPM[0]))
#define FRAME_COUNT1 (sizeof(thermometer) / sizeof(thermometer[0]))
#define FRAME_COUNT2 (sizeof(Personal_information) / sizeof(Personal_information[0]))
#define FRAME_COUNT3 (sizeof(pedometer) / sizeof(pedometer[0]))

void graph_animation()
{
	static uint8_t frame0;
	ssd1306_Fill2(Black2);
	ssd1306_DrawBitmap2(32, 0, graph_animation1[frame0], 64, 64, 1);
	ssd1306_UpdateScreen2();
	frame0 = (frame0 + 1) % FRAME_COUNT_BPM;
	//usleep(20000);
}


// BPM MODE ANIMATION
void ssd1306_BPM_animation()
{
	static uint8_t frame0;
	ssd1306_Fill2(Black2);
	ssd1306_DrawBitmap2(32, 0, BPM[frame0], FRAME_WIDTH, FRAME_HEIGHT, 1);
	ssd1306_UpdateScreen2();
	frame0 = (frame0 + 1) % FRAME_COUNT0;
	//usleep(20000);
}

// THERMOMETER MODE ANIMATION
void ssd1306_thermometer_animation()
{
	static uint8_t frame1;
	ssd1306_Fill2(Black2);
	ssd1306_DrawBitmap2(32, 0, thermometer[frame1], FRAME_WIDTH, FRAME_HEIGHT, 1);
	ssd1306_UpdateScreen2();
	frame1 = (frame1 + 1) % FRAME_COUNT1;
	//usleep(20000);
}

// PERSONAL INFORMATION MODE ANIMATION
void ssd1306_Personal_information_animation()
{
	static uint8_t frame2;
	ssd1306_Fill2(Black2);
	ssd1306_DrawBitmap2(32, 0, Personal_information[frame2], FRAME_WIDTH, FRAME_HEIGHT, 1);
	ssd1306_UpdateScreen2();
	frame2 = (frame2 + 1) % FRAME_COUNT2;
	//usleep(20000);
}

// PEDOMETER MODE ANIMATION
void ssd1306_pedometer_animation()
{
	static uint8_t frame3;
	ssd1306_Fill2(Black2);
	ssd1306_DrawBitmap2(32, 0, pedometer[frame3], FRAME_WIDTH, FRAME_HEIGHT, 1);
	ssd1306_UpdateScreen2();
	frame3 = (frame3 + 1) % FRAME_COUNT3;
	//usleep(20000);
}

