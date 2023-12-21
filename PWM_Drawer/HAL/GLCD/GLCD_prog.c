/*
 * GLCD_prog.c
 *
 *  Created on: Dec 10, 2023
 *      Author: Yusseif
 */
#include "../../LIB/errorState.h"
#include "../../LIB/stdTypes.h"

#include "../../MCAL/DIO/DIO_int.h"

#include "../../HAL/GLCD/GLCD_priv.h"
#include "../../HAL/GLCD/GLCD_config.h"

#include <util/delay.h>
static u8 LOCAL_u8Counter = 0;
static u8 LOCAL_u8Page = 0;
static u8 LOCAL_u8Address = 0;

static ES_t GOTOX(u8 Copy_u8Page){

	if(Copy_u8Page<8){

	DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RS, DIO_LOW);
	DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RW, DIO_LOW);

    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_0,((Copy_u8Page >> 0) & 1));
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_1,((Copy_u8Page >> 1) & 1));
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_2,((Copy_u8Page >> 2) & 1));
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_3,DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_4,DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_5,DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_6,DIO_LOW);
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_7,DIO_HIGH);


    _delay_ms(3);
        DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_HIGH);
        _delay_ms(1);
        DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_LOW);
//        LOCAL_u8Page=Copy_u8Page;


	}
}
static ES_t GOTOY(u8 Copy_u8Address){
	LOCAL_u8Address=Copy_u8Address;

		if(Copy_u8Address < 64){
			DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RS, DIO_LOW);
			DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RW, DIO_LOW);

			DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_HIGH);
			DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS02, DIO_LOW);

			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_0,((Copy_u8Address >> 0) & 1));
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_1,((Copy_u8Address >> 1) & 1));
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_2,((Copy_u8Address >> 2) & 1));
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_3,((Copy_u8Address >> 3) & 1));
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_4,((Copy_u8Address >> 4) & 1));
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_5,((Copy_u8Address >> 5) & 1));
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_6,DIO_HIGH);
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_7,DIO_LOW);

			_delay_ms(2);
			    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_HIGH);
			    _delay_ms(1);
			    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_LOW);


		}else{
			LOCAL_u8Address=Copy_u8Address;


			DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RS, DIO_LOW);
			DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RW, DIO_LOW);

			DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_LOW);
			DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RESET, DIO_HIGH);
			_delay_ms(1);
			DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS02, DIO_HIGH);





			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_0,(((Copy_u8Address-64) >> 0) & 1));
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_1,(((Copy_u8Address-64) >> 1) & 1));
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_2,(((Copy_u8Address-64) >> 2) & 1));
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_3,(((Copy_u8Address-64) >> 3) & 1));
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_4,(((Copy_u8Address-64) >> 4) & 1));
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_5,(((Copy_u8Address-64) >> 5) & 1));
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_6,DIO_HIGH);
			DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_7,DIO_LOW);



			_delay_ms(2);
			    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_HIGH);
			    _delay_ms(1);
			    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_LOW);


		}
}

static ES_t getPage(void){
	return LOCAL_u8Page;
}

static ES_t getAddress(void){
	return LOCAL_u8Address;
}

ES_t GLCD_enuInit() {
    ES_t Local_enuErrorState = ES_NOK;
    #if GLCD_MODE == CS01
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_RS, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_RW, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_RESET, DIO_OUTPUT);


    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RS, DIO_LOW);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RW, DIO_LOW);
    _delay_ms(5);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RESET, DIO_LOW);
    _delay_ms(5);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RESET, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS02, DIO_LOW);


    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_0, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_1, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_2, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_3, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_4, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_5, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_6, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_7, DIO_OUTPUT);

    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_0, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_1, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_2, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_3, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_4, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_5, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_6, DIO_LOW);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_7, DIO_LOW);

    _delay_ms(2);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_LOW);
    _delay_ms(1);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_HIGH);

    #elif GLCD_MODE == CS02
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_CS02, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_RS, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_RW, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_RESET, DIO_OUTPUT);

    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RS, DIO_LOW);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RW, DIO_LOW);
    _delay_ms(5);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RESET, DIO_LOW);
    _delay_ms(5);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RESET, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS02, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_LOW);

    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_0, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_1, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_2, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_3, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_4, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_5, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_6, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_7, DIO_OUTPUT);

    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_0, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_1, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_2, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_3, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_4, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_5, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_6, DIO_LOW);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_7, DIO_LOW);

    _delay_ms(2);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_LOW);
    _delay_ms(1);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_HIGH);

    #elif GLCD_MODE == BOTH
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_CS02, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_RS, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_RW, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_A, GLCD_PIN_RESET, DIO_OUTPUT);

    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RS, DIO_LOW);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RW, DIO_LOW);
    _delay_ms(5);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RESET, DIO_LOW);
    _delay_ms(5);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RESET, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_LOW);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS02, DIO_LOW);

    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_0, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_1, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_2, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_3, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_4, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_5, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_6, DIO_OUTPUT);
    DIO_enuSetPinDirection(GLCD_GROUP_B, GLCD_PIN_7, DIO_OUTPUT);

    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_0, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_1, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_2, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_3, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_4, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_5, DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_6, DIO_LOW);
    DIO_enuSetPinValue(GLCD_GROUP_B, GLCD_PIN_7, DIO_LOW);

    _delay_ms(2);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_HIGH);
    _delay_ms(1);
    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_LOW);


    #else
      #error you must choose from config file

    #endif  

}

