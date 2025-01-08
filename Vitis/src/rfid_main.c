#include <stdio.h>
#include "xil_printf.h"
#include "mfrc522_reg.h"
#include "xspi.h"
#include "xparameters.h"
#include "mfrc522_cmd.h"
#include "sleep.h"
#include "mfrc522.h"
#include "rfid_main.h"
//#include "display_oled.h"


uint8_t rfid_check_flag=0;
uint8_t readData;
uint8_t carddata;
uint8_t rxDataStr[MAX_LEN];   // rfid tagging data

int oledstate = 0;

XSpi SpiInstance;

void mfrc522_reset()
{
	mfrc522_write(CommandReg,SoftReset_CMD);
}

void mfrc522_init()
{
	uint8_t byte;

	mfrc522_reset();
	mfrc522_write(TModeReg, 0x8D);
    mfrc522_write(TPrescalerReg, 0x3E);
    mfrc522_write(TReloadReg_1, 30);
    mfrc522_write(TReloadReg_2, 0);
	mfrc522_write(TxASKReg, 0x40);
	mfrc522_write(ModeReg, 0x3D);

	byte = mfrc522_read(TxControlReg);
//	xil_printf("TxControlReg : %x\n\r", byte);
	if(!(byte&0x03))
	{
		mfrc522_write(TxControlReg,byte|0x03);
	}

}

// RFID 레지스터 쓰기 함수
void mfrc522_write(uint8_t addr, uint8_t value) {
    uint8_t tx_data[2];
    tx_data[0] = (addr << 1) & 0x7E;
    tx_data[1] = value;

    XSpi_SetSlaveSelect(&SpiInstance, 0x01);
    XSpi_Transfer(&SpiInstance, tx_data, NULL, 2);
    XSpi_SetSlaveSelect(&SpiInstance, 0x00);
}

// RFID 레지스터 읽기 함수
uint8_t mfrc522_read(uint8_t addr) {
    static uint8_t tx_data[2], rx_data[2];
    tx_data[0] = ((addr << 1) & 0x7E) | 0x80;
    tx_data[1] = 0x00;

    XSpi_SetSlaveSelect(&SpiInstance, 0x01);
    XSpi_Transfer(&SpiInstance, tx_data, rx_data, 2);
    XSpi_SetSlaveSelect(&SpiInstance, 0x00);

    return rx_data[1];
}


void spi_init() {
    int status;

    // SPI 초기화
    status = XSpi_Initialize(&SpiInstance, XPAR_SPI_0_DEVICE_ID);
    if (status != XST_SUCCESS) {
        //xil_printf("SPI Initialization Failed\n");
        return;
    }

    // SPI 옵션 설정 (마스터 모드, 클록 속도 등)
    XSpi_SetOptions(&SpiInstance, XSP_MASTER_OPTION | XSP_MANUAL_SSELECT_OPTION);

    // SPI 시작
    XSpi_Start(&SpiInstance);

    // 슬레이브 선택 해제
    XSpi_IntrGlobalDisable(&SpiInstance);
    XSpi_SetSlaveSelect(&SpiInstance, 0x01);
}

uint8_t mfrc522_to_card(uint8_t cmd, uint8_t *send_data, uint8_t send_data_len, uint8_t *back_data, uint32_t *back_data_len)
{
    uint8_t status = ERROR;
    uint8_t irqEn = 0x00;
    uint8_t waitIRq = 0x00;
    uint8_t lastBits;
    uint8_t n;
    //uint8_t tmp;
    uint32_t i;

    switch (cmd)
    {
        case MFAuthent_CMD:
            irqEn = 0x12;
            waitIRq = 0x10;
            break;
        case Transceive_CMD:
            irqEn = 0x77;
            waitIRq = 0x30;
            break;
        default:
            break;
    }

    mfrc522_write(ComIrqReg, mfrc522_read(ComIrqReg) & (~0x80));
    mfrc522_write(FIFOLevelReg, mfrc522_read(FIFOLevelReg) | 0x80);

    mfrc522_write(CommandReg, Idle_CMD);

    for (i = 0; i < send_data_len; i++) {
        mfrc522_write(FIFODataReg, send_data[i]);
    }

    mfrc522_write(CommandReg, cmd);

    if (cmd == Transceive_CMD) {
        mfrc522_write(BitFramingReg, mfrc522_read(BitFramingReg) | 0x80);
    }

    i = 2000;
    do {
        n = mfrc522_read(ComIrqReg);
        i--;
    } while ((i != 0) && !(n & 0x01) && !(n & waitIRq));

    mfrc522_write(BitFramingReg, mfrc522_read(BitFramingReg) & (~0x80));

    if (i != 0) {
        if (!(mfrc522_read(ErrorReg) & 0x1B)) {
            status = CARD_FOUND;
            if (n & irqEn & 0x01) {
                status = CARD_NOT_FOUND;
            }

            if (cmd == Transceive_CMD) {
                n = mfrc522_read(FIFOLevelReg);
                lastBits = mfrc522_read(ControlReg) & 0x07;
                *back_data_len = lastBits ? (n - 1) * 8 + lastBits : n * 8;

                if (n == 0) {
                    n = 1;
                }
                if (n > MAX_LEN) {
                    n = MAX_LEN;
                }

                for (i = 0; i < n; i++) {
                    back_data[i] = mfrc522_read(FIFODataReg);
                    //xil_printf("card data : %x \n",back_data[i]);
                }
            }
        } else {
            status = ERROR;
        }
    }

    return status;
}

