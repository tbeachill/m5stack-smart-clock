#include <M5Core2.h>

// auto dim between 10pm and 8am
void AutoBrightness(RTC_TimeTypeDef *time)
{
    if (time->Hours > 21 || time->Hours < 8)
        M5.Axp.SetLcdVoltage(2500);
    else
        M5.Axp.SetLcdVoltage(2750);
    
    return;
}

// clear screen and set cursor and font to defaults
void ClearScreen()
{
    M5.Lcd.clearDisplay();
    M5.Lcd.setCursor(0, 20);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setTextColor(TFT_WHITE);
    M5.Lcd.setTextFont(GLCD);

    return;
}
