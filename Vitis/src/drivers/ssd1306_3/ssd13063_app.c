#include "ssd1306_font3.h"
#include <string.h>
#include <stdio.h>
void ssd1306_num_write3(uint8_t num,SSD1306_Font_t3 Font, SSD1306_COLOR3 color){
	char buffer[2]; // 숫자 하나와 널 문자를 위한 배열
	if (num <= 9) {
		buffer[0] = '0' + num; // 숫자를 문자로 변환
		buffer[1] = '\0';      // 널 문자 추가
		ssd1306_WriteString3(buffer, Font, color); // 숫자 출력
	}
}

extern uint32_t temp_high_data, temp_low_data, hum_high_data, hum_low_data, checksum_data;

void display_dht11_rtc(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute, uint8_t second){

	ssd1306_Fill3(Black3);
	ssd1306_SetCursor3(2, 1);
	ssd1306_num_write3(month / 10, Font_7x103, White3);
	ssd1306_SetCursor3(9, 1);
	ssd1306_num_write3(month % 10, Font_7x103, White3);

	ssd1306_SetCursor3(16, 1);
	ssd1306_WriteString3(".", Font_7x103, White3);
	ssd1306_SetCursor3(25, 1);
	ssd1306_num_write3(day / 10, Font_7x103, White3);
	ssd1306_SetCursor3(32, 1);
	ssd1306_num_write3(day % 10, Font_7x103, White3);

	ssd1306_SetCursor3(46, 1);
	ssd1306_num_write3(hour / 10, Font_7x103, White3);
	ssd1306_SetCursor3(53, 1);
	ssd1306_num_write3(hour % 10, Font_7x103, White3);
	ssd1306_SetCursor3(60, 1);
	ssd1306_WriteString3(":", Font_7x103, White3);


	ssd1306_SetCursor3(65, 1);
	ssd1306_num_write3(minute / 10, Font_7x103, White3);
	ssd1306_SetCursor3(72, 1);
	ssd1306_num_write3(minute % 10, Font_7x103, White3);

	ssd1306_SetCursor3(79, 1);
	ssd1306_WriteString3(":", Font_7x103, White3);

	ssd1306_SetCursor3(84, 1);
	ssd1306_num_write3(second / 10, Font_7x103, White3);
	ssd1306_SetCursor3(91, 1);
	ssd1306_num_write3(second % 10, Font_7x103, White3);

	ssd1306_SetCursor3(3, 18);
	ssd1306_WriteString3("Temp:", Font_11x183, White3);
	ssd1306_SetCursor3(60, 18);
	ssd1306_num_write3(temp_high_data / 10, Font_11x183, White3);
	ssd1306_SetCursor3(71, 18);
	ssd1306_num_write3(temp_high_data % 10, Font_11x183, White3);

	ssd1306_SetCursor3(82, 18);
	ssd1306_WriteString3(".", Font_11x183, White3);
	ssd1306_SetCursor3(93, 18);
	ssd1306_num_write3(temp_low_data / 10, Font_11x183, White3);
	ssd1306_SetCursor3(104, 18);
	ssd1306_num_write3(temp_low_data % 10, Font_11x183, White3);
	ssd1306_SetCursor3(115, 18);
	ssd1306_WriteString3("C", Font_11x183, White3);

	ssd1306_SetCursor3(3, 37);
	ssd1306_WriteString3("HUMI:", Font_11x183, White3);
	ssd1306_SetCursor3(60, 37);
	ssd1306_num_write3(hum_high_data / 10, Font_11x183, White3);
	ssd1306_SetCursor3(71, 37);
	ssd1306_num_write3(hum_high_data % 10, Font_11x183, White3);

	ssd1306_SetCursor3(82, 37);
	ssd1306_WriteString3(".", Font_11x183, White3);
	ssd1306_SetCursor3(93, 37);
	ssd1306_num_write3(hum_low_data / 10, Font_11x183, White3);
	ssd1306_SetCursor3(104, 37);
	ssd1306_num_write3(hum_low_data % 10, Font_11x183, White3);
	ssd1306_SetCursor3(115, 37);
	ssd1306_WriteString3("%", Font_11x183, White3);

	ssd1306_UpdateScreen3();


}
