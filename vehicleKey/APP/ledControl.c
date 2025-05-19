#include "CONFIG.h"
#include "HAL.h"
#include "hidconsumer.h"

// 0:r 1:g: 3:y
void setThreeLed (int color) {
    HalLedSet (HAL_LED_4, HAL_LED_MODE_OFF);
    HalLedSet (HAL_LED_3, HAL_LED_MODE_OFF);
    if (color == 0)
        HalLedSet (HAL_LED_4, HAL_LED_MODE_ON);
    if (color == 1)
        HalLedSet (HAL_LED_3, HAL_LED_MODE_ON);
    if (color == 2) {
        HalLedSet (HAL_LED_4, HAL_LED_MODE_ON);
        HalLedSet (HAL_LED_3, HAL_LED_MODE_ON);
    }
}


void status_connected()
{
    HalLedBlink(HAL_LED_1,100,50,2000);
}
void status_idle() //disconnect
{
    HalLedBlink(HAL_LED_1,100,50,500);
}
void status_unlock() //disconnect
{
    HalLedSet(HAL_LED_1,HAL_LED_MODE_ON);
}

void status_pair()
{
    HalLedBlink(HAL_LED_2,0,50,2000);
}
void low_power()
{
    HalLedBlink(HAL_LED_2,0,50,300);
}
void status_error()
{
    HalLedSet(HAL_LED_2,HAL_LED_MODE_ON);
}
void setVehicleLedStatusWork(int status)
{
    switch (status & 0x0F) {
        case STATUS_CONNECTED:
            PRINT("STATUS_CONNECTED");
            status_connected();
        break;
        case STATUS_IDLE:
            PRINT("STATUS_IDLE");
            status_idle();
        break;
        case STATUS_UNLOCK:
            PRINT("STATUS_UNLOCK");
            status_unlock();
        break;
    }
    switch (status& 0xF0) {
        case STATUS_PAIR:
            status_pair();
        break;
        case STATUS_LOW_POWER:
            low_power();
        break;
        case STATUS_ERROR:
            status_error();
        break;
    }    
}

