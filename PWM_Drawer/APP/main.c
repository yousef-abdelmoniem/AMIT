/*
 * main.c
 *
 *  Created on: Dec 5, 2023
 *      Author: Yusseif
 */
#include "../LIB/stdTypes.h"
#include "../LIB/errorState.h"

#include "../MCAL/DIO/DIO_int.h"
#include "../HAL/LCD/LCD_int.h"
#include "../HAL/GLCD/GLCD_int.h"
#include "../MCAL/GIE/GIE_int.h"
#include "../TMU/TMU_int.h"
#include "PWMDRAWER/PWMDRAWER_int.h"
#include <util/delay.h>
// Define your continuous pattern




int main() {

//	PWMDRAWER_enuInit();
//	PWMDRAWER_DrawLCD();
//	PWMDRAWER_DrawDC_FREQ();
//	GLCD_enuInit();
//
//	GLCD_enuSendString("HFLH");
	PWMDRAWER_DrawGLCD();
	// Define your continuous pattern
//	const uint8_t continuousPattern[5] =
//			{0x7F, 0x09, 0x09, 0x09, 0x01};
//    // Assuming GLCD_enuInit initializes and clears the screen
//    GLCD_enuInit();
//



//
//                for (int i = 0; i < 8; ++i) {
//                    GLCD_enuWriteData(continuousPattern[i]);
//                }
//
//                for (int i = 0; i < 8; ++i) {
//                                    GLCD_enuWriteData(continuousPattern[i]);
//                                }
//


        // Introduce a delay or other logic as needed



}
//int
//main(void)
//{
//	u8 name []= {
//					0x03,0x04,0x1F,0x00,0x04,0x04,0x04,0x04,// aleph
//					0x00,0x00,0x06,0x09,0x01,0x1E,0x00,0x00,// 7aa'
//					0x00,0x00,0x00,0x00,0x00,0x1F,0x0A,0x06,// mem
//					0x00,0x00,0x00,0x0C,0x04,0x1F,0x00,0x00,// dal
//				};
//
//
//
//
//	LCD_enuInit();
//	LCD_enuSendCommand(0x50); // CGRAM P2
//	for (u8 i =0 ; i<32 ; i++ )
//	{
//		LCD_enuSendData(name[i]);
//	}
//	LCD_enuGotoXY(1 , 10); // DDRAM 1st line , 14th colomn
//	LCD_enuSendCommand (0x04);// decresing DDRAM Counter
//	LCD_enuSendData(2);
//	LCD_enuSendData(3);
//	LCD_enuSendData(4);
//	LCD_enuSendData(5);
////LCD_enuInit();
////LCD_enuSendString("kosom shheeebaa");
//}
