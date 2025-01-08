/*
 * max30102.h
 *
 *  Created on: 2024. 9. 22.
 *      Author: HARMAN-12
 */

#ifndef SRC_MAX30102_H_
#define SRC_MAX30102_H_

#include "xil_printf.h"
#include "xiic_l.h"
#include "xparameters.h"
#include "sleep.h"
#include <math.h>
#include <stdint.h>




void MAX30102_Init();
void read_max30102_data(u8 *data, unsigned byte_count);



#endif /* SRC_MAX30102_H_ */
