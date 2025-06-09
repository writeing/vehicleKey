/********************************** (C) COPYRIGHT *******************************
 * File Name          : hidconsumer.h
 * Author             : WCH
 * Version            : V1.0
 * Date               : 2018/12/13
 * Description        :
 *********************************************************************************
 * Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
 * Attention: This software (modified or not) and binary are used for 
 * microcontroller manufactured by Nanjing Qinheng Microelectronics.
 *******************************************************************************/

#ifndef HIDCONSUMER_H
#define HIDCONSUMER_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************************************************************
 * INCLUDES
 */

/*********************************************************************
 * CONSTANTS
 */

// Task Events
#define START_DEVICE_EVT          0x0001
#define START_REPORT_EVT          0x0002
#define START_PARAM_UPDATE_EVT    0x0004
#define START_RSSI_UPDATE_EVT     0x0008
#define VEHICLE_UPDATE_EVT        0x0010
#define CONFIG_VEHICLE_POWER_LEVEL    1.8

/*********************************************************************
 * MACROS
 */

/*********************************************************************
 * FUNCTIONS
 */

/*********************************************************************
 * GLOBAL VARIABLES
 */
typedef enum
{
    STATUS_CONNECTED = 0x01,
    STATUS_DISCONNECT = 0x02,
    STATUS_UNLOCK = 0x03,
    STATUS_USER_OPEN = 0x04,
    STATUS_USER_KEEP = 0x05,    

    STATUS_PAIRING = 0x10,    
    STATUS_USER_CLOSE = 0x20,
    STATUS_NO_PAIR = 0x30,
    STATUS_ERROR = 0x40,

    STATUS_SLEEP = 0x80,
}enum_led_status;

enum
{
    KEEP_UNLOCK,
    VEHICLE_KEY_POWER,
    UNLOCK,    
};
/*
 * Task Initialization for the BLE Application
 */
extern void HidEmu_Init(void);
extern void initKeyUser(void);
extern void flashResetMasterMac(void);
extern void loopVehicleControl(void);
extern void bleDistanceModeControl(void);
extern void setThreeLed (int color);
extern void setVehicleLedStatusWork(enum_led_status status);
extern void initVehicleControl();
extern void setBleConenctStatus(int status);
extern void setBleKeyStatus(int status,BOOL sw);
extern void hidRssiCB( uint16_t connHandle, int8_t newRSSI );
extern void saveModeFlash(int mode);
extern int getDistacnceMode(void);
/*
 * Task Event Processor for the BLE Application
 */
extern uint16_t HidEmu_ProcessEvent(uint8_t task_id, uint16_t events);


/*********************************************************************
*********************************************************************/

#ifdef __cplusplus
}
#endif

#endif
