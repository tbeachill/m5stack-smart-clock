#include <NTPClient.h>
#include <WiFiUdp.h>
#include <RTC.h>
#include <M5Core2.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <Config.h>
#include <Alarm.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
String weekday[7] = {"SUN", "MON", "TUE", "WED", "THU", "FRI", "SAT"};

// populate date and time structs
std::pair<RTC_DateTypeDef, RTC_TimeTypeDef> InitTime()
{
    timeClient.begin();
    
    tm* gmtm = GetTime(0);

    // check if DST is in effect
    if(GetDST(gmtm) == 1)
        gmtm = GetTime(3600);

    // populate a timestruct
    RTC_TimeTypeDef TimeStruct;
    TimeStruct.Hours = gmtm->tm_hour;
    TimeStruct.Minutes = gmtm->tm_min;
    TimeStruct.Seconds = gmtm->tm_sec;

    // populate a datestruct
    RTC_DateTypeDef DateStruct;
    DateStruct.Date = gmtm->tm_mday;
    DateStruct.Month = (gmtm->tm_mon) + 1;
    DateStruct.Year = (gmtm->tm_year) + 1900;
    DateStruct.WeekDay = (gmtm->tm_wday); // 0 = Sunday

    // package up the date and time
    std::pair<RTC_DateTypeDef, RTC_TimeTypeDef> packed = std::make_pair(DateStruct, TimeStruct);
    
    return packed;
}

// get the current time from the internet
tm* GetTime(int offset)
{
    timeClient.setTimeOffset(offset);

    while(!timeClient.update())
    {
        timeClient.forceUpdate();
    }

    // get the current time
    time_t t = timeClient.getEpochTime();
    delay(5000);
    tm *gmtm = gmtime(&t);

    return gmtm;
}

// print the current time and date to the screen
void DisplayTime(RTC_DateTypeDef *date, RTC_TimeTypeDef *time, bool *alarmSet)
{
    // update screen
    M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);

    // write time
    M5.Lcd.setTextSize(5);
    M5.Rtc.GetTime(time);
    M5.Rtc.GetDate(date);
    M5.Lcd.setCursor(30, 40);
    M5.Lcd.printf("%02d:%02d:%02d", time->Hours, time->Minutes, time->Seconds);

    // display if alarm is set
    if (*alarmSet)
    {
        M5.Lcd.setTextSize(2);
        M5.Lcd.setCursor(280, 40);
        M5.Lcd.setTextColor(YELLOW);
        M5.Lcd.print("AL");
        M5.Lcd.setTextColor(WHITE); 
    }
    else
    {
        // fill rectangle to remove alarm status without doing a clear
        M5.Lcd.fillRect(265, 20, 40, 40, TFT_BLACK);
    }

    // write date
    M5.Lcd.setCursor(30, 120);
    M5.Lcd.setTextSize(4);
    M5.Lcd.printf("%02d %02d %04d", date->Date, date->Month, date->Year);
    
    // write weekday
    M5.Lcd.setCursor(30, 170);
    M5.Lcd.printf("%s", weekday[date->WeekDay]);
}

// get whether or not daylight savings is being observed
int GetDST(tm* gmtm)
{
    int dst = 0;

    // set rough dst in case API cant be reached
    if(gmtm->tm_mon > 2 && gmtm->tm_mon < 10)
        dst = 1;

    if (WiFi.status() != WL_CONNECTED)
    {
        return dst;
    }

    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    // get the current timezone offset
    http.begin(client, WEATHER_API);
    int httpResponse = http.GET();

    // parse json data
    if (httpResponse == 200)
    {
        DynamicJsonDocument doc(2048);
        String jsonreq = http.getString();

        deserializeJson(doc, jsonreq);

        // extract timezone offset to int
        dst = doc["tzoffset"];

        http.end();
    }

    return dst;
}
