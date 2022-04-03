#include <M5Core2.h>

// auto dim between 10pm and 8am
void AutoBrightness(RTC_TimeTypeDef timeStruct)
{
    if (timeStruct.Hours > 21 || timeStruct.Hours < 8)
    {
        M5.Axp.SetLcdVoltage(2500);
    }
    else
    {
        M5.Axp.SetLcdVoltage(2750);
    }
    
    return;
}