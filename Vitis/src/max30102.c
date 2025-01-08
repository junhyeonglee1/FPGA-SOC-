
/*
 * max30102.c
 *
 *  Created on: 2024. 9. 22.
 *      Author: HARMAN-18
 */
#include "max30102.h"
#define BUFFER_SIZE 2

#define MAX30102_ADDRESS 0x57

#define FIFO_DATA_REG 0x07
#define REG_INTR_STATUS_1    0x00
#define REG_INTR_ENABLE_1    0x02
#define REG_FIFO_WR_PTR      0x04
#define REG_FIFO_RD_PTR      0x06
#define REG_FIFO_OVF_CNT     0x05
#define REG_FIFO_DATA        0x07
#define REG_FIFO_CONFIG      0x08
#define REG_MODE_CONFIG      0x09
#define REG_SPO2_CONFIG      0x0A
#define REG_LED1_PA          0x0C
#define REG_LED2_PA          0x0D
#define REG_PILOT_PA         0x10

void MAX30102_Init() {
	// interrupt set
	u8 buffer[BUFFER_SIZE];
	buffer[0] = REG_INTR_ENABLE_1;
	buffer[1] = 0xC0;
	XIic_Send(XPAR_IIC_0_BASEADDR, MAX30102_ADDRESS, buffer, 2, XIIC_STOP);

	// FIFO WR_PTR, OVF_CNT, RD_PTR reset
	buffer[0] = REG_FIFO_WR_PTR;
	buffer[1] = 0x00;
	XIic_Send(XPAR_IIC_0_BASEADDR, MAX30102_ADDRESS, buffer, 2, XIIC_STOP);

	buffer[0] = REG_FIFO_OVF_CNT;
	buffer[1] = 0x00;
	XIic_Send(XPAR_IIC_0_BASEADDR, MAX30102_ADDRESS, buffer, 2, XIIC_STOP);

	buffer[0] = REG_FIFO_RD_PTR;
	buffer[1] = 0x00;
	XIic_Send(XPAR_IIC_0_BASEADDR, MAX30102_ADDRESS, buffer, 2, XIIC_STOP);

	// FIFO ����
	buffer[0] = REG_FIFO_CONFIG;
	buffer[1] = 0x4F;
	XIic_Send(XPAR_IIC_0_BASEADDR, MAX30102_ADDRESS, buffer, 2, XIIC_STOP);

	// ��� ����: SPO2 ��� Ȱ��ȭ
	buffer[0] = REG_MODE_CONFIG;
	buffer[1] = 0x03;
	XIic_Send(XPAR_IIC_0_BASEADDR, MAX30102_ADDRESS, buffer, 2, XIIC_STOP);

	// SPO2 ����
	buffer[0] = REG_SPO2_CONFIG;
	buffer[1] = 0x67;
	XIic_Send(XPAR_IIC_0_BASEADDR, MAX30102_ADDRESS, buffer, 2, XIIC_STOP);

	// LED ���� ������ ���� ���� (0x24 -> 0x10)
	buffer[0] = REG_LED1_PA;
	buffer[1] = 0x24;  // LED ���� ������ �� ����
	XIic_Send(XPAR_IIC_0_BASEADDR, MAX30102_ADDRESS, buffer, 2, XIIC_STOP);

	buffer[0] = REG_LED2_PA;
	buffer[1] = 0x24;  // LED ���� ������ �� ����
	XIic_Send(XPAR_IIC_0_BASEADDR, MAX30102_ADDRESS, buffer, 2, XIIC_STOP);

	buffer[0] = REG_PILOT_PA;
	buffer[1] = 0x7F;
	XIic_Send(XPAR_IIC_0_BASEADDR, MAX30102_ADDRESS, buffer, 2, XIIC_STOP);
}


// FIFO���� �����͸� �д� �Լ�
void read_max30102_data(u8 *data, unsigned byte_count) {
	u8 reg = FIFO_DATA_REG;

	// �������� �ּ� ���� (FIFO ������ ��������)
	XIic_Send(XPAR_IIC_0_BASEADDR, MAX30102_ADDRESS, &reg, 1, XIIC_REPEATED_START);

	// FIFO ������ �б�
	XIic_Recv(XPAR_IIC_0_BASEADDR, MAX30102_ADDRESS, data, byte_count, XIIC_STOP);
}
