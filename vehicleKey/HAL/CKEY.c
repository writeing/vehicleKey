/* ͷ�ļ����� */
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
void hal_set_on_Ckey (int index) {
    switch (index) {
    case HAL_CKEY_SW_1:
        HAL_TURN_ON_CKEY (1);
        break;
    case HAL_CKEY_SW_LOCK:
        HAL_TURN_ON_CKEY (2);
        break;
    case HAL_CKEY_SW_UNLOCK:
        HAL_TURN_ON_CKEY (3);
        break;
    case HAL_CKEY_SW_4:
        HAL_TURN_ON_CKEY (4);
        break;
    case HAL_CKEY_SW_5:
        HAL_TURN_ON_CKEY (5);
        break;
    case HAL_CKEY_SW_POWER_OUT:
        HAL_TURN_ON_CKEY (6);
        break;
    case HAL_CKEY_SW_POWER_EN:
        HAL_TURN_ON_CKEY (7);
        break;
    }
}

/**
 * @brief
 *
 * @param index  [1-5]
 */
void hal_set_off_Ckey (int index) {
    switch (index) {
    case HAL_CKEY_SW_1:
        HAL_TURN_OFF_CKEY (1);
        break;
    case HAL_CKEY_SW_LOCK:
        HAL_TURN_OFF_CKEY (2);
        break;
    case HAL_CKEY_SW_UNLOCK:
        HAL_TURN_OFF_CKEY (3);
        break;
    case HAL_CKEY_SW_4:
        HAL_TURN_OFF_CKEY (4);
        break;
    case HAL_CKEY_SW_5:
        HAL_TURN_OFF_CKEY (5);
        break;
    case HAL_CKEY_SW_POWER_OUT:
        HAL_TURN_OFF_CKEY (6);
        break;
    case HAL_CKEY_SW_POWER_EN:
        HAL_TURN_OFF_CKEY (7);
        break;
    }
}

void HAL_CKeyInit() {
    CKEY1_DDR;
    CKEY2_DDR;
    CKEY3_DDR;
    CKEY4_DDR;
    CKEY5_DDR;
    CKEY6_DDR;
    CKEY7_DDR;
    tmos_start_task (halTaskID, HAL_CKEY_UPDATE_EVT, MS1_TO_SYSTEM_TIME (1000)); /* Kick off polling */
}

void hal_set_pwm_power() {
    if (power_level_pwm < 1.2)
        power_level_pwm = 1.2;
    if (power_level_pwm >= 3.0)
        power_level_pwm = 2.9;
    int simple = ((power_level_pwm - 1.2) / (2.9 - 1.2)) * 100;
    simple = (int)((100 - simple) * 0.4);
    PRINT ("\nsimple:%d\n", (uint8_t)simple);
    TMR1_Disable();
    simple = 60 * simple;
    TMR1_PWMActDataWidth (simple);
    TMR1_Enable();
}

//
/**
 * @brief set vehicle key control,system open
 *
 * @param sw  false:close  true:open
 */
void HAL_setVehicleKeyPowerCtl (BOOL sw) {
    if (sw == TRUE) {
        hal_set_off_Ckey (HAL_CKEY_SW_POWER_EN);
        DelayMs (10);
        hal_set_pwm_power();
        DelayMs (10);
        hal_set_on_Ckey (HAL_CKEY_SW_POWER_OUT);
        DelayMs (10);
    }
    if (sw == FALSE) {
        hal_set_off_Ckey (HAL_CKEY_SW_POWER_OUT);
        DelayMs (10);
        PWMX_ACTOUT (CH_PWM4, 100, Low_Level, DISABLE);  // 25% ռ�ձ�
        DelayMs (10);
        hal_set_on_Ckey (HAL_CKEY_SW_POWER_EN);
    }
}

/**
 * @brief keep vehicle status
 *
 * @param sw  True:open  false:close
 */
void HAL_keepVehicleKeyStatus (BOOL sw) {
    cur_lock_status = sw;
}

/**
 * @brief
 *
 * @param lock true:unlock false:lock
 */
void HAL_setVehicleKeyLock (BOOL lock) {
    if (lock == TRUE) {
        hal_set_on_Ckey (HAL_CKEY_SW_LOCK);
        DelayMs (100);
        hal_set_off_Ckey (HAL_CKEY_SW_LOCK);
    }
    if (lock == FALSE) {
        hal_set_on_Ckey (HAL_CKEY_SW_UNLOCK);
        DelayMs (100);
        hal_set_off_Ckey (HAL_CKEY_SW_UNLOCK);
    }
}

void HAL_CKeyPoll (void) {
}

void initPwmControl() {
    GPIOA_ResetBits (GPIO_Pin_10);  // ����PWM�� PB22
    GPIOA_ModeCfg (GPIO_Pin_10, GPIO_ModeOut_PP_5mA);

    TMR1_PWMInit (High_Level, PWM_Times_1);
    TMR1_PWMCycleCfg (6000);   // ���� 100us
    TMR1_Disable();
    TMR1_PWMActDataWidth (0);  // ռ�ձ� 50%, �޸�ռ�ձȱ�����ʱ�رն�ʱ��
    TMR1_Enable();
}

void Hal_CKeyConfig (float level) {
    initPwmControl();
    power_level_pwm = level;
    HAL_setVehicleKeyPowerCtl (TRUE);
}
