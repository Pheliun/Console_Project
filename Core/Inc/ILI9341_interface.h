#ifndef INC_ILI9341_INTERFACE_H_
#define INC_ILI9341_INTERFACE_H_

#define RED_CLR 0xF800
#define WHITE_CLR 0xFFFF
int init_ILI9341();
int columnAddressSet(uint8_t start_col, uint8_t end_col);
int pageAddressSet(uint8_t start_pag, uint8_t end_pag);
int writeMemoryContinue(uint8_t clr, uint8_t start_pag, uint8_t end_pag, uint8_t start_col, uint8_t end_col);
int displayInversionON();
int displayInversionOFF();
int ClearScreen(uint16_t clr, uint8_t start_col, uint8_t end_col, uint8_t start_pag, uint8_t end_pag);


#endif /* INC_ILI9341_INTERFACE_H_ */
