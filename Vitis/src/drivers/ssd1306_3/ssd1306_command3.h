#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>  // For memcpy
#include <_ansi.h>
#include "xparameters.h"
#include "xiic_l.h"
#include "xil_io.h"
#include "sleep.h"

//#include "ssd1306_conf_template3.h"
#define SSD1306_HEIGHT          64
#define SSD1306_WIDTH           128
#define SSD1306_BUFFER_SIZE   SSD1306_WIDTH * SSD1306_HEIGHT / 8

#ifdef SSD1306_X_OFFSET
#define SSD1306_X_OFFSET_LOWER (SSD1306_X_OFFSET & 0x0F)
#define SSD1306_X_OFFSET_UPPER ((SSD1306_X_OFFSET >> 4) & 0x07)
#else
#define SSD1306_X_OFFSET_LOWER 0
#define SSD1306_X_OFFSET_UPPER 0
#endif

typedef enum {
    Black3 = 0x00, // Black color, no pixel
    White3 = 0x01  // Pixel is set. Color depends on OLED
} SSD1306_COLOR3;

typedef enum {
    SSD1306_OK3 = 0x00,
    SSD1306_ERR3 = 0x01  // Generic error.
} SSD1306_Error_t3;

typedef struct {
    uint16_t CurrentX3;
    uint16_t CurrentY3;
    uint8_t Initialized3;
    uint8_t DisplayOn3;
} SSD1306_t3;

typedef struct {
    uint8_t x3;
    uint8_t y3;
} SSD1306_VERTEX3;

typedef struct {
	const uint8_t width3;                /**< Font width in pixels */
	const uint8_t height3;               /**< Font height in pixels */
	const uint16_t *const data3;         /**< Pointer to font data array */
    const uint8_t *const char_width3;    /**< Proportional character width in pixels (NULL for monospaced) */
} SSD1306_Font_t3;

// Procedure definitions
void ssd1306_Init3(void);
void ssd1306_Fill3(SSD1306_COLOR3 color);
void ssd1306_UpdateScreen3(void);
void ssd1306_DrawPixel3(uint8_t x, uint8_t y, SSD1306_COLOR3 color);
char ssd1306_WriteChar3(char ch, SSD1306_Font_t3 Font, SSD1306_COLOR3 color);
char ssd1306_WriteString3(char* str, SSD1306_Font_t3 Font, SSD1306_COLOR3 color);
void ssd1306_SetCursor3(uint8_t x, uint8_t y);
void ssd1306_num_write3(uint8_t num,SSD1306_Font_t3 Font, SSD1306_COLOR3 color);






void display_dht11_rtc(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second);
/**
 * @brief Invert color of pixels in rectangle (include border)
 *
 * @param x1 X Coordinate of top left corner
 * @param y1 Y Coordinate of top left corner
 * @param x2 X Coordinate of bottom right corner
 * @param y2 Y Coordinate of bottom right corner
 * @return SSD1306_Error_t status
 */
//SSD1306_Error_t2 ssd1306_InvertRectangle2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

//void ssd1306_DrawBitmap2(uint8_t x, uint8_t y, const unsigned char* bitmap, uint8_t w, uint8_t h, SSD1306_COLOR2 color);

/**
 * @brief Sets the contrast of the display.
 * @param[in] value contrast to set.
 * @note Contrast increases as the value increases.
 * @note RESET = 7Fh.
 */
void ssd1306_SetContrast3(const uint8_t value);

/**
 * @brief Set Display ON/OFF.
 * @param[in] on 0 for OFF, any for ON.
 */
void ssd1306_SetDisplayOn3(const uint8_t on);

/**
 * @brief Reads DisplayOn state.
 * @return  0: OFF.
 *          1: ON.
 */
uint8_t ssd1306_GetDisplayOn3();

// Low-level procedures
//void ssd1306_Reset(void);
void ssd1306_WriteCommand3(uint8_t byte);
void ssd1306_WriteData3(uint8_t* buffer, size_t buff_size);
SSD1306_Error_t3 ssd1306_FillBuffer3(uint8_t* buf, uint32_t len);




