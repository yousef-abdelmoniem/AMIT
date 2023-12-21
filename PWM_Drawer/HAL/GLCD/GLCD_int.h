/*
 * GLCD_confih.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Yusseif
 */

#ifndef HAL_GLCD_GLCD_CONFIH_H_
#define HAL_GLCD_GLCD_CONFIH_H_

#define GLCD_PIN_CS01    DIO_PIN_3
#define GLCD_PIN_CS02    DIO_PIN_7

ES_t  GLCD_enuInit(void);

ES_t  GLCD_enuSetAddress(u8 Copy_u8Address);

//ES_t  GLCD_enuSetPage(u8 Copy_u8Page);

ES_t  GLCD_enuDisplayStartLine(u8 Copy_u8Start);

ES_t  GLCD_enuWriteData(u8 Copy_u8Data);

ES_t  GLCD_enuReadData(void);

ES_t GLCD_enuSendString(const char * data);

ES_t GLCD_DisplayNum(u16 Copy_u16num);
#endif /* HAL_GLCD_GLCD_CONFIH_H_ */