ES_t GLCD_enuSetAddress(u8 Copy_u8Address){
	LOCAL_u8Address=Copy_u8Address;

	if(Copy_u8Address < 64){
		DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RS, DIO_LOW);
		DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RW, DIO_LOW);

		DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_HIGH);
		DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS02, DIO_LOW);

		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_0,((Copy_u8Address >> 0) & 1));
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_1,((Copy_u8Address >> 1) & 1));
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_2,((Copy_u8Address >> 2) & 1));
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_3,((Copy_u8Address >> 3) & 1));
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_4,((Copy_u8Address >> 4) & 1));
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_5,((Copy_u8Address >> 5) & 1));
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_6,DIO_HIGH);
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_7,DIO_LOW);

		_delay_ms(2);
		    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_HIGH);
		    _delay_ms(1);
		    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_LOW);


	}else{



		DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RS, DIO_LOW);
		DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RW, DIO_LOW);

		DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_LOW);
		DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS02, DIO_HIGH);





		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_0,(((Copy_u8Address-64) >> 0) & 1));
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_1,(((Copy_u8Address-64) >> 1) & 1));
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_2,(((Copy_u8Address-64) >> 2) & 1));
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_3,(((Copy_u8Address-64) >> 3) & 1));
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_4,(((Copy_u8Address-64) >> 4) & 1));
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_5,(((Copy_u8Address-64) >> 5) & 1));
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_6,DIO_HIGH);
		DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_7,DIO_LOW);



		_delay_ms(2);
		    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_HIGH);
		    _delay_ms(1);
		    DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_LOW);


	}
}

ES_t GLCD_enuSetPage(u8 Copy_u8Page){
	_delay_ms(3);
	LOCAL_u8Page=Copy_u8Page;

	DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RS, DIO_LOW);
	DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_RW, DIO_LOW);

    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_0,((Copy_u8Page >> 0) & 1));
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_1,((Copy_u8Page >> 1) & 1));
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_2,((Copy_u8Page >> 2) & 1));
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_3,DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_4,DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_5,DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_6,DIO_LOW);
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_7,DIO_HIGH);


    _delay_ms(1);
        DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_HIGH);
        _delay_ms(1);
        DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_LOW);




}

ES_t GLCD_enuDisplayStartLine(u8 Copy_u8Start){
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_0,((Copy_u8Start >> 0) & 1));
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_1,((Copy_u8Start >> 1) & 1));
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_2,((Copy_u8Start >> 2) & 1));
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_3,((Copy_u8Start >> 3) & 1));
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_4,((Copy_u8Start >> 4) & 1));
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_5,((Copy_u8Start >> 5) & 1));
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_6,DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_7,DIO_HIGH);
    _delay_ms(2);
            DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_LOW);
            _delay_ms(1);
            DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_HIGH);
}


static ES_t enuWriteData(u8 Copy_u8Data){



    DIO_enuSetPinValue(GLCD_GROUP_A,GLCD_PIN_RS,DIO_HIGH);
    DIO_enuSetPinValue(GLCD_GROUP_A,GLCD_PIN_RW,DIO_LOW);

    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_0,((Copy_u8Data >> 0) & 1));
