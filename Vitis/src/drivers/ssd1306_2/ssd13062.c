#include "ssd13062.h"

#include <stdlib.h>  // abs �Լ� ����� ���� ��� ����
//
void ssd1306_w_command2(uint8_t cmd)
{
	uint8_t buffer[2] = {0};
	buffer[0] = (0<<7)|(0<<6);
	buffer[1] = cmd;

	XIic_Send(XPAR_IIC_0_BASEADDR, OLED_SLAVE_ADDRESS, buffer, 2, XIIC_STOP);
}

void ssd1306_init_012()
{
	ssd1306_w_command2(0xA8);	//Set Mux Ratio
	ssd1306_w_command2(0x3F);	//64MUX

	ssd1306_w_command2(0xD3);	//Set Display Offset
	ssd1306_w_command2(0x00);	//COM0

	ssd1306_w_command2(0x40);	//Set Display Start Line

	ssd1306_w_command2(0xA1);	//Set Segment re-map, Default 0xA0
	//column address 127 is mapped to SEG0 (�¿� ����)

	ssd1306_w_command2(0xC8);	//Set COM Output Scan Direction, default 0xC0
	//remapped mode. Scan from COM[N-1] to COM0 (���� ����)

	ssd1306_w_command2(0xDA);	//Set COM Pins hardware configuration
	ssd1306_w_command2(0x12);

	ssd1306_w_command2(0x20);	//Set Memory Addressing Mode
	ssd1306_w_command2(0x02);	//Page Addressing Mode

	ssd1306_w_command2(0x81);	//Set Contrast Control
	ssd1306_w_command2(0x7F);	//1~256

	ssd1306_w_command2(0xA4);	//Disable Entire Display On

	ssd1306_w_command2(0xA6);	//Set Normal Display

	ssd1306_w_command2(0xD5);	//Set Osc Frequency
	ssd1306_w_command2(0x80);

	ssd1306_w_command2(0x8D);	//Enable charge pump regulator
	ssd1306_w_command2(0x14);

	ssd1306_w_command2(0xAF);	//Display ON
}
//
void ssd1306_w_data2(uint8_t* data_buffer, uint16_t buffer_size)
{
	uint8_t Buffer[font_width*2 + 1]={0};
	Buffer[0] = 0x40;
	for(uint16_t i = 0; i < buffer_size; i++) {
		Buffer[i + 1] = data_buffer[i];
	}

	XIic_Send(XPAR_IIC_0_BASEADDR, OLED_SLAVE_ADDRESS, Buffer, buffer_size+1 , XIIC_STOP);
}

