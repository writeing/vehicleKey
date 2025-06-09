#include "CONFIG.h"
#include "HAL.h"
#include "hidconsumer.h"

typedef enum {
    BLE_DISTANCE_MODE_0 = 0,
    BLE_DISTANCE_MODE_1,
    BLE_DISTANCE_MODE_2,
    BLE_DISTANCE_MODE_3,
} enum_ble_distance_mode;

#define RTC_SLEEP_SEC(n) (32000 * n)

#define KEEP_TIMEOUT (3600 * 2)      // 2h
#define IDLE_TIMEOUT_SLEEP (50 * 10)  // 10min
static int keep_lock_Timeout = KEEP_TIMEOUT;
static int bleDistanceRssi[3] = {1, 1, 1};
// read flash end write flash
static int bleDistanceMode = BLE_DISTANCE_MODE_0;
static int keep_lock_sw = FALSE;
static int8_t NowRSSI;
static uint16_t nowConnHandle;
static BOOL vehicle_key_power_flag = FALSE;

void bleDistanceModeControl() {
    bleDistanceMode++;
    bleDistanceMode %= BLE_DISTANCE_MODE_3;
    PRINT ("\ncurrent ble distance mode:%d\n", bleDistanceMode);
    setThreeLed (bleDistanceMode);
    saveModeFlash(bleDistanceMode);
}

static int bleConnectStatus = 0xff;

// 0:adv  1:connected  2:disconnect  3:pairing 0xff:unknown
void setBleConenctStatus (int status) { bleConnectStatus = status; }

void hidRssiCB (uint16_t connHandle, int8_t newRSSI) {
    PRINT ("RSSI - %d dB Conn  %x \n", -newRSSI, connHandle);
    nowConnHandle = connHandle;
    NowRSSI = newRSSI;
}

void setBleKeyStatus (int status, BOOL sw) {
    PRINT ("status:%d,sw:%d\n", status, sw);
    switch (status) {
    case KEEP_UNLOCK:
        keep_lock_sw = sw;
        if (keep_lock_sw == TRUE && vehicle_key_power_flag == FALSE) {
            setVehicleLedStatusWork (STATUS_USER_KEEP);
            keep_lock_Timeout = KEEP_TIMEOUT - 1;
        } else {
            keep_lock_sw = FALSE;
        }
        break;
    case VEHICLE_KEY_POWER: {
        HAL_setVehicleKeyPowerCtl (sw);
        HAL_setVehicleKeyLock (sw);
        vehicle_key_power_flag = sw;
        if (sw == TRUE) {
            setVehicleLedStatusWork (STATUS_USER_OPEN);
        } else {
            setVehicleLedStatusWork (STATUS_USER_CLOSE);
        }
    } break;
    case UNLOCK:
        HAL_setVehicleKeyLock (TRUE);
        break;
    }
}

void loopVehicleControl()  // 100ms
{
    // 3200 = 100ms
    uint32_t cur_time;
    static int idle_time = 0;
    static int proWorkStatus = 0xff;
    // user control vehicle key power and lock status
    if (vehicle_key_power_flag == TRUE) {
        PRINT ("vehicle_key_power_flag:%d\n", vehicle_key_power_flag);
        keep_lock_Timeout = KEEP_TIMEOUT;
        return;
    }
    // keep lock timeout
    if (keep_lock_Timeout <= 10) {
        keep_lock_sw = FALSE;
    }
    if (keep_lock_Timeout != KEEP_TIMEOUT) {
        keep_lock_Timeout--;
        if (keep_lock_sw == FALSE) {
            keep_lock_Timeout = KEEP_TIMEOUT;
            proWorkStatus = 0xff;  // init unknown status
        }
        return;
    }
    if (bleConnectStatus != proWorkStatus) {
        PRINT ("bleConnectStatus:%d\n", bleConnectStatus);
        if (bleConnectStatus == 0) {
            // adv
            setVehicleLedStatusWork (STATUS_DISCONNECT);
            HAL_setVehicleKeyPowerCtl (FALSE);
            HAL_setVehicleKeyLock (FALSE);
        }
        if (bleConnectStatus == 1) {
            // connected
            if (bleDistanceRssi[bleDistanceMode] < NowRSSI) {
                setVehicleLedStatusWork (STATUS_CONNECTED);
                HAL_setVehicleKeyPowerCtl (TRUE);
                HAL_setVehicleKeyLock (TRUE);
            }
        }
        if (bleConnectStatus == 2) {
            // disconnect
            //   setVehicleLedStatusWork(STATUS_DISCONNECT);
            HAL_setVehicleKeyPowerCtl (FALSE);
            HAL_setVehicleKeyLock (FALSE);
        }

        if (bleConnectStatus == 3) {
            setVehicleLedStatusWork (STATUS_PAIRING);
        }
        if (bleConnectStatus == 4) {
            setVehicleLedStatusWork (STATUS_NO_PAIR);
        }
        proWorkStatus = bleConnectStatus;
        // bleDistanceModeControl();
    }
    switch (bleConnectStatus) {
    // adv
    case 0:
        if (idle_time++ == IDLE_TIMEOUT_SLEEP) {
            setVehicleLedStatusWork (STATUS_SLEEP);
            // pm sleep mod
            cur_time = RTC_GetCycle32k();
            // sleepCkey();
            CH57X_LowPower (RTC_SLEEP_SEC (15) + cur_time);
            SetSysClock (CLK_SOURCE_PLL_60MHz);
            setVehicleLedStatusWork (STATUS_DISCONNECT);
            PWR_DCDCCfg (ENABLE);

            idle_time = 0;
        }
        break;
    // connected
    case 1:
        idle_time = 0;
        break;
    // disconnect
    case 2:
        idle_time = 0;
        break;
    }
    return;
}

void initVehicleControl() {
    bleDistanceMode = getDistacnceMode();
    PRINT("DistanceMode:%d\n",bleDistanceMode);
    setVehicleLedStatusWork (STATUS_DISCONNECT);
}
