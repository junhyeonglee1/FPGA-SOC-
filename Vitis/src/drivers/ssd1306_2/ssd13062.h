#include "sleep.h"
#include <stdint.h>
#include "xparameters.h"
#include "xiic_l.h"
////#include "xil_io.h"
//#include "font.h"

void ssd1306_W_Command2(uint8_t cmd);
void ssd1306_init_012(void);
void ssd1306_W_Data2(uint8_t* data_buffer, uint16_t buffer_size);
void ssd1306_Clear2(void);
void ssd1306_Set_Coord2(uint8_t page, uint8_t col);



#define I2C_OLED_ADDRESS 0x3c // I2C OLED 주소 설정
#define OLED_SLAVE_ADDRESS 0x3c
#define font_width 12
