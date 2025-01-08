#include "sleep.h"
#include <stdint.h>
#include "xparameters.h"
#include "xiic_l.h"
////#include "xil_io.h"
//#include "font.h"

void ssd1306_W_Command(uint8_t cmd);
void ssd1306_init_01(void);
void ssd1306_W_Data(uint8_t* data_buffer, uint16_t buffer_size);
void ssd1306_Clear(void);
void ssd1306_Set_Coord(uint8_t page, uint8_t col);
//void ssd1306_W_Char(uint8_t character_Code, uint8_t page, uint16_t column);
//void ssd1306_W_bitmap(uint8_t *bitmap);
//void ssd1306_draw_bitmap(int x,int y, uint8_t *bitmap);
//void ssd1306_W_animation(uint8_t *bitmap);
//void ssd1306_draw_chart(uint8_t* data, uint8_t data_size);
//void ssd1306_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
//void ssd1306_draw_chart_sentinel(uint8_t* data);
//void ssd1306_scroll_chart(uint8_t new_data);
//void ssd1306_w_data(uint8_t* data_buffer, uint16_t buffer_size);


#define I2C_OLED_ADDRESS 0x3c // I2C OLED 주소 설정
#define OLED_SLAVE_ADDRESS 0x3c
#define font_width 12
