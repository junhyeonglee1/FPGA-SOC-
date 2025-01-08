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

#include "ssd1306_conf_template2.h"
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
    Black2 = 0x00, // Black color, no pixel
    White2 = 0x01  // Pixel is set. Color depends on OLED
} SSD1306_COLOR2;

typedef enum {
    SSD1306_OK2 = 0x00,
    SSD1306_ERR2 = 0x01  // Generic error.
} SSD1306_Error_t2;

typedef struct {
    uint16_t CurrentX2;
    uint16_t CurrentY2;
    uint8_t Initialized2;
    uint8_t DisplayOn2;
} SSD1306_t2;

typedef struct {
    uint8_t x2;
    uint8_t y2;
} SSD1306_VERTEX2;

typedef struct {
	const uint8_t width2;                /**< Font width in pixels */
	const uint8_t height2;               /**< Font height in pixels */
	const uint16_t *const data2;         /**< Pointer to font data array */
    const uint8_t *const char_width2;    /**< Proportional character width in pixels (NULL for monospaced) */
} SSD1306_Font_t2;

// Procedure definitions
void ssd1306_Init2(void);
void ssd1306_Fill2(SSD1306_COLOR2 color);
void ssd1306_UpdateScreen2(void);
void ssd1306_DrawPixel2(uint8_t x, uint8_t y, SSD1306_COLOR2 color);
char ssd1306_WriteChar2(char ch, SSD1306_Font_t2 Font, SSD1306_COLOR2 color);
char ssd1306_WriteString2(char* str, SSD1306_Font_t2 Font, SSD1306_COLOR2 color);
void ssd1306_SetCursor2(uint8_t x, uint8_t y);
void ssd1306_Line2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR2 color);
void ssd1306_DrawArc2(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR2 color);
void ssd1306_DrawArcWithRadiusLine2(uint8_t x, uint8_t y, uint8_t radius, uint16_t start_angle, uint16_t sweep, SSD1306_COLOR2 color);
void ssd1306_DrawCircle2(uint8_t par_x, uint8_t par_y, uint8_t par_r, SSD1306_COLOR2 color);
void ssd1306_FillCircle2(uint8_t par_x,uint8_t par_y,uint8_t par_r,SSD1306_COLOR2 par_color);
void ssd1306_Polyline2(const SSD1306_VERTEX2 *par_vertex, uint16_t par_size, SSD1306_COLOR2 color);
void ssd1306_DrawRectangle2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR2 color);
void ssd1306_FillRectangle2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, SSD1306_COLOR2 color);

/**
 * @brief Invert color of pixels in rectangle (include border)
 *
 * @param x1 X Coordinate of top left corner
 * @param y1 Y Coordinate of top left corner
 * @param x2 X Coordinate of bottom right corner
 * @param y2 Y Coordinate of bottom right corner
 * @return SSD1306_Error_t status
 */
SSD1306_Error_t2 ssd1306_InvertRectangle2(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);

void ssd1306_DrawBitmap2(uint8_t x, uint8_t y, const unsigned char* bitmap, uint8_t w, uint8_t h, SSD1306_COLOR2 color);

/**
 * @brief Sets the contrast of the display.
 * @param[in] value contrast to set.
 * @note Contrast increases as the value increases.
 * @note RESET = 7Fh.
 */
void ssd1306_SetContrast2(const uint8_t value);

/**
 * @brief Set Display ON/OFF.
 * @param[in] on 0 for OFF, any for ON.
 */
void ssd1306_SetDisplayOn2(const uint8_t on);

/**
 * @brief Reads DisplayOn state.
 * @return  0: OFF.
 *          1: ON.
 */
uint8_t ssd1306_GetDisplayOn2();

// Low-level procedures
//void ssd1306_Reset(void);
void ssd1306_WriteCommand2(uint8_t byte);
void ssd1306_WriteData2(uint8_t* buffer, size_t buff_size);
SSD1306_Error_t2 ssd1306_FillBuffer2(uint8_t* buf, uint32_t len);

void ssd1306_BPM_animation();
void ssd1306_thermometer_animation();
void ssd1306_Personal_information_animation();
void ssd1306_pedometer_animation();
void graph_animation();



