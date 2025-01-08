#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"
#include "sleep.h"

#define RTC_BASEADDR XPAR_RTC_ALL_0_S00_AXI_BASEADDR
#define RTC_WR           0x04
#define RTC_SEC_REG       0x08
#define RTC_MIN_REG       0x0C
#define RTC_HOUR_REG    0x10
#define RTC_DAY_REG       0x14
#define RTC_MONTH_REG    0x18
#define RTC_INIT_REG     0x00  // initial value를 쓰기 위한 레지스터





void rtc_init(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t days, uint8_t months);
uint32_t encode_rtc_value(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t days, uint8_t months);
void update_rtc();
