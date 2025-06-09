/* ͷ�ļ����� */
#include "CONFIG.h"
#include "HAL.h"
#include "flexible_button.h"
#include "hidconsumer.h"
#define ENUM_TO_STR(e) (#e)

typedef enum {
  USER_BUTTON_1 = 1,
  USER_BUTTON_2,
  USER_BUTTON_3,
  USER_BUTTON_4,
  USER_BUTTON_MAX,
} user_button_t;

static char *enum_event_string[] = {
    ENUM_TO_STR(FLEX_BTN_PRESS_DOWN),
    ENUM_TO_STR(FLEX_BTN_PRESS_CLICK),
    ENUM_TO_STR(FLEX_BTN_PRESS_DOUBLE_CLICK),
    ENUM_TO_STR(FLEX_BTN_PRESS_REPEAT_CLICK),
    ENUM_TO_STR(FLEX_BTN_PRESS_SHORT_START),
    ENUM_TO_STR(FLEX_BTN_PRESS_SHORT_UP),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_START),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_UP),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_HOLD),
    ENUM_TO_STR(FLEX_BTN_PRESS_LONG_HOLD_UP),
    ENUM_TO_STR(FLEX_BTN_PRESS_MAX),
    ENUM_TO_STR(FLEX_BTN_PRESS_NONE),
};

static flex_button_t user_button[USER_BUTTON_MAX];

static uint8_t common_btn_read(void *arg) {
  uint8_t value = 1;
  flex_button_t *btn = (flex_button_t *)arg;
  switch (btn->id) {
    case USER_BUTTON_1:
      // value = HAL_PUSH_BUTTON1();
      break;
    case USER_BUTTON_2:
      // value = HAL_PUSH_BUTTON2();
      break;
    case USER_BUTTON_3:
      value = HAL_PUSH_BUTTON3();
      break;
    case USER_BUTTON_4:
      value = HAL_PUSH_BUTTON4();
      break;
    default:
      PRINT("id:%d, not int key press\n", btn->id);
  }
  return value;
}
static void vehicleKeyCmd(int keyId, flex_button_event_t keyEvent) {
  switch (keyId) {
    case USER_BUTTON_1: {
      if (keyEvent == FLEX_BTN_PRESS_LONG_UP) {
        // long press
        PRINT("long press  开始配对\n");
        flashResetMasterMac();  // clean flash info
        SYS_ResetExecute();     // reset system
      }
      if (keyEvent == FLEX_BTN_PRESS_CLICK) {
        // ble info distance mode
        PRINT("ble info distance mode\n");
        bleDistanceModeControl();
      }
    } break;
    case USER_BUTTON_2: {
      if (keyEvent == FLEX_BTN_PRESS_LONG_UP) {
        // open vehicle power and unlock vehicle
        PRINT("open keep unlock vehicle\n");
        setBleKeyStatus(KEEP_UNLOCK, TRUE);
      }
      if (keyEvent == FLEX_BTN_PRESS_CLICK) {
        // lock vehicle and close vehicle key power
        PRINT("close keep unlock vehicle\n");
        setBleKeyStatus(KEEP_UNLOCK, FALSE);
      }
    } break;
    case USER_BUTTON_3: {
      if (keyEvent == FLEX_BTN_PRESS_LONG_UP) {
        // lock vehicle and close vehicle key power
        PRINT("lock vehicle and close vehicle key power\n");
        setBleKeyStatus(VEHICLE_KEY_POWER, FALSE);
      }
      if (keyEvent == FLEX_BTN_PRESS_SHORT_UP) {
        // open vehicle power and unlock vehicle
        PRINT("open vehicle power and unlock vehicle\n");
        setBleKeyStatus(VEHICLE_KEY_POWER, TRUE);
      }
      if (keyEvent == FLEX_BTN_PRESS_DOUBLE_CLICK) {
        // unlock vehicle
        PRINT("unlock vehicle\n");
        setBleKeyStatus(UNLOCK, TRUE);
      }
    } break;
    case USER_BUTTON_4:
      break;
  }
}

static void common_btn_evt_cb(void *arg) {
  flex_button_t *btn = (flex_button_t *)arg;
  PRINT("id: [%d]  event: [%d - %30s]  repeat: %d\n", btn->id, btn->event,
        enum_event_string[btn->event], btn->click_cnt);
  // if (btn->event == FLEX_BTN_PRESS_DOWN) {
  //     // can_send_voice_data((enumVoiceCMD)btn->id);
  // }
  // if (btn->event == FLEX_BTN_PRESS_REPEAT_CLICK) {
  //     // can_send_voice_data((enumVoiceCMD)btn->id);
  // }
  vehicleKeyCmd(btn->id, btn->event);
}

static void user_button_init(void) {
  tmos_memset(&user_button[0], 0x0, sizeof(user_button));

  int i = USER_BUTTON_1;
  user_button[i].id = i;
  user_button[i].usr_button_read = common_btn_read;
  user_button[i].cb = common_btn_evt_cb;
  user_button[i].pressed_logic_level = 0;
  user_button[i].short_press_start_tick = FLEX_MS_TO_SCAN_CNT(1000);
  user_button[i].long_press_start_tick = FLEX_MS_TO_SCAN_CNT(5000);
  user_button[i].long_hold_start_tick = FLEX_MS_TO_SCAN_CNT(50000);
  flex_button_register(&user_button[i]);
  i++;
  user_button[i].id = i;
  user_button[i].usr_button_read = common_btn_read;
  user_button[i].cb = common_btn_evt_cb;
  user_button[i].pressed_logic_level = 0;
  user_button[i].short_press_start_tick = FLEX_MS_TO_SCAN_CNT(1000);
  user_button[i].long_press_start_tick = FLEX_MS_TO_SCAN_CNT(3000);
  user_button[i].long_hold_start_tick = FLEX_MS_TO_SCAN_CNT(50000);
  flex_button_register(&user_button[i]);
  i++;
  user_button[i].id = i;
  user_button[i].usr_button_read = common_btn_read;
  user_button[i].cb = common_btn_evt_cb;
  user_button[i].pressed_logic_level = 0;
  user_button[i].short_press_start_tick = FLEX_MS_TO_SCAN_CNT(1000);
  user_button[i].long_press_start_tick = FLEX_MS_TO_SCAN_CNT(5000);
  user_button[i].long_hold_start_tick = FLEX_MS_TO_SCAN_CNT(50000);
  flex_button_register(&user_button[i]);
}

static void halKeyCBack(uint8_t keys) { flex_button_scan(); }

void initKeyUser() {
  user_button_init();
  HalKeyConfig(halKeyCBack);
}