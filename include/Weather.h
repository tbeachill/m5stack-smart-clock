#pragma once

struct WeatherStruct
{
    float MinTemp;
    float MaxTemp;
    float PrecipAmount;
    int PrecipProb;
};

WeatherStruct GetWeather();
void WeatherPrintInfo();
void WeatherUpdate();