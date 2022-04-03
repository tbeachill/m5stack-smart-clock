#pragma once

enum Place {Obby, Club};

struct RblxGameInfo 
{
    int Playing;
    int Visits;
    int Favourites;
};

void RblxUpdate();
void RblxPrintInfo();
RblxGameInfo RblxGetInfo(Place place);