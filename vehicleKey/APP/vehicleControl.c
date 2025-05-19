#include "CONFIG.h"
#include "HAL.h"
#include "hidconsumer.h"

typedef enum
{
    BLE_DISTANCE_MODE_0= 0,
    BLE_DISTANCE_MODE_1,
    BLE_DISTANCE_MODE_2,
    BLE_DISTANCE_MODE_3,
}enum_ble_distance_mode;

//read flash end write flash
static int bleDistanceMode = BLE_DISTANCE_MODE_0;

void bleDistanceModeControl()
{
    bleDistanceMode ++;
    bleDistanceMode %= BLE_DISTANCE_MODE_3;
    PRINT("current ble distance mode:%d\n",bleDistanceMode);
    setThreeLed(bleDistanceMode);
}
static int bleConnectStatus = 0;
//0:adv  1:connected  2:disconnect
void setBleConenctStatus(int status)
{
    bleConnectStatus = status;
}
void loopVehicleControl()
{
    static int proWorkStatus = 0;
    static int delayTime = 100;
    if(bleConnectStatus != proWorkStatus || delayTime-- <= 0)
    {
        PRINT("bleConnectStatus:%d\n",bleConnectStatus);
        if(bleConnectStatus == 1)
            setVehicleLedStatusWork(STATUS_CONNECTED);
        if(bleConnectStatus == 2)
            setVehicleLedStatusWork(STATUS_IDLE);
        if(bleConnectStatus == 0)
            setVehicleLedStatusWork(STATUS_IDLE);
        proWorkStatus = bleConnectStatus;
        delayTime = 100;
        bleDistanceModeControl();
    }    
    return;
}
void initVehicleControl()
{
    setVehicleLedStatusWork(STATUS_IDLE);
    
}