//    LOCAL_u8Address++;
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_1,((Copy_u8Data >> 1) & 1));
//    LOCAL_u8Address++;
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_2,((Copy_u8Data >> 2) & 1));
//    LOCAL_u8Address++;
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_3,((Copy_u8Data >> 3) & 1));
//    LOCAL_u8Address++;
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_4,((Copy_u8Data >> 4) & 1));
//    LOCAL_u8Address++;
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_5,((Copy_u8Data >> 5) & 1));
//    LOCAL_u8Address++;
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_6,((Copy_u8Data >> 6) & 1));
//    LOCAL_u8Address++;
    DIO_enuSetPinValue(GLCD_GROUP_B,GLCD_PIN_7,((Copy_u8Data >> 7) & 1));
    LOCAL_u8Address++;


    _delay_ms(2);
        DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_HIGH);
        _delay_ms(1);
        DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_ENABLE, DIO_LOW);

        if(LOCAL_u8Address<64){

        	GOTOX(LOCAL_u8Page);
        	GOTOY(LOCAL_u8Address);
        	_delay_ms(5);
        	DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_HIGH);
        	_delay_ms(1);
        	DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS02, DIO_LOW);

        }else if(LOCAL_u8Address>=64 && LOCAL_u8Address<128){
        	GOTOX(LOCAL_u8Page);
        	GOTOY((LOCAL_u8Address));
        	_delay_ms(5);
        	DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_LOW);
        	_delay_ms(1);
        	DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS02, DIO_HIGH);

        }
        else  if(LOCAL_u8Address>=128){

        	LOCAL_u8Address=0;
        	GOTOY(LOCAL_u8Address);
        	DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS01, DIO_HIGH);
        	_delay_ms(1);
        	DIO_enuSetPinValue(GLCD_GROUP_A, GLCD_PIN_CS02, DIO_LOW);


        }




}