void ssd1306_Set_Coord2(uint8_t page, uint8_t col)
{
	uint8_t col_low=0x0F,col_high=0x1F;
	col_low=(col&0x0F);
	col_high=0x10|((col>>4)&0x0F);
	ssd1306_w_command2(0xB0+page);
	ssd1306_w_command2(col_low);
	ssd1306_w_command2(col_high);
}
//
void ssd1306_Clear2(void)
{
	//1���� 1����Ʈ�� �����Ǿ� �ְ� 1�������� 128���� ���� �����ϹǷ�
	//1����Ʈ ũ���� ���� 128���� ���� �迭 ����
	uint8_t buffer[2]={0};
	buffer[0] = 0x40;

	//0��° ������ �����ؾ� �ϹǷ� 0x00, 0x10�� ��ɾ� �Լ��� ���� ������
	//������ �ּҸ� 0���� ����
	ssd1306_w_command2(0x00);
	ssd1306_w_command2(0x10);

	for(uint8_t i=0;i<8;i++)
	{
		//Page Addressing Mode�� ��� ������ �ּҰ� ���� ���κп� �������� ��
		//������ �ּҴ� �״�� ������ä �� �ּҸ� ���µǹǷ�
		//��ü �������� �����ϱ� ���ؼ� �����Ͱ� ��ġ�� ������ �ּҸ� 1�� ����������� �Ѵ�
		//ssd1306_w_command(0xB0+i);
		for(uint8_t j=0;j<128;j=j+1)
		{
			ssd1306_Set_Coord2(i,j);
			//1����Ʈ ũ���� 0x00���� ���� 128 �迭�� �����ϹǷ� �� ������ ��ü�� 0���� ���ŵȴ�
			//ssd1306_w_data(0x00,12);
			XIic_Send(XPAR_IIC_0_BASEADDR, OLED_SLAVE_ADDRESS, buffer, 2 , XIIC_STOP);
		}
	}
}
//
//
//void ssd1306_W_Char(uint8_t character_Code, uint8_t page, uint16_t column)
//{
//	uint8_t char_Buffer[font_width*2]={0};
//
//	for(uint8_t i=0;i<font_width*2;i++)
//	{
//		char_Buffer[i]=ssd1306_Fonts[(character_Code-32)*(font_width*2)+i];
//	}
//
//	for(uint8_t i=0;i<2;i++)
//	{
//		ssd1306_Set_Coord(page+i,column);
//		ssd1306_w_data(&char_Buffer[i*font_width],font_width);
//	}
//}
//
//void ssd1306_W_bitmap(uint8_t *bitmap)
//{
//
//	for(int j = 0; j< 8;j++)
//	{
//		for(uint8_t i=0;i<16;i++){
//			ssd1306_Set_Coord(j,i*8);
//			ssd1306_w_data(&bitmap[i*8 + 128*j],8);
//		}
//	}
//}
//
//void ssd1306_draw_bitmap(int x,int y, uint8_t *bitmap)
//{
//
//	for(int j = 0; j< 8;j++)
//	{
//		for(uint8_t i=0;i<16;i++){
//			ssd1306_Set_Coord(j,i*8);
//			ssd1306_w_data(&bitmap[i*8 + 128*j],8);
//		}
//	}
//}
//
//
//void ssd1306_W_animation(uint8_t *bitmap)
//{
//	for(int k = 0; k < 28; k++) {
//		for(int j = 0; j < 8; j++) {
//			for(uint8_t i = 0; i < 16; i++) {
//				ssd1306_Set_Coord(j, i * 8);
//
//				// bitmap���� 1�������� �����Ͽ� ������ �迭�� ����
//				uint8_t temp_buffer[8];
//				for(int m = 0; m < 8; m++) {
//					temp_buffer[m] = bitmap[k * 64 * 8 + j * 64 + i * 8 + m];
//				}
//
//				// ssd1306_w_data�� 1���� �迭�� ����
//				ssd1306_w_data(temp_buffer, 8);
//			}
//		}
//		usleep(500000);
//	}
//}
//
//void ssd1306_draw_chart(uint8_t* data, uint8_t data_size) {
//    ssd1306_Clear(); // ȭ���� ����
//
//    // X�࿡ �����͸� ������ 128 �ȼ��� ���� �׸���
//    for (uint8_t i = 0; i < data_size - 1; i++) {
//        uint8_t x1 = (i * 128) / data_size; // X��ǥ ���
//        uint8_t y1 = 63 - (data[i] * 63 / 100); // Y��ǥ ��� (0~100 ������ ����)
//        uint8_t x2 = ((i + 1) * 128) / data_size;
//        uint8_t y2 = 63 - (data[i + 1] * 63 / 100);
//
//        // �� ���� �����ϴ� �� �׸���
//        ssd1306_draw_line(x1, y1, x2, y2);
//    }
//}
//
//
//
//void ssd1306_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {
//    int dx = abs(x2 - x1), sx = x1 < x2 ? 1 : -1;
//    int dy = -abs(y2 - y1), sy = y1 < y2 ? 1 : -1;
//    int err = dx + dy, e2; /* error value e_xy */
//
//    for(;;){  /* loop */
//        ssd1306_Set_Coord(y1/8, x1); // ��ǥ ����
//        uint8_t temp_data[1] = {1 << (y1 % 8)};
//        ssd1306_w_data(temp_data, 1); // �ش� ��ġ�� �� ���
//
//        if (x1 == x2 && y1 == y2) break;
//        e2 = 2 * err;
//        if (e2 >= dy) { err += dy; x1 += sx; } /* e_xy+e_x > 0 */
//        if (e2 <= dx) { err += dx; y1 += sy; } /* e_xy+e_y < 0 */
//    }
//}
//
////void ssd1306_scroll_chart(uint8_t* data, uint8_t data_size) {
////    static uint8_t chart_buffer[128] = {0}; // ȭ�� ũ��� ������ ����
////    static uint8_t current_position = 0;
////
////    // ���ο� ������ �߰�
////    chart_buffer[current_position] = 63 - (data[data_size - 1] * 63 / 100);  // ������ ������ �� ����
////    current_position++;
////
////    if (current_position >= 128) {  // ȭ�� ���� �����ϸ�
////        current_position = 0;  // ó������ �ǵ��� (��ȯ)
////    }
////
////    // ȭ���� ������ �ʰ�, ��� �����͸� �� ĭ�� �������� �б�
////    for (uint8_t x = 0; x < 128; x++) {
////        uint8_t y = chart_buffer[(current_position + x) % 128];  // ��ȯ ����ó�� ���
////        ssd1306_Set_Coord(x / 8, x);  // ��ǥ ����
////        uint8_t temp_data[1] = {1 << (y % 8)};
////        ssd1306_w_data(temp_data, 1);  // �� ��ġ�� �� �׸���
////    }
////}
