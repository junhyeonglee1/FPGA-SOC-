/*
 * rfid_main.h
 *
 *  Created on: 2024. 9. 23.
 *      Author: HARMAN-22
 */

#ifndef SRC_RFID_MAIN_H_
#define SRC_RFID_MAIN_H_

void spi_init();
uint8_t mfrc522_read(uint8_t addr);
void mfrc522_write(uint8_t addr, uint8_t value);
void mfrc522_init();
uint8_t mfrc522_to_card(uint8_t cmd, uint8_t *send_data, uint8_t send_data_len, uint8_t *back_data, uint32_t *back_data_len);
uint8_t mfrc522_get_card_serial(uint8_t *serial_out);
void rfid_reader_init(void);
uint8_t mfrc522_request(uint8_t req_mode, uint8_t * tag_type);
void rfid_tag_processing(void);


#endif /* SRC_RFID_MAIN_H_ */
