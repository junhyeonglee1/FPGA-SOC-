#include "sleep.h"
#include <stdint.h>
#include "xparameters.h"
#include "xiic_l.h"
////#include "xil_io.h"
//#include "font.h"


#define I2C_OLED_ADDRESS 0x3c // I2C OLED 주소 설정
#define OLED_SLAVE_ADDRESS 0x3c
#define font_width 12
