/*
 * GLCD_confih.h
 *
 *  Created on: Dec 10, 2023
 *      Author: Yusseif
 */

#ifndef HAL_GLCD_GLCD_CONFIG_H_

#define HAL_GLCD_GLCD_CONFIG_H_
/*********** GROUP A ****************/
#define GLCD_GROUP_B     DIO_GROUP_B
#define GLCD_PIN_0       DIO_PIN_0
#define GLCD_PIN_1       DIO_PIN_1
#define GLCD_PIN_2       DIO_PIN_2
#define GLCD_PIN_3       DIO_PIN_3
#define GLCD_PIN_4       DIO_PIN_4
#define GLCD_PIN_5       DIO_PIN_5
#define GLCD_PIN_6       DIO_PIN_6
#define GLCD_PIN_7       DIO_PIN_7
/*********** GROUP B ****************/

#define GLCD_GROUP_A     DIO_GROUP_A
#define GLCD_PIN_RS      DIO_PIN_5
#define GLCD_PIN_RW      DIO_PIN_1
#define GLCD_PIN_ENABLE  DIO_PIN_2
#define GLCD_PIN_CS01    DIO_PIN_3
#define GLCD_PIN_CS02    DIO_PIN_7
#define GLCD_PIN_RESET   DIO_PIN_0

/****************CHOOSE IF CS01 OR CS02 OR BOTH********************/
/****************WE DO NOT RECOMEND SELECTION ONE CHIP********************/
#define GLCD_MODE        BOTH
                  




#endif /* HAL_GLCD_GLCD_CONFIG_H_ */
