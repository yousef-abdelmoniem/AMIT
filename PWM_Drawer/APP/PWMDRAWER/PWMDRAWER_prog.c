/*
 * PWMDRAWER_prog.c
 *
 *  Created on: Dec 12, 2023
 *      Author: Yusseif
 */

#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"

#include "../../MCAL/DIO/DIO_int.h"
#include "../../HAL/GLCD/GLCD_int.h"
#include "../../HAL/LCD/LCD_int.h"
#include "../../HAL/ICU/ICU_int.h"
#include<util/delay.h>
ES_t PWMDRAWER_enuInit(void){
	GLCD_enuInit();
	ICU_vidInit();
	GLCD_enuSetAddress(0);
	GLCD_enuSetPage(0);
	_delay_ms(3);
}

ES_t PWMDRAWER_DrawDC_FREQ(void){
	ICU_vidStartCapture();
	ICU_vidCalculatePWMParams();

	_delay_ms(30);
	GLCD_enuSetAddress(0);
	GLCD_enuSetPage(0);
	GLCD_enuSendString("frequency");
	GLCD_enuSetPage(1);
	GLCD_enuSendString("=");
	GLCD_enuSetPage(2);
	GLCD_DisplayNum(ICU_u16GetFrequency());
	_delay_ms(30);
//	GLCD_enuSetAddress(70);
//	GLCD_enuSetPage(2);
//	GLCD_enuSendString("dc=");
//	GLCD_DisplayNum(ICU_u8GetDutyCycle());
	_delay_ms(30);

}
ES_t PWMDRAWER_DrawGLCD(void){
	GLCD_enuInit();
	ICU_vidInit();
	GLCD_enuSetAddress(0);
	GLCD_enuSetPage(0);
	GLCD_enuSendString("frequency = ");
	GLCD_enuSetAddress(90);
	GLCD_enuSetPage(0);
	GLCD_enuSendString("khz");
	GLCD_enuSetPage(2);
	GLCD_enuSetAddress(1);
	GLCD_enuSendString("dc = ");
	ICU_vidStartCapture();
	GIE_vidEnable();
	while(1){
	ICU_vidCalculatePWMParams();
	GLCD_enuSetAddress(63);
	GLCD_enuSetPage(0);
	GLCD_DisplayNum(ICU_u16GetFrequency());
	GLCD_enuSetPage(2);
	GLCD_enuSetAddress(30);
	GLCD_DisplayNum(ICU_u8GetDutyCycle());
	ICU_vidStartCapture();
	GLCD_enuSetPage(6);
	GLCD_enuSetAddress(0);
//	GLCD_enuSendString("%");
//	GLCD_DisplayNum(ICU_u16GetFrequency());
	GLCD_enuSendString("HFLRHFLRHFLRHFLRHFLRHFLRH");

	}

}
ES_t PWMDRAWER_DrawLCD(void){
	u8 duty;
		u16 freq;
		ICU_vidInit();
		LCD_enuInit();
		LCD_enuSendString("Duty = ");
		LCD_enuGotoXY(2,1);
		LCD_enuSendString("Freq = ");
//		LCD_enuWriteIntegarNum(-180);

		GIE_vidEnable();
		ICU_vidStartCapture();
		while(1)
		{
			ICU_vidCalculatePWMParams();
			duty = ICU_u8GetDutyCycle();
			*((u8*)0x35)= duty;
			freq = ICU_u16GetFrequency();
			*((u8*)0x34)= freq;

			if (duty < 100)
			{
				LCD_enuGotoXY(1, 8);
				LCD_enuSendString("   %");
				LCD_enuGotoXY(1, 8);
//				LCD_enuWriteIntegarNum(duty);
				LCD_enuGotoXY(2, 8);
				LCD_enuSendString("    Hz");
				LCD_enuGotoXY(2, 8);
//				LCD_enuWriteIntegarNum(freq);

				ICU_vidStartCapture();
			}
		}
}
//ES_t PWMDRAWER_DrawGLCD(u8 Copy_u8Page, u8 Copy_u8Address){
//	GLCD_enuInit();
//
//	GLCD_enuSetAddress(Copy_u8Page);
//	GLCD_enuSetPage(Copy_u8Address);



//}
