/*
 * display_oled.h
 *
 *  Created on: 2024. 9. 24.
 *      Author: HARMAN-22
 */

#ifndef SRC_DISPLAY_OLED_H_
#define SRC_DISPLAY_OLED_H_
#include <stdint.h>
void display_patient_info();
void display_temperatur();
void display_line_test();
void update_oled_chart();
void display_beatavg();
void display_calculate();
void display_spio2();
void display_nofinger();
int millis();
void incTimeTick();
void timer_isr_handler();
void timer_intc_init();
void max30102_drive();
void display_tagcard();
void display_state_display();

#endif /* SRC_DISPLAY_OLED_H_ */
