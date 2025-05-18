/********************************** (C) COPYRIGHT *******************************
 * File Name          : KEY.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2016/04/12
 * Description        :
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

/******************************************************************************/
#ifndef __CKEY_H
#define __CKEY_H

#ifdef __cplusplus
extern "C" {
#endif

/**************************************************************************************************
 *                                              MACROS
 **************************************************************************************************/


/* Switches (keys) */
#define HAL_CKEY_SW_1                 1  // key1
#define HAL_CKEY_SW_LOCK              2  // key2
#define HAL_CKEY_SW_UNLOCK            3  // key3
#define HAL_CKEY_SW_4                 4  // key4
#define HAL_CKEY_SW_5                 5  // key4
#define HAL_CKEY_SW_POWER_OUT         6  // key4
#define HAL_CKEY_SW_POWER_EN          7  // key4
#define HAL_CKEY_SW_POWER_PWM         8  // key4

/* °´¼ü¶¨Òå */

/* 1 - CKEY */
#define CKEY1_BV                 BV(5)
#define CKEY2_BV                 BV(15)
#define CKEY3_BV                 BV(14)
#define CKEY4_BV                 BV(8)
#define CKEY5_BV                 BV(9)
#define CKEY6_BV                 BV(11)
#define CKEY7_BV                 BV(13)

#define CKEY1_OUT                (R32_PA_OUT)
#define CKEY2_OUT                (R32_PA_OUT)
#define CKEY3_OUT                (R32_PA_OUT)
#define CKEY4_OUT                (R32_PA_OUT)
#define CKEY5_OUT                (R32_PA_OUT)
#define CKEY6_OUT                (R32_PA_OUT)
#define CKEY7_OUT                (R32_PB_OUT)

#define CKEY1_DDR                (R32_PA_DIR |= CKEY1_BV)
#define CKEY2_DDR                (R32_PA_DIR |= CKEY2_BV)
#define CKEY3_DDR                (R32_PA_DIR |= CKEY3_BV)
#define CKEY4_DDR                (R32_PA_DIR |= CKEY4_BV)
#define CKEY5_DDR                (R32_PA_DIR |= CKEY5_BV)
#define CKEY6_DDR                (R32_PA_DIR |= CKEY6_BV)
#define CKEY7_DDR                (R32_PB_DIR |= CKEY7_BV)

#define HAL_TURN_OFF_CKEY(x)   (CKEY##x##_OUT &= (~(CKEY##x##_BV)))
#define HAL_TURN_ON_CKEY(x)   (CKEY##x##_OUT |= CKEY##x##_BV)
/**************************************************************************************************
 * TYPEDEFS
 **************************************************************************************************/

/**************************************************************************************************
 *                                             GLOBAL VARIABLES
 **************************************************************************************************/

/*********************************************************************
 * FUNCTIONS
 */

/**
 * @brief   Initialize the Key Service
 */
void HAL_CKeyInit(void);

/**
 * @brief   This is for internal used by hal_driver
 */
void HAL_CKeyPoll(void);

/**
 * @brief   Configure the Key serivce
 *
 * @param   cback - pointer to the CallBack function
 */
void Hal_CKeyConfig(float level);

/**************************************************************************************************
**************************************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
