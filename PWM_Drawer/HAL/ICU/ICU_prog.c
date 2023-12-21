/*
 * ICU_prog.c
 *
 *  Created on: Oct 13, 2023
 *      Author: Ahmed El-Gaafrawy
 */
#include "../../LIB/stdTypes.h"
#include "../../LIB/errorState.h"

#include "../../MCAL/EXTI/EXTI_int.h"
#include "../../MCAL/Timer0/Timer0_int.h"
#include "../../MCAL/DIO/DIO_int.h"

#include "ICU_config.h"
#include "ICU_priv.h"

static ICU_t LOC_strICUParams ={0};

static ICU_State_t LOC_enuICUStateMachine = IDLE;

static u16 LOC_u16TimerOvfCounts;
static u8 LOC_u8DutyCycle = 0xff;
static u16 LOC_u16Frequency = 0xffff;

void ICU_vidInit(void)
{
    Timer0_vidInit();
    EXTI_enuInit();
    DIO_enuSetPinDirection(DIO_GROUP_D, DIO_PIN_3, DIO_INPUT);
    DIO_enuSetPinValue(DIO_GROUP_D, DIO_PIN_3, DIO_FLOAT);

    EXTI_enuSetCallBack(EXTI_INT1 , vidReadingTask);
    Timer_vidCallBack(vidTimerCallBack);
    Timer_vidEnableInterrupt();
}


void ICU_vidCalculatePWMParams(void)
{
    if (LOC_enuICUStateMachine == IDLE)
    {
        u16 Local_u16TonCounts = (LOC_strICUParams.u8TonCounts + (LOC_strICUParams.u8TonOvfCounts*256UL));
        u16 Local_u16TcycleCounts = (LOC_strICUParams.u8TcCounts + (LOC_strICUParams.u8TcOvfCounts*256UL));
    
        LOC_u8DutyCycle = (u8)((Local_u16TonCounts *100UL)/Local_u16TcycleCounts);
    
        LOC_u16Frequency = (u16)((16000000UL / (Local_u16TcycleCounts * 8UL)));
    }    
}

void ICU_vidStartCapture(void)
{
    if (LOC_enuICUStateMachine == IDLE)
    {
        LOC_enuICUStateMachine = ICU_FIRST_RISING;
        EXTI_enuEnableInterrupt(EXTI_INT0);
        Timer_vidEnableInterrupt();
    }
}


u8 ICU_u8GetDutyCycle(void)
{
    u8 Local_u8Duty =0xff;
    if (LOC_enuICUStateMachine == IDLE)
    {
        Local_u8Duty = LOC_u8DutyCycle;
    }
    return Local_u8Duty;
}

u16 ICU_u16GetFrequency(void)
{
    u16 Local_u16freq =0xffff;
    if (LOC_enuICUStateMachine == IDLE)
    {
        Local_u16freq = LOC_u16Frequency;
    }
    return Local_u16freq;
}


static void vidTimerCallBack(void)
{
    LOC_u16TimerOvfCounts++;
}

static void vidReadingTask(void)
{
    switch (LOC_enuICUStateMachine)
    {
    case ICU_FIRST_RISING:
        Timer_vidSetTimerCounts(0);
        LOC_u16TimerOvfCounts = 0;
        EXTI_enuSetSenseLevel(EXTI_INT0 , EXTI_FALLING);
        LOC_enuICUStateMachine = ICU_FALLING;
        break;

    case ICU_FALLING:
        LOC_strICUParams.u8TonCounts = Timer_u8GetTimerCounts();
        LOC_strICUParams.u8TonOvfCounts = LOC_u16TimerOvfCounts;
        EXTI_enuSetSenseLevel(EXTI_INT0 , EXTI_RISING);
        LOC_enuICUStateMachine = ICU_SECOND_RISING;
        break;

    case ICU_SECOND_RISING:
        LOC_strICUParams.u8TcCounts = Timer_u8GetTimerCounts();
        LOC_strICUParams.u8TcOvfCounts = LOC_u16TimerOvfCounts;
        EXTI_enuDisableInterrupt(EXTI_INT0);
        Timer_vidDisableInterrupt();
        LOC_enuICUStateMachine = IDLE;
        break;
    
    default:
        break;
    }
}
