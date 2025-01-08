/*
 * dht11.h
 *
 *  Created on: 2024. 9. 25.
 *      Author: HARMAN-22
 */

#ifndef SRC_DHT11_H_
#define SRC_DHT11_H_

#include "xparameters.h"

#define DHT11_BASEADDR XPAR_DHT11_24_0_S00_AXI_BASEADDR
#define TEMP_HIGH_REG    0x00
#define TEMP_LOW_REG    0x04
#define HUM_HIGH_REG    0x08
#define HUM_LOW_REG    0x0c
#define CHECKSUM_REG    0x10

void dht_cal();

#endif /* SRC_DHT11_H_ */
