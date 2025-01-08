/*
 * heartrate.h
 *
 *  Created on: 2024. 9. 22.
 *      Author: HARMAN-12
 */

#ifndef SRC_HEARTRATE_H_
#define SRC_HEARTRATE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

bool checkForBeat(int32_t sample);
int16_t averageDCEstimator(int32_t *p, uint16_t x);
int16_t lowPassFIRFilter(int16_t din);
int32_t mul16(int16_t x, int16_t y);


#endif /* SRC_HEARTRATE_H_ */
