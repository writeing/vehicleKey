/* 头文件包含 */
#include "CONFIG.h"
#include "HAL.h"
#include "hidconsumer.h"
static BOOL cur_lock_status = FALSE;
static float power_level_pwm = 1.5;
/**
 * @brief 
 * 
 * @param index  [1-5]
 */
void hal_set_on_Ckey(int index)
{
    switch (index) {
        case 1:
            HAL_TURN_ON_CKEY(1);
        break;
        case 2:
            HAL_TURN_ON_CKEY(2);
        break;
        case 3:
            HAL_TURN_ON_CKEY(3);
        break;
        case 4:
            HAL_TURN_ON_CKEY(4);
        break;
        case 5:
            HAL_TURN_ON_CKEY(5);
        break;
        case 6:
            HAL_TURN_ON_CKEY(6);
        break;
        case 7:
            HAL_TURN_ON_CKEY(7);
        break;                
    }
}
/**
 * @brief 
 * 
 * @param index  [1-5]
 */
void hal_set_off_Ckey(int index)
{
        switch (index) {
        case 1:
            HAL_TURN_OFF_CKEY(1);
        break;
        case 2:
            HAL_TURN_OFF_CKEY(2);
        break;
        case 3:
            HAL_TURN_OFF_CKEY(3);
        break;
        case 4:
            HAL_TURN_OFF_CKEY(4);
        break;
        case 5:
            HAL_TURN_OFF_CKEY(5);
        break;
        case 6:
            HAL_TURN_OFF_CKEY(6);
        break;
        case 7:
            HAL_TURN_OFF_CKEY(7);
        break;                
    }
}
void HAL_CKeyInit()
{
    CKEY1_DDR;
    CKEY2_DDR;
    CKEY3_DDR;
    CKEY4_DDR;
    CKEY5_DDR;
    CKEY6_DDR;
    CKEY7_DDR;
    tmos_start_task(halTaskID, HAL_CKEY_UPDATE_EVT, MS1_TO_SYSTEM_TIME(1000)); /* Kick off polling */
    GPIOA_ModeCfg(GPIO_Pin_10, GPIO_ModeOut_PP_5mA); // PA12 - PWM4
    PWMX_CLKCfg(4);
    PWMX_CycleCfg(PWMX_Cycle_64);                     // 周期 = 64*cycle
}

void hal_set_pwm_power()
{   
    if(power_level_pwm < 1.2)
        power_level_pwm = 1.2;
    if(power_level_pwm >= 3.0)
        power_level_pwm = 2.9;        
    int simple = ((power_level_pwm - 1.2) / (3.0 - 1.2))*100;
    simple = (int)((100 - simple) *0.4);
    PRINT("simple:%d\n",(uint8_t)(0.64 * simple) );
    PWMX_ACTOUT(CH_PWM4, (uint8_t)(0.64 * simple)  , Low_Level, ENABLE);  // 25% 占空比
}

// 
/**
 * @brief set vehicle key control,system open
 * 
 * @param sw  false:close  true:open
 */
void HAL_setVehicleKeyCtl(BOOL sw)
{
    if(sw == TRUE)
    {
        hal_set_off_Ckey(HAL_CKEY_SW_POWER_EN);
        DelayMs(10);
        hal_set_pwm_power();
        DelayMs(10);
        hal_set_on_Ckey(HAL_CKEY_SW_POWER_OUT);
        DelayMs(10);
    }
    if(sw == FALSE)
    {
        hal_set_off_Ckey(HAL_CKEY_SW_POWER_OUT);
        power_level_pwm = 3.0;
        hal_set_pwm_power();
        hal_set_on_Ckey(HAL_CKEY_SW_POWER_EN);
        
    }
}
/**
 * @brief keep vehicle status 
 * 
 * @param sw  True:open  false:close
 */
void HAL_keepVehicleKeyStatus(BOOL sw)
{
    cur_lock_status = sw;
}

/**
 * @brief 
 * 
 * @param lock true:unlock false:lock
 */
void HAL_setVehicleKeyLock(BOOL lock)
{
    if(lock == TRUE)
    {
        hal_set_on_Ckey(HAL_CKEY_SW_LOCK);
        DelayMs(100);
        hal_set_off_Ckey(HAL_CKEY_SW_LOCK);
    }
    if(lock == FALSE)
    {
        hal_set_on_Ckey(HAL_CKEY_SW_UNLOCK);
        DelayMs(100);
        hal_set_off_Ckey(HAL_CKEY_SW_UNLOCK);
    }
}
void HAL_CKeyPoll(void)
{
    
}
void Hal_CKeyConfig(float level)
{   
    power_level_pwm = level;
    HAL_setVehicleKeyCtl(TRUE);
}
