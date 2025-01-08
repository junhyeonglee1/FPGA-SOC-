/*
 * display_oled.c
 *
 *  Created on: 2024. 9. 24.
 *      Author: HARMAN-22
 */
#include "display_oled.h"
#include "drivers/ssd1306/ssd1306.h"
#include <stdbool.h>
#include "heartrate.h"
#include "max30102.h"
#include "xintc.h"
#include "mlx90614.h"
#define RATE_SIZE 4
uint8_t rates[RATE_SIZE]; //Array of heart rates
XIntc intc1;

extern int oledtemp;
int r_value_oled = 0;
int timer_count=0;

uint8_t rateSpot;
float beatsPerMinute;
int beatAvg = 0;
int index_bpm=0;
int beats_array[5];
int start_flag;
uint8_t read_buff[6];
long ir_value=0;
long red_value=0;
long lastBeat; //Time at which the last beat occurred
char spo2_buffer[50];

int graphtemp;
double r_value;

int oled_state;

//void ssd1306_draw_chart_sentinel(uint8_t* data) {
//    ssd1306_Clear(); // 화면을 지움
//
//    uint8_t i = 0;
//    while (data[i] != 255) {  // 종료 값을 255로 설정 (데이터가 0~100 범위일 경우)
//        uint8_t x1 = (i * 128) / 10;  // 여기서는 예시로 데이터 크기를 10으로 가정
//        uint8_t y1 = 63 - (data[i] * 63 / 100);  // Y좌표 계산 (0~100 범위로 가정)
//        uint8_t x2 = ((i + 1) * 128) / 10;
//        uint8_t y2 = 63 - (data[i + 1] * 63 / 100);
//
//        ssd1306_draw_line(x1, y1, x2, y2);  // 두 점을 연결하는 선 그리기
//        i++;
//    }
//}

//void ssd1306_scroll_chart(uint8_t new_data) {
//    static uint8_t chart_buffer[128] = {0}; // OLED 화면 크기(128픽셀)에 맞춘 버퍼
//    static uint8_t current_position = 0;
//
//    // 새로운 온도값을 버퍼에 추가 (0 ~ 100의 온도 범위로 변환)
//    chart_buffer[current_position] = 63 - (new_data * 63 / 100);
//    current_position++;
//
//    if (current_position >= 128) {  // 화면 끝에 도달하면 다시 처음부터 그리기
//        current_position = 0;
//    }
//
//    // OLED 화면에 그리기 (기존 데이터를 한 칸씩 왼쪽으로 밀기)
//    for (uint8_t x = 0; x < 128; x++) {
//        uint8_t y = chart_buffer[(current_position + x) % 128];  // 순환 버퍼처럼 사용
//        ssd1306_Set_Coord(x / 8, x);  // 좌표 설정
//        uint8_t temp_data[1] = {1 << (y % 8)};  // Y 좌표에 맞춰 점을 찍음
//        ssd1306_w_data(temp_data, 1);  // 각 위치에 점 그리기
//
//    }
//}
//
//void update_oled_chart() {
//    // OLED 초기화
//    ssd1306_init();
//	graphtemp = oledtemp/100+40;
//    // 온도값을 지속적으로 받아와서 OLED에 차트로 그리기
//
//        temp_data = graphtemp;  // 외부 함수에서 받은 oledtemp 값을 사용
//        ssd1306_scroll_chart(temp_data);  // 새로운 온도값으로 차트를 그리기
//        usleep(50000);  // 0.5초마다 업데이트 (필요에 맞게 조절 가능)
//
//}

uint8_t bpm_state = 0;

void max30102_drive(){
//	beats_array[index_bpm] =0;
	index_bpm++;
	index_bpm %= 5; //

	read_max30102_data(read_buff,6);
	ir_value = ((uint32_t)(read_buff[0] & 0x03) << 16) | ((uint32_t)read_buff[1] << 8) | read_buff[2];
	red_value = ((uint32_t)(read_buff[3] & 0x03) << 16) | ((uint32_t)read_buff[4] << 8) | read_buff[5];

	//xil_printf("ir_value : %d \n", ir_value );
	//long irValue = ir_value;
	if(ir_value > 25000)
	{
		if (checkForBeat(ir_value) == true)
		{

			//We sensed a beat!
			long delta = millis() - lastBeat;
			lastBeat = millis();
			//			xil_printf("delta : %d \n", delta );
			//			xil_printf("beatdetected!!\n\n");
			beatsPerMinute = 60 / (delta / 1000.0);


			if (beatsPerMinute < 150 && beatsPerMinute > 50)
			{

				rates[rateSpot++] = (uint8_t)beatsPerMinute; //Store this reading in the array
				rateSpot %= RATE_SIZE; //Wrap variable

				//Take average of readings
				beatAvg = 0;
				for (uint8_t x = 0 ; x < RATE_SIZE ; x++)
				{beatAvg += rates[x];}
				beatAvg /= RATE_SIZE;
				beats_array[index_bpm] = beatAvg;
				//beatAvg = (beats_array[0] + beats_array[1] + beats_array[2] + beats_array[3] + beats_array[4]) / 5;
				//xil_printf("heartbeat : %d bpm \n",beatAvg-15);

				r_value = (double)red_value / ir_value;
//				ssd1306_Clear();
//			display_calculate();

				//oled_state = 1;

				if (beatAvg < 100 && start_flag ==0 && beatAvg > 50)	{
//					xil_printf("sensing start\n");
					start_flag =1;
				}

				else if (start_flag)
				{

//					sprintf(spo2_buffer, "SpO2 : %2.f %% \n", 110-25*r_value + 17); //module2 -> 13
					r_value_oled = 110-25*r_value + 17;
//			    	ssd1306_Clear();
//					display_beatavg();
//					display_spio2();
//					xil_printf(spo2_buffer);
					//oled_state = 2;
				}
			}
		}
	} else {
		//xil_printf("no finger on sesor\n");
//		display_nofinger();
		//oled_state = 3;
	}
}

int millis(){
	return timer_count;
}

unsigned int timercounter = 0;
unsigned int animationcounter = 0; // Animation은 30ms마다 실행
unsigned int displaycounter = 0;   // Display는 1000ms마다 실행
unsigned int rfidtimer = 0;
//extern void max30102_drive();
void incTimeTick(){
	timer_count++;
    timercounter++;
    animationcounter++;
    displaycounter++;
    rfidtimer++;
}

void timer_isr_handler()
{
	incTimeTick();
}

void timer_intc_init()
{
	XIntc_Initialize(&intc1, XPAR_INTC_0_DEVICE_ID);
	//exception, Interrupt setting
	Xil_ExceptionInit();
	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT, (Xil_ExceptionHandler)XIntc_InterruptHandler, &intc1);
	Xil_ExceptionEnable();

	//interrupt ISRT Function
	XIntc_Connect(&intc1, XPAR_INTC_0_TIMER2_0_VEC_ID, (XInterruptHandler)timer_isr_handler, 0);
	XIntc_Enable(&intc1, XPAR_INTC_0_TIMER2_0_VEC_ID);
	XIntc_Start(&intc1, XIN_REAL_MODE);
}
