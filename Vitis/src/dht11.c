/*
 * dht11.c
 *
 *  Created on: 2024. 9. 25.
 *      Author: HARMAN-22
 */

#include "dht11.h"
#include <stdio.h>

uint32_t temp_high_data, temp_low_data, hum_high_data, hum_low_data, checksum_data;
char tempbuffer[50];
char humidbuffer[50];
char checksumbuffer[100];
void dht_cal() {

    	temp_high_data = *(uint32_t *)(DHT11_BASEADDR + TEMP_HIGH_REG);
    	temp_low_data = *(uint32_t *)(DHT11_BASEADDR + TEMP_LOW_REG);
    	hum_high_data = *(uint32_t *)(DHT11_BASEADDR + HUM_HIGH_REG);
    	hum_low_data = *(uint32_t *)(DHT11_BASEADDR + HUM_LOW_REG);
    	checksum_data = *(uint32_t *)(DHT11_BASEADDR + CHECKSUM_REG);


		//float temperature = ((temp_high_data << 8) | temp_low_data) / 10.0;
		//float humidity = ((hum_high_data << 8) | hum_low_data) / 10.0;


//		xil_printf("%d.%d C\n",temp_high_data,temp_low_data);
//		xil_printf("%d.%d %%\n",hum_high_data,hum_low_data);
//


}
