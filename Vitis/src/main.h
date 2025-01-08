#include <stdio.h>
#include <stdbool.h>
#include "platform.h"
#include "rfid_main.h"
#include "mlx90614.h"
#include "timer.h"
#include "max30102.h"
#include "display_oled.h"
//#include "xgpio.h" // Xilinx GPIO 제어용 헤더 파일
#include "xparameters.h"
#include "dht11.h"
//#include "active.h"
//#include "xgpio.h"
//#include "drivers/ssd1306/ssd1306.h"
#include "drivers/ssd1306/ssd1306_command.h"
#include "drivers/ssd1306/ssd1306_test.h"
#include "drivers/ssd1306_2/ssd1306_command2.h"
#include "drivers/ssd1306_3/ssd1306_command3.h"
//#include "drivers/ssd1306_3/ssd1306_font3.h"
#include "rtc.h"
//#include "drivers/ssd1306_2/ssd1306_test2.h"
#include "button.h"
//#include "drivers/ssd1306/bitmap_1.h"

//XGpio Gpio, Gpio1;

static int flag = 1;

//void setup_gpio();
//void check_buttons_and_execute();

//extern void ssd1306_BPM_animation();
//extern void ssd1306_thermometer_animation();
//extern void ssd1306_Personal_information_animation();
//extern void ssd1306_pedometer_animation();

extern int oledstate;

#define GPIO_DEVICE_ID XPAR_GPIO_1_DEVICE_ID // Vivado에서 설정된 GPIO ID
#define BUTTON_CHANNEL 1                    // GPIO의 채널 번호
#define BUTTON_MASK 0x0F                    // 4비트 마스크
#define STEP_LENGTH 0.75
#define CALORIE_PER_KM 60
#define GPIO_DEVICE_ID2  XPAR_AXI_GPIO_1_DEVICE_ID
#define GPIO_CHANNEL    1

#define GPI ( *(uint32_t*)XPAR_GPI_V1_0_0_BASEADDR)
#define GPI2 ( *(uint32_t*)XPAR_GPI_V1_0_1_BASEADDR)
button_t leftButton;
button_t rightButton;
button_t downButton;

extern unsigned int timercounter;
extern unsigned int animationcounter; // Animation은 30ms마다 실행
extern unsigned int displaycounter;   // Display는 1000ms마다 실행
extern unsigned int rfidtimer;
void button_check();
uint8_t UIstate = 0;


void active_data(int *step_count);

int mode_state = 0;

int calorie = 0;
int distance_whole = 0;

extern uint8_t seconds;
extern uint8_t hours;
extern uint8_t minutes;
extern uint8_t days;
extern uint8_t months;
