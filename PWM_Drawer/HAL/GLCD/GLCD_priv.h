/*
 * GLCD_confih.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Yusseif
 */

#ifndef HAL_GLCD_GLCD_CONFIH_H_
#define HAL_GLCD_GLCD_CONFIH_H_


static ES_t enuWriteData(u8 Copy_u8Data);
static ES_t enuDrawChar(u8 Copy_u8char);
static ES_t getAddress(void);
static ES_t getPage(void);
static ES_t GOTOX(u8 Copy_u8Page);
static ES_t GOTOY(u8 Copy_u8Address);


#define CS01         21
#define CS02         12
#define BOTH         13

#define GLCD_RIGHT            128
#define GLCD_LEFT             64

#define GLCD_MAX_PAGE     7
#define GLCD_MAX_COL      64


#endif /* HAL_GLCD_GLCD_CONFIH_H_ */
