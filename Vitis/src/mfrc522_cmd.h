/*
 * mfrc522_cmd.h
 *
 *  Created on: 2024. 9. 22.
 *      Author: HARMAN-22
 */

#ifndef SRC_MFRC522_CMD_H_
#define SRC_MFRC522_CMD_H_

//command set
#define Idle_CMD 				0x00
#define Mem_CMD					0x01
#define GenerateRandomId_CMD	0x02
#define CalcCRC_CMD				0x03
#define Transmit_CMD			0x04
#define NoCmdChange_CMD			0x07
#define Receive_CMD				0x08
#define Transceive_CMD			0x0C
#define Reserved_CMD			0x0D
#define MFAuthent_CMD			0x0E
#define SoftReset_CMD			0x0F

#endif /* SRC_MFRC522_CMD_H_ */
