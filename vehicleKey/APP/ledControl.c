#include "CONFIG.h"
#include "HAL.h"
#include "hidconsumer.h"

// 0:r 1:g: 3:y
void setThreeLed(int color) {
  HalLedSet(HAL_LED_4, HAL_LED_MODE_OFF);
  HalLedSet(HAL_LED_3, HAL_LED_MODE_OFF);
  if (color == 0) HalLedSet(HAL_LED_4, HAL_LED_MODE_ON);
  if (color == 1) HalLedSet(HAL_LED_3, HAL_LED_MODE_ON);
  if (color == 2) {
    HalLedSet(HAL_LED_4, HAL_LED_MODE_ON);
    HalLedSet(HAL_LED_3, HAL_LED_MODE_ON);
  }
}

void status_connected() { HalLedBlink(HAL_LED_1, 0xFF, 50, 2000); }
void status_disconnct()  // disconnect
{
  HalLedBlink(HAL_LED_1, 0xFF, 50, 500);
}
void status_unlock()  // unlock
{
  HalLedSet(HAL_LED_1, HAL_LED_MODE_ON);
}
void status_user_keep()  // status_user_keep
{
  HalLedBlink(HAL_LED_1, 0xFF, 50, 1000);
}
void status_user_open()  // status_user_open
{
  HalLedBlink(HAL_LED_1, 0xFF, 50, 10000);
}

void status_pair() { HalLedBlink(HAL_LED_2, 0xFF, 50, 500); }
void status_no_pair() { HalLedBlink(HAL_LED_2, 0xFF, 50, 2000); }
void status_user_close() { HalLedBlink(HAL_LED_2, 0xFF, 50, 10000); }
void status_error() { HalLedSet(HAL_LED_2, HAL_LED_MODE_ON); }
void status_sleep() { HalLedSet(HAL_LED_ALL, HAL_LED_MODE_OFF); }
void setVehicleLedStatusWork(enum_led_status status) {
  switch (status & 0x0F) {
    case STATUS_CONNECTED:
      PRINT("STATUS_CONNECTED");
      status_connected();
      break;
    case STATUS_DISCONNECT:
      PRINT("STATUS_DISCONNECT");
      status_disconnct();
      break;
    case STATUS_UNLOCK:
      PRINT("STATUS_UNLOCK");
      status_unlock();
      break;
    case STATUS_USER_OPEN:
      PRINT("STATUS_USER_OPEN");
      status_user_open();
      break;
    case STATUS_USER_KEEP:
      PRINT("STATUS_USER_KEEP");
      status_user_keep();
      break;
  }
  // 红灯
  switch (status & 0xF0) {
    case STATUS_PAIRING:
      status_pair();
      break;
    case STATUS_NO_PAIR:
      status_no_pair();
      break;
    case STATUS_USER_CLOSE:
      status_user_close();
      break;
    case STATUS_ERROR:
      status_error();
      break;
  }
  if (status == STATUS_SLEEP) {
    status_sleep();
  }
}
