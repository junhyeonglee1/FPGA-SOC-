#include "main.h"

extern uint8_t bpm_state;

int main()
{

	spi_init();
	timer_intc_init();
	Timer_SetPrescale(TIM0, 999);
	Timer_SetTimerTop(TIM0,99);
	Timer_StartIEnable(TIM0);

	rtc_init(10, 31, 8, 30, 9);


	rfid_reader_init();

	initButtonState(&leftButton, &GPI, 1);
	initButtonState(&rightButton, &GPI, 2);
	initButtonState(&downButton, &GPI, 3);

	MAX30102_Init();
	ssd1306_Init();
	ssd1306_Init2();
	ssd1306_Init3();

	int step_count = 0;

	int roundrobin = 0;
	UIstate = 1;


	while (1) {
	    roundrobin = (roundrobin + 1) % 3;

	    switch (roundrobin) {
	        case 0:
	            button_check();
	            rfid_tag_processing();
	            update_rtc();
	            if(timercounter >= 1000){
	            	dht_cal();
	            	timercounter = 0;
	            	display_dht11_rtc(months, days, hours, minutes, seconds);
	            }
	            if (oledstate == 1) {
	                flag = 99;
	            }
	            break;

	        case 1:
	            switch (flag) {
	                case 1:
	                	max30102_drive();
	                    break;
	                case 2:
	                	mlx_writecommand();
	                    break;
	                case 3:
	                	active_data(&step_count);
	                    break;
	                case 4:
	                    break;
	                default:
	                    break;
	            }
	            break;

	        case 2:
	            if (UIstate == 1) {
	                displaycounter = 1000;
	                animationcounter = 42;
	                UIstate = 0; // ���� �ʱ�ȭ
	            }

	            if (displaycounter >= 1000) {
	                displaycounter = 0;

	                switch (flag) {
	                    case 1:
	                    	//ssd1306_display_BodyTemperature();
	                    	ssd1306_display_BPM_UI();
	                        break;
	                    case 2:
	                        ssd1306_display_BodyTemperature();
	                        break;
	                    case 3:
	                    	ssd1306_display_step_cnt_UI(step_count, distance_whole, calorie);
	                        break;
	                    case 4:
	                        break;
	                    default:
	                        ssd1306_display_PatienInfo_UI();
	                        if(rfidtimer >= 3000)
	                        {	flag = 1;
	                        	oledstate = 0;
	                        	UIstate = 1;
	                        }
	                        break;
	                }
	            }
	            if (animationcounter >= 42) {
	                animationcounter = 0;

	                switch (flag) {
	                    case 1:
	                    		ssd1306_BPM_animation();
	                        break;
	                    case 2:
	                        ssd1306_thermometer_animation();
	                        break;
	                    case 3:
	                    	ssd1306_pedometer_animation();
	                        break;
	                    default:
	                        ssd1306_Personal_information_animation();
	                        break;
	                }
	            }
	            break;
	        default:
	            break;
	    }
	}

	return 0;
}


void button_check()
{
	if(getButtonState(&rightButton) == ACT_RELEASED){
		flag = 1;
		UIstate = 1;
	} else if(getButtonState(&leftButton) == ACT_RELEASED){
		flag = 2;
		UIstate = 1;
	}else if(getButtonState(&downButton) == ACT_RELEASED){
		flag = 3;
		UIstate = 1;
	}
}


//void setup_gpio() {
//	int status;
//
//	// GPIO �ʱ�ȭ
//	status = XGpio_Initialize(&Gpio, GPIO_DEVICE_ID);
//	if (status != XST_SUCCESS) {
//		//xil_printf("GPIO �ʱ�ȭ ����\n");
//		return;
//	}
//
//	// ��ư GPIO�� �Է����� ����
//	XGpio_SetDataDirection(&Gpio, BUTTON_CHANNEL, BUTTON_MASK);
//}
//
//void check_buttons_and_execute() {
//	uint32_t button_data = XGpio_DiscreteRead(&Gpio, BUTTON_CHANNEL); // GPIO �� �б�
//
//	// ù ��° ��Ʈ�� ������ max30102_drive() ������ Ʈ�����ϰ�, �ٸ� �÷��״� ��Ȱ��ȭ
//	if (button_data & 0x01) {
////		max30102_flag = 1;
////		rfid_flag = 0;
////		mlx_flag = 0;
//		flag = 1;
//
//	}
//
//	// �� ��° ��Ʈ�� ������ rfid_tag_processing() ������ Ʈ�����ϰ�, �ٸ� �÷��״� ��Ȱ��ȭ
//	if (button_data & 0x02) {
//
//		flag = 2;
//	}
//
//	// �� ��° ��Ʈ�� ������ mlx_writecommand() ������ Ʈ�����ϰ�, �ٸ� �÷��״� ��Ȱ��ȭ
//	if (button_data & 0x04) {
//
//		flag = 3;
//	}
//
//	if (button_data & 0x08) {
//
//		flag = 4;
//	}
//	//
//	//    // �÷��װ� Ȱ��ȭ�� �Լ��� ��� ����
//	//    if (max30102_flag) {
//	//        max30102_drive();
//	//    }
//	//
//	//    if (rfid_flag) {
//	//        rfid_tag_processing();
//	//    }
//	//
//	//    if (mlx_flag) {
//	//        mlx_writecommand();
//	//    }
//}




void active_data(int *step_count) {
	static u32 sensor_data;
	static float distance = 0.0;
	//static int calorie = 0;
	//static int distance_fraction;
	//XGpio_Initialize(&Gpio1, XPAR_AXI_GPIO_1_DEVICE_ID);
	// GPIO �ʱ�ȭ (�� ���� �ʱ�ȭ�ϵ��� ���� ����)
//	int Status =
//	if (Status != XST_SUCCESS) {
//		//xil_printf("GPIO Initialization Failed\r\n");
//		return;
//	}
	//XGpio_Initialize(&Gpio1, XPAR_AXI_GPIO_1_DEVICE_ID);
	//XGpio_SetDataDirection(&Gpio1, GPIO_CHANNEL, 0xFFFFFFFF);

	// ���� ������ �б� �� ó��
	sensor_data = GPI2;
	if (sensor_data & 0x01) {
		(*step_count)++;
		distance = (*step_count * STEP_LENGTH) / 1000.0;
		calorie = distance * CALORIE_PER_KM;

		distance_whole = (int)distance;

	}
}
//

