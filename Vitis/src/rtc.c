#include "rtc.h"

// Function to combine seconds, minutes, hours, days, and months into a 26-bit value
uint32_t encode_rtc_value(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t days, uint8_t months) {
    // Assuming the bit allocation:
    // - Seconds: bits [5:0] (6 bits)
    // - Minutes: bits [11:6] (6 bits)
    // - Hours: bits [16:12] (5 bits)
    // - Days: bits [21:17] (5 bits)
    // - Months: bits [25:22] (4 bits)
    uint32_t value = 0;
    value |= (seconds & 0x3F);         // Seconds in bits [5:0]
    value |= (minutes & 0x3F) << 6;    // Minutes in bits [11:6]
    value |= (hours & 0x1F) << 12;     // Hours in bits [16:12]
    value |= (days & 0x1F) << 17;      // Days in bits [21:17]
    value |= (months & 0x0F) << 22;    // Months in bits [25:22]
    return value;
}

void rtc_init(uint8_t seconds, uint8_t minutes, uint8_t hours, uint8_t days, uint8_t months) {
    uint32_t initial_value = encode_rtc_value(seconds, minutes, hours, days, months);

    // Write the combined initial value to slv_reg0 (RTC_BASEADDR)
    *(uint32_t *)(RTC_BASEADDR + RTC_INIT_REG) = initial_value;

    // Set write signal to 1 by writing to the RTC_WR register
    *(uint32_t *)(RTC_BASEADDR + RTC_WR) = 1;

    // Small delay to ensure the write is registered
    usleep(10);

    // Set write signal back to 0 after the write is complete
    *(uint32_t *)(RTC_BASEADDR + RTC_WR) = 0;
}

uint8_t seconds = 0;
uint8_t hours =0;
uint8_t minutes = 0;
uint8_t days = 0;
uint8_t months = 0;

void update_rtc()
{
	seconds = *(uint32_t *)(RTC_BASEADDR + RTC_SEC_REG);
	minutes = *(uint32_t *)(RTC_BASEADDR + RTC_MIN_REG);
	hours = *(uint32_t *)(RTC_BASEADDR + RTC_HOUR_REG);
	days = *(uint32_t *)(RTC_BASEADDR + RTC_DAY_REG);
	months = *(uint32_t *)(RTC_BASEADDR + RTC_MONTH_REG);

}


//int main() {
//    uint32_t sec_data, min_data, hour_data, day_data, month_data;
//
//    // RTC 초기화 값 설정 (시작 시점: 9월 27일, 4시 50분 00초)
//    rtc_init(00, 50, 4, 27, 9);
//
//    while (1) {
//        // RTC 레지스터에서 시간 정보 읽기
//        sec_data = *(uint32_t *)(RTC_BASEADDR + RTC_SEC_REG);
//        min_data = *(uint32_t *)(RTC_BASEADDR + RTC_MIN_REG);
//        hour_data = *(uint32_t *)(RTC_BASEADDR + RTC_HOUR_REG);
//        day_data = *(uint32_t *)(RTC_BASEADDR + RTC_DAY_REG);
//        month_data = *(uint32_t *)(RTC_BASEADDR + RTC_MONTH_REG);
//
//        // 읽은 시간 및 날짜 정보 출력
//        xil_printf("Time: %02d:%02d:%02d\n", hour_data, min_data, sec_data);
//        xil_printf("Date: %02d/%02d\n", month_data, day_data);
//
//        // 1초 대기
//        sleep(1);
//    }
//}
