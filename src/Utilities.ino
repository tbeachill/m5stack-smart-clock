//#include <M5Core2.h>

void AutoBrightness(RTC_TimeTypeDef timeStruct)
{
    // auto dim between 10pm and 8am

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