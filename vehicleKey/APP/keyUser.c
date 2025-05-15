/* 头文件包含 */
#include "CONFIG.h"
#include "HAL.h"
#include "hidconsumer.h"

// #define HAL_KEY_SW_1             0x01  // key1
// #define HAL_KEY_SW_2             0x02  // key2
// #define HAL_KEY_SW_3             0x04  // key3
// #define HAL_KEY_SW_4             0x08  // key4

static void halKeyCBack(uint8_t keys)
{
    PRINT("keys:%x\n",keys);
    if((keys & 0x04))
    {
        flashResetMasterMac();
    }
}


void initKeyUser()
{
    HalKeyConfig(halKeyCBack);
}
