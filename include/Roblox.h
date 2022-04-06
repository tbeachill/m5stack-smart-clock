#pragma once

enum Place {Obby, Club};

struct RblxGameInfo 
{
    int Playing;
    int Visits;
    int Favourites;
};

void RblxUpdate(RTC_TimeTypeDef *time);

void RblxPrintInfo();

RblxGameInfo RblxGetInfo(Place place);

void FormatNumber(int number, bool space);