static ES_t enuDrawChar(u8 Copy_u8char){
	switch(Copy_u8char){
	case 'a': ;
		u8 a[5]={0x20,0x54,0x54,0x54,0x78};
		for(int i = 0 ; i<5;i++){
			enuWriteData(a[i]);

		}
		break;

case 'c': ;
		u8 c[5]={0x38, 0x44, 0x44, 0x44, 0x44};
		for(int i = 0 ; i<5;i++){
			enuWriteData(c[i]);
		}
		break;

    case 'd': ;
		u8 d[5]={0x38, 0x44, 0x44, 0x44, 0x7F};
		for(int i = 0 ; i<5;i++){
			enuWriteData(d[i]);
		}
		break;

        case 'e': ;
		u8 e[5]={0x38, 0x54, 0x54, 0x54, 0x18};
		for(int i = 0 ; i<5;i++){
			enuWriteData(e[i]);
		}
		break;
        case 'f': ;
		u8 f[5]={0x04, 0x04, 0x7E, 0x05, 0x05};
		for(int i = 0 ; i<5;i++){
			enuWriteData(f[i]);
		}
		break;

        case 'h': ;
		u8 h[5]={0x7F, 0x08, 0x04, 0x04, 0x78};
		for(int i = 0 ; i<5;i++){
			enuWriteData(h[i]);
		}
		break;
        case 'i': ;
		u8 i1[5]={0x00, 0x44, 0x7D, 0x40, 0x00};
		for(int i = 0 ; i<5;i++){
			enuWriteData(i1[i]);
		}
		break;

        case 'k': ;
		u8 k[5]={0x7F, 0x10, 0x28, 0x44, 0x00};
		for(int i = 0 ; i<5;i++){
			enuWriteData(k[i]);
		}
		break;
        case 'm': ;
		u8 m[5]={0x7C, 0x04, 0x78, 0x04, 0x78};
		for(int i = 0 ; i<5;i++){
			enuWriteData(m[i]);
		}
		break;
        case 'n': ;
		u8 n[5]={0x7C, 0x08, 0x04, 0x04, 0x78};
		for(int i = 0 ; i<5;i++){
			enuWriteData(n[i]);
		}
		break;

        case 'q': ;
		u8 q[5]={0x08, 0x14, 0x14, 0x14, 0x7C};
		for(int i = 0 ; i<5;i++){
			enuWriteData(q[i]);
		}
		break;
        case 'r': ;
		u8 r[5]={0x00, 0x7C, 0x08, 0x04, 0x04};
		for(int i = 0 ; i<5;i++){
			enuWriteData(r[i]);
		}
		break;
        case 't': ;
		u8 t[5]={0x04, 0x04, 0x3F, 0x44, 0x44};
		for(int i = 0 ; i<5;i++){
			enuWriteData(t[i]);
		}
		break;
        case 'u': ;
		u8 u[5]={0x3C, 0x40, 0x40, 0x20, 0x7C};
		for(int i = 0 ; i<5;i++){
			enuWriteData(u[i]);
		}
		break;
        case 'y': ;
		u8 y[5]={0x0C, 0x50, 0x50, 0x50, 0x3C};
		for(int i = 0 ; i<5;i++){
			enuWriteData(y[i]);
		}
		break;
        case 'z': ;
		u8 z[5]={0x44, 0x64, 0x54, 0x4C, 0x44};
		for(int i = 0 ; i<5;i++){
			enuWriteData(z[i]);
		}
		break;

        case ' ': ;
        u8 Z12[3]={0x00, 0x00, 0x00};
        for(int i = 0 ; i<5;i++){
            enuWriteData(Z12[i]);
        }
        break;

        case '=': ;
    	u8 Z11[3]={0x14, 0x14, 0x14,0x14};
    	for(int i = 0 ; i<5;i++){
    		enuWriteData(Z11[i]);
    	}
    	break;
        case '0': ;
    	u8 Z0[5]={0x3E, 0x51, 0x49, 0x45, 0x3E};
    	for(int i = 0 ; i<5;i++){
    		enuWriteData(Z0[i]);
    	}
    	break;
        case '1': ;
    	u8 Z1[5]={0x04, 0x02, 0x7F, 0x00, 0x00};
    	for(int i = 0 ; i<5;i++){
    		enuWriteData(Z1[i]);
    	}
    	break;

        case '2': ;
    	u8 Z2[5]={0x42, 0x61, 0x51, 0x49, 0x46};
    	for(int i = 0 ; i<5;i++){
    		enuWriteData(Z2[i]);
    	}
    	break;
        case '3': ;
    	u8 Z3[5]={0x22, 0x41, 0x49, 0x49, 0x36};
    	for(int i = 0 ; i<5;i++){
    		enuWriteData(Z3[i]);
    	}
    	break;
        case '4': ;
    	u8 Z4[5]={0x18, 0x14, 0x12, 0x7F, 0x10};
    	for(int i = 0 ; i<5;i++){
    		enuWriteData(Z4[i]);
    	}
    	break;

        case '5': ;
    	u8 Z5[5]={0x27, 0x45, 0x45, 0x45, 0x39};
    	for(int i = 0 ; i<5;i++){
    		enuWriteData(Z5[i]);
    	}
    	break;

        case '6': ;
    	u8 Z6[5]={0x3E, 0x49, 0x49, 0x49, 0x32};
    	for(int i = 0 ; i<5;i++){
    		enuWriteData(Z6[i]);
    	}
    	break;

        case '7': ;
    	u8 Z7[5]={0x01, 0x01, 0x71, 0x09, 0x07};
    	for(int i = 0 ; i<5;i++){
    		enuWriteData(Z7[i]);
    	}
    	break;

        case '8': ;
    	u8 Z8[5]={0x36, 0x49, 0x49, 0x49, 0x36};
    	for(int i = 0 ; i<5;i++){
    		enuWriteData(Z8[i]);
    	}
    	break;
        case '9': ;
    	u8 Z9[5]={0x26, 0x49, 0x49, 0x49, 0x3E};
    	for(int i = 0 ; i<5;i++){
    		enuWriteData(Z9[i]);
    	}
    	break;
        case 'H': ;
            	u8 H[8]={0x01,
            			  0x01,
            			  0x01,
            			  0x01,
            			  0x01,
            			  0x01,
            			  0x01,
            			  0x01};
            	for(int i = 0 ; i<5;i++){
            		enuWriteData(H[i]);
            	}
            	break;
        case 'L': ;
                    	u8 L[8]={0x10,
                    			  0x10,
                    			  0x10,
                    			  0x10,
                    			  0x10,
                    			  0x10,
                    			  0x10,
                    			  0x10};
                    	for(int i = 0 ; i<5;i++){
                    		enuWriteData(L[i]);
                    	}
                    	break;
        case 'F': ;
                    	u8 R[5]={
                    			  0x01,
                    			  0x01,
                    			  0x1F,
                    			  0x10,
                    			  0x10};
                    	for(int i = 0 ; i<5;i++){
                    		enuWriteData(R[i]);
                    	}
                    	break;
        case 'R': ;
                    	u8 F[5]={0x10,
                    			  0x10,
                    			  0x1F,
                    			  0x01,
                    			  0x01,
                    			  };
                    	for(int i = 0 ; i<5;i++){
                    		enuWriteData(F[i]);
                    	}
                    	break;
        case '-': ;
            	u8 Z10[5]={0x08, 0x08, 0x08, 0x08, 0x08};
            	for(int i = 0 ; i<5;i++){
            		enuWriteData(Z10[i]);
            	}
            	break;


	default: break;
	}




}
ES_t GLCD_enuSendString(const char * data){


	 while (*data)
	    {
		 enuDrawChar(*data++);

	    }
	 LOCAL_u8Address=0;




}
ES_t GLCD_DisplayNum(u16 Copy_u16num){
if (Copy_u16num < 0) {
	    enuDrawChar('-');
		Copy_u16num = -1 * Copy_u16num;
	}
	u16 u8Local_Digit = 0;
	char str_reversed[5] = "";
	char* str_ptr = str_reversed;
	do {
		u8Local_Digit = Copy_u16num %10;
		*str_ptr = (char)(48 + u8Local_Digit); /* 48 is the ASCII code of '0' */
		Copy_u16num = Copy_u16num/10;
		str_ptr++;
	} while (Copy_u16num> 0);
	do {
		str_ptr--;
		enuDrawChar(*str_ptr);
	} while (str_ptr != str_reversed);
}


