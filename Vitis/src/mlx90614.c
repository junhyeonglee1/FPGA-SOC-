#include "xparameters.h"
#include "xiic.h"
#include "xiic_l.h"
#include "xil_printf.h"
#include <stdio.h>
#include "mlx90614.h"
//#include "display_oled.h"


u8 WriteBuffer[1] = {0x07};
u8 ReadBuffer[3];  // 2-byte data + 1-byte PEC (ignored)
int oledtemp=0;
double temp_amb;
int temp_amb_x100;


void mlx_writecommand() {

    XIic_Send(XPAR_AXI_IIC_0_BASEADDR, MLX90614_ADDR, WriteBuffer, 1, XIIC_REPEATED_START);  // Stop condition
    XIic_Recv(XPAR_AXI_IIC_0_BASEADDR, MLX90614_ADDR, ReadBuffer, 3, XIIC_STOP);  // Read 2 bytes
    temp_amb=(ReadBuffer[1]<<8|ReadBuffer[0]);
    temp_amb=(temp_amb*0.02)-273.15;
    oledtemp = temp_amb * 100;

	temp_amb_x100 = temp_amb * 100;

}
