/* 头文件包含 */
#include "CONFIG.h"
#include "HAL.h"
#include "hidconsumer.h"

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