// RFID READER 초기화 함수
void rfid_reader_init(void)
{
	mfrc522_init();
	sleep(1);    // wait for RFID init

	readData = mfrc522_read(VersionReg);
	if (readData == 0x92)
	{
		//printf("MIFARE RC522v2\n");
		//printf("Detected !!!\n");
	}
	else if (readData == 0x91 || readData == 0x90)
	{
		//printf("MIFARE RC522v1\n");
		//printf("Detected !!!\n");
	}
	else
	{
		//printf("No RFID Reader found !!!\n");
	}
}

uint8_t mfrc522_get_card_serial(uint8_t *serial_out)
{
    uint8_t status;
    uint8_t i;
    uint8_t serNumCheck = 0;
    uint32_t unLen;

    // BitFramingReg 설정 (TxLastBists = BitFramingReg[2..0])
    mfrc522_write(BitFramingReg, 0x00);

    // 카드와의 통신 시작 (PICC_ANTICOLL 명령 및 데이터 송신)
    serial_out[0] = PICC_ANTICOLL;
    serial_out[1] = 0x20;
    status = mfrc522_to_card(Transceive_CMD, serial_out, 2, serial_out, &unLen);

    // CARD_FOUND 상태일 때 카드 시리얼 번호 확인
    if (status == CARD_FOUND)
    {
        // 카드 시리얼 번호의 체크섬을 확인
        for (i = 0; i < 4; i++)
        {
            serNumCheck ^= serial_out[i];
        }

        // 시리얼 번호의 체크섬이 일치하지 않으면 에러 처리
        if (serNumCheck != serial_out[i])
        {
            status = ERROR;
        }
    }

    return status;
}

uint8_t mfrc522_request(uint8_t req_mode, uint8_t * tag_type) {
    uint8_t status;
    uint32_t backBits; // The received data bits

    // TxLastBists 설정 (BitFramingReg[2..0])
    mfrc522_write(BitFramingReg, 0x07);

    // 카드 요청 명령 송신
    tag_type[0] = req_mode;
    status = mfrc522_to_card(Transceive_CMD, tag_type, 1, tag_type, &backBits);

    // 상태 및 수신된 비트 확인
    if ((status != CARD_FOUND) || (backBits != 0x10)) {
        status = ERROR;
    }

    return status;
}

extern unsigned int rfidtimer;
extern uint8_t UIstate;
void rfid_tag_processing(void)
{
//	display_tagcard();
//	oledstate = 0;
        if (!rfid_check_flag)   // If not currently checking RFID
        {
            readData = mfrc522_request(PICC_REQALL, rxDataStr);

            // Check if RFID tag is found
            if (readData == CARD_FOUND)
            {
            	oledstate = 1;
            	rfidtimer = 0;
            	UIstate = 1;
                // Clear rxDataStr buffer
                for (int i = 0; i < MAX_LEN; i++)
                    rxDataStr[i] = ' ';

                // Get card serial number
                readData = mfrc522_get_card_serial(rxDataStr);

                // Print RFID serial number
                //xil_printf("rfid:");
                for (int i = 0; i < 5; i++)
                {
                   // xil_printf("%02x ", rxDataStr[i]);
                }
                //xil_printf("\n");
//                display_patient_info();
                //usleep(10000);
            }
            //else oledstate = 0;
        }

}
