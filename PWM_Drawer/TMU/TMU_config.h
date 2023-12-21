/*
 * TMU_config.h
 *
 *  Created on: Oct 7, 2023
 *      Author: Ahmed El-Gaafrawy
 */

#ifndef TMU_TMU_CONFIG_H_
#define TMU_TMU_CONFIG_H_

/***********************************************************/
/*********** [ TIMER0  -   TIMER1  -   TIMER2 ] ************/
#define TMU_TIMER_CHANNEL                  TIMER2
/***********************************************************/

/***********************************************************/
/******* Write the time of OS Tick in mS [1 - 200] *********/
#define TMU_OS_TICK                         5
/***********************************************************/

/***********************************************************/
/*********** Write the frequency of CPU in KHz *************/
#define TMU_CPU_FREQ                        16000UL
/***********************************************************/

/***********************************************************/
/*********** Write Max number of Tasks [max 10] ************/
#define TMU_MAX_NUM_TASKS                  4
/***********************************************************/

#endif /* TMU_TMU_CONFIG_H_ */