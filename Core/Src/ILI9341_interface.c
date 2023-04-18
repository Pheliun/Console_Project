#include "stm32f1xx_hal.h"
#include "ILI9341_interface.h"
#define CMD_SOFTRST 0x01
#define CMD_COLADDRSET 0x2A
#define CMD_PAGADDRSET 0x2B
#define CMD_MEMWRCON 0x3C
#define CMD_DSPINVON 0x21
#define CMD_DSPINVOFF 0x20

uint16_t red_color = (uint16_t) ((255<<11) | (0<<5) | 0);
uint16_t white_color = (uint16_t) ((255<<11) | (255<<5) | 255);

extern SPI_HandleTypeDef hspi1;

/* ----------ILI9341 INTERFACE ------------*/

int init_ILI9341(){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); //CS Low

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); //DC Low -> Command

	HAL_SPI_Transmit(&hspi1, (uint8_t*)CMD_SOFTRST, 1, HAL_MAX_DELAY); // Sends Soft Reset to the Screen Driver
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //CS High

	return 1; //Successful return
}

int columnAddressSet(uint8_t start_col, uint8_t end_col){
	size_t buf_len = 4;
	uint8_t buffer[buf_len];

	buffer[0] = (start_col >> 8) & 0xFF; // High byte of start column
	buffer[1] = start_col & 0xFF; // Low byte of start column
	buffer[2] = (end_col >> 8) & 0xFF; // High byte of end column
	buffer[3] = end_col & 0xFF; // Low byte of end column

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); //CS Low

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); //DC Low -> Command
	HAL_SPI_Transmit(&hspi1, (uint8_t*)CMD_COLADDRSET, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); // DC High -> Data
	HAL_SPI_Transmit(&hspi1, (uint8_t*)buffer, buf_len, HAL_MAX_DELAY); //sets column address

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //CS High

	return 1; //Successful return
}

int pageAddressSet(uint8_t start_pag, uint8_t end_pag){
	size_t buf_len = 4;
	uint8_t buffer[buf_len];

	buffer[0] = (start_pag >> 8) & 0xFF; // High byte of start column
	buffer[1] = start_pag & 0xFF; // Low byte of start column
	buffer[2] = (end_pag >> 8) & 0xFF; // High byte of end column
	buffer[3] = end_pag & 0xFF; // Low byte of end column

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); //CS Low

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); //DC Low -> Command
	HAL_SPI_Transmit(&hspi1, (uint8_t*)CMD_PAGADDRSET, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); // DC High -> Data
	HAL_SPI_Transmit(&hspi1, (uint8_t*)buffer, buf_len, HAL_MAX_DELAY); //sets page address

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //CS High

	return 1; //Successful return
}

int writeMemoryContinue(uint8_t clr,  uint8_t start_col, uint8_t end_col, uint8_t start_pag, uint8_t end_pag){

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); //CS Low

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); //DC Low -> Command
	HAL_SPI_Transmit(&hspi1, (uint8_t*)CMD_MEMWRCON, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_SET); // DC High -> Data
	for (int i=0; i<(start_pag-end_pag+1)*(start_col-end_col+1);i++){
		HAL_SPI_Transmit(&hspi1, &clr, 1, HAL_MAX_DELAY); //sets page address
	}
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //CS High

	return 1; //Successful return
}

int displayInversionON(){

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); //CS Low

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); //DC Low -> Command
	HAL_SPI_Transmit(&hspi1, (uint8_t*)CMD_DSPINVON, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //CS High

	return 1; //Successful return
}

int displayInversionOFF(){

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_RESET); //CS Low

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, GPIO_PIN_RESET); //DC Low -> Command
	HAL_SPI_Transmit(&hspi1, (uint8_t*)CMD_DSPINVOFF, 1, HAL_MAX_DELAY);

	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, GPIO_PIN_SET); //CS High

	return 1; //Successful return
}

int ClearScreen(uint8_t start_col, uint8_t end_col, uint8_t start_pag, uint8_t end_pag){
	columnAddressSet((uint8_t)0,(uint8_t)320);
	pageAddressSet(0, 240);
	writeMemoryContinue(red_color,(uint8_t) 0,(uint8_t) 320,(uint8_t) 0,(uint8_t) 240);
	columnAddressSet(start_col, end_col);
	pageAddressSet(start_pag, end_pag);

	return 1;
}


