#include <WiFi.h>
#include <Config.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <Weather.h>
#include <M5Core2.h>

WeatherStruct CurrentWeather;
RTC_TimeTypeDef WeatherUpdateTime;

// update the currently held information
void WeatherUpdate(RTC_TimeTypeDef *time)
{
    if (WeatherUpdateTime.Minutes == time->Minutes)
        return;
    
    CurrentWeather = GetWeather();
    WeatherUpdateTime = *time;

    // cover up previous weather info
    M5.Lcd.fillRect(130, 150, 150, 70, TFT_BLACK);

    return;
}

// print the information to the screen
void WeatherPrintInfo()
{
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(150, 170);

    M5.Lcd.setTextColor(TFT_RED,TFT_BLACK);
    M5.Lcd.printf("%.1f", CurrentWeather.MaxTemp);

    M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);
    M5.Lcd.print(" / ");

    M5.Lcd.setTextColor(TFT_BLUE,TFT_BLACK);
    M5.Lcd.printf("%.1f\n", CurrentWeather.MinTemp);


    M5.Lcd.setCursor(150, 190);

    M5.Lcd.setTextColor(TFT_DARKCYAN,TFT_BLACK);
    M5.Lcd.printf("%.2f", CurrentWeather.PrecipAmount);

    M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);
    M5.Lcd.print("\" ");

    M5.Lcd.setTextColor(TFT_DARKCYAN,TFT_BLACK);
    M5.Lcd.printf("%i", CurrentWeather.PrecipProb);

    M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);
    M5.Lcd.print("%");

    return;
}

// get the current weather from the internet
WeatherStruct GetWeather()
{
    WeatherStruct weather;

    // check that wifi is connected
    if (WiFi.status() != WL_CONNECTED)
        return weather;

    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    // send the GET request
    http.begin(client, WEATHER_API);
    int httpResponse = http.GET();

    // parse json data
    if (httpResponse == 200)
    {
        DynamicJsonDocument doc(2048);
        String jsonreq = http.getString();

        deserializeJson(doc, jsonreq);
        http.end();

        JsonObject days_0 = doc["days"][0];
        weather.MaxTemp = days_0["tempmax"];
        weather.MinTemp = days_0["tempmin"];
        weather.PrecipAmount = days_0["precip"];
        weather.PrecipProb = days_0["precipprob"];
    }
    else
        http.end();

    return weather;
}
