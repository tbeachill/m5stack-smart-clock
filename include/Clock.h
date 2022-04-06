#pragma once

std::pair<RTC_DateTypeDef, RTC_TimeTypeDef> InitTime();

tm* GetTime(int offset);

void DisplayTime(RTC_DateTypeDef *date, RTC_TimeTypeDef *time, bool *alarmSet);

int GetDST(tm* gmtm);
