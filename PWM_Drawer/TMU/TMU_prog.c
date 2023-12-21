/*
 * TMU_prog.c
 *
 *  Created on: Oct 7, 2023
 *      Author: Ahmed El-Gaafrawy
 */
#include "../LIB/stdTypes.h"

#include "TMU_config.h"
#include "TMU_priv.h"

#if TMU_TIMER_CHANNEL == TIMER0 || TMU_TIMER_CHANNEL == TIMER2
static u16 LOC_u16NumOfOvfs = 0;
static u16 LOC_u16CountISRs = 0;
static u8 LOC_u8Preload = 0;
#endif

#if TMU_MAX_NUM_TASKS >=1 && TMU_MAX_NUM_TASKS <= 10
static TCB_t LOC_astrTasks [ TMU_MAX_NUM_TASKS ];
#else
    #error Num of Tasks in TMU is invalid 
#endif

static u32 LOC_u32OsTicks =0;


void TMU_vidInit(void)
{
    #if TMU_TIMER_CHANNEL == TIMER0
        #if TMU_OS_TICK >= 1 && TMU_OS_TICK <= 200
            //OVF , 1024 , dis OC0
            TCCR0 = 0x05;
            u32 Local_u32Counts = (TMU_OS_TICK * (u32)TMU_CPU_FREQ) / (1024);
            
            LOC_u16NumOfOvfs = (Local_u32Counts + 255) / (256);
            LOC_u16CountISRs = LOC_u16NumOfOvfs;

            LOC_u8Preload = (256UL - (Local_u32Counts % 256UL));

            TCNT0 = LOC_u8Preload;
            TIMSK |= (1<<0);
        #else
            #error OS Tick value in TMU in invalid
        #endif
    #elif TMU_TIMER_CHANNEL == TIMER1
        #if TMU_OS_TICK >= 1 && TMU_OS_TICK <= 200
            // CTC on OCR1A , dis OC1A,OC1B , pres = 64 , 
            TCCR1A = 0x00; 
            TCCR1B = 0x0B;

            u16 Local_u16Counts = (TMU_OS_TICK * (u32)TMU_CPU_FREQ) / (64);

            OCR1AH = (Local_u16Counts >> 8);
            OCR1AL = (u8)Local_u16Counts;

            TIMSK |= (1<<4);

        #else
            #error OS Tick value in TMU in invalid
        #endif
    #elif TMU_TIMER_CHANNEL == TIMER2
        #if TMU_OS_TICK >= 1 && TMU_OS_TICK <= 200
            //OVF , 1024 , dis OC2
            TCCR2 = 0x07;
            u32 Local_u32Counts = (TMU_OS_TICK * (u32)TMU_CPU_FREQ) / (1024);
            
            LOC_u16NumOfOvfs = (Local_u32Counts + 255) / (256);
            LOC_u16CountISRs = LOC_u16NumOfOvfs;

            LOC_u8Preload = (256UL - (Local_u32Counts % 256UL));

            TCNT2 = LOC_u8Preload;
            TIMSK |= (1<<6);
        #else
            #error OS Tick value in TMU in invalid
        #endif
    #else 
        #error Timer channel selection in TMU in invalid
    #endif
}

void TMU_vidCreateTask(void(*Copy_pfunAppFun)(void*), void * Copy_pvidParameter, 
                u16 Copy_u16Periodicity , u8 Copy_u8Priority)
{
    if (Copy_u8Priority < TMU_MAX_NUM_TASKS)
    {
        LOC_astrTasks[ Copy_u8Priority ].pfunTask       = Copy_pfunAppFun;
        LOC_astrTasks[ Copy_u8Priority ].pvidParameter  = Copy_pvidParameter;
        LOC_astrTasks[ Copy_u8Priority ].u16Periodicity = Copy_u16Periodicity;
        LOC_astrTasks[ Copy_u8Priority ].state          = READY;
    }
}

void TMU_vidStartScheduler(void)
{
    u32 Local_u32Temp = 0;
    asm("SEI");
    while (1)
    {
        if (LOC_u32OsTicks > Local_u32Temp)
        {
            Local_u32Temp = LOC_u32OsTicks;
            // run scheduler
            // for (u8 u8Index = 0 ; u8Index < TMU_MAX_NUM_TASKS ; u8Index++) // 0 highest
            for (s8 s8Index = TMU_MAX_NUM_TASKS-1 ; s8Index >=0 ; s8Index --) // TMU_MAX_NUM_TASKS -1  -> highest
            {
                if ((LOC_astrTasks[s8Index].pfunTask != NULL) && 
                    (LOC_astrTasks[s8Index].state == READY) &&
                    ((LOC_u32OsTicks % LOC_astrTasks[s8Index].u16Periodicity) == 0))
                {
                    //dispatcher
                    LOC_astrTasks[s8Index].pfunTask ( LOC_astrTasks[s8Index].pvidParameter );
                }
            }
        }
    }
    
}

void TMU_vidDelete(u8 Copy_u8Priority)
{
    if (Copy_u8Priority < TMU_MAX_NUM_TASKS)
    {
        LOC_astrTasks[ Copy_u8Priority ].state = DELETED;
        LOC_astrTasks[ Copy_u8Priority ].pfunTask = NULL;
    }
}

void TMU_vidResume(u8 Copy_u8Priority)
{
    if (Copy_u8Priority < TMU_MAX_NUM_TASKS)
    {
        LOC_astrTasks[ Copy_u8Priority ].state = READY;
    }
}
void TMU_vidPause(u8 Copy_u8Priority)
{
    if (Copy_u8Priority < TMU_MAX_NUM_TASKS)
    {
        LOC_astrTasks[ Copy_u8Priority ].state = SUSPENDED;
    }
}


#if TMU_TIMER_CHANNEL == TIMER0 
void __vector_11 (void)__attribute__((signal));
void __vector_11 (void)
{
    LOC_u16CountISRs--;
    if (! LOC_u16CountISRs)
    {
        TCNT0 = LOC_u8Preload;

        LOC_u32OsTicks++;

        LOC_u16CountISRs = LOC_u16NumOfOvfs;
    }
}
#elif TMU_TIMER_CHANNEL == TIMER1
void __vector_7 (void)__attribute__((signal));
void __vector_7 (void)
{
    LOC_u32OsTicks++;
}
#elif TMU_TIMER_CHANNEL == TIMER2
void __vector_5 (void)__attribute__((signal));
void __vector_5 (void)
{
    LOC_u16CountISRs--;
    if (! LOC_u16CountISRs)
    {
        TCNT2 = LOC_u8Preload;

        LOC_u32OsTicks++;

        LOC_u16CountISRs = LOC_u16NumOfOvfs;
    }
    
}
#endif
