#pragma once

// button colours
ButtonColors col1 = {TFT_DARKGREY, TFT_WHITE, TFT_WHITE};
ButtonColors col2 = {TFT_ORANGE, TFT_WHITE, TFT_WHITE};

struct HourMin
{
    int Hour;
    int Minute;
};

void AlarmControl(HourMin *alarm, bool *set);

void AlarmListener(RTC_TimeTypeDef *time, HourMin *alarm, bool *set);
