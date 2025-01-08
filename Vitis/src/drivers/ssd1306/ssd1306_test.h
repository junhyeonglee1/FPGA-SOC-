/*
 * ssd1306_test.h
 *
 *  Created on: 2024. 9. 25.
 *      Author: HARMAN-18
 */

#ifndef SRC_SSD1306_TEST_H_
#define SRC_SSD1306_TEST_H_

#include <_ansi.h>

_BEGIN_STD_C

void ssd1306_TestBorder(void);
void ssd1306_TestFonts1(void);
void ssd1306_TestFonts2(void);
void ssd1306_TestFonts3(void);
void ssd1306_TestFPS(void);
void ssd1306_TestAll(void);
void ssd1306_TestLine(void);
void ssd1306_TestRectangle(void);
void ssd1306_TestRectangleFill(void);
void ssd1306_TestRectangleInvert(void);
void ssd1306_TestCircle(void);
void ssd1306_TestArc(void);
void ssd1306_TestPolyline(void);
void ssd1306_TestDrawBitmap(void);
//void ssd1306_num_write(uint8_t num,SSD1306_Font_t Font, SSD1306_COLOR color);

void ssd1306_display_step_cnt_UI(int step_count, int distance, int calorie);
void ssd1306_display_BodyTemperature(void);
void ssd1306_display_PatienInfo_UI(void);
void ssd1306_display_BPM_UI(void);
void ssd1306_progressbar();
void ssd1306_BPM_graph_animation();
void ssd1306_BPM_sensor();

#define FRAME_DELAY (42)
#define FRAME_WIDTH (32)
#define FRAME_HEIGHT (32)
#define FRAME_COUNT (sizeof(BPM_animation1) / sizeof(BPM_animation1[0]))






_END_STD_C



#endif /* SRC_SSD1306_TEST_H_ */
