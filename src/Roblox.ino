#include <WiFi.h>
#include <Config.h>
#include <HTTPClient.h>
#include <Roblox.h>
#include <ArduinoJson.h>
#include <ssl_client.h>
#include <WiFiClientSecure.h>
#include <M5Core2.h>
#include <Utilities.h>

RblxGameInfo ObbyInfo;
RblxGameInfo ClubInfo;
int PreviousHigh = 0;
RTC_TimeTypeDef RblxUpdateTime;

// update the currently held information
void RblxUpdate(RTC_TimeTypeDef *time)
{
    // return if the update has already been performed
    if (RblxUpdateTime.Minutes == time->Minutes)
        return;
    
    ObbyInfo = RblxGetInfo(Obby);
    ClubInfo = RblxGetInfo(Club);
    RblxUpdateTime = *time;

    // vibrate once if more people are playing now than the last update and it is daytime
    if (ObbyInfo.Playing + ClubInfo.Playing > PreviousHigh && (time->Hours > 8 || time->Hours < 21))
    {
        M5.Axp.SetLDOEnable(3, true);
        delay(100);
        M5.Axp.SetLDOEnable(3, false);

        PreviousHigh = ObbyInfo.Playing + ClubInfo.Playing;
    }

    ClearScreen();

    return;
}

// print the information to the screen
void RblxPrintInfo()
{
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("--------------------------");
    M5.Lcd.println("|        | obby  | club  |");
    M5.Lcd.println("|------------------------|");

    M5.Lcd.print("|playing | ");
    FormatNumber(ObbyInfo.Playing, true);
    FormatNumber(ClubInfo.Playing, false);
    M5.Lcd.println();


    M5.Lcd.print("|visits  | ");
    FormatNumber(ObbyInfo.Visits, true);
    FormatNumber(ClubInfo.Visits, false);
    M5.Lcd.println();

    M5.Lcd.print("|favs    | ");
    FormatNumber(ObbyInfo.Favourites, true);
    FormatNumber(ClubInfo.Favourites, false);
    M5.Lcd.println();

    M5.Lcd.println("--------------------------");
    M5.Lcd.printf("       last updated: %02d:%02d", RblxUpdateTime.Hours, RblxUpdateTime.Minutes);

    return;
}

// format a number to 0.0k if 1000 or over
void FormatNumber(int number, bool space)
{
    number > 999 ? M5.Lcd.printf("%4.1fk |", (float) number / 1000) : M5.Lcd.printf("%4d  |", number);

    if (space)
        M5.Lcd.print(" ");

    return;
}

// get current info on own roblox games
RblxGameInfo RblxGetInfo(Place place)
{
    RblxGameInfo rb;

    // check that wifi is connected
    if (WiFi.status() != WL_CONNECTED)
        return rb;

    // select the correct webhook url
    String placeURL;
    switch (place) 
    {
        case Obby:
            placeURL = ROBLOX_OBBY;
            break;
        case Club:
            placeURL = ROBLOX_CLUB;
            break;
    }

    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    // send the GET request
    http.begin(client, placeURL);
    int httpResponse = http.GET();

    // parse json data
    if (httpResponse == 200)
    {
        DynamicJsonDocument doc(2048);
        String jsonreq = http.getString();

        deserializeJson(doc, jsonreq);
        JsonObject data_0 = doc["data"][0];

        http.end();

        rb.Favourites = data_0["favoritedCount"];
        rb.Visits = data_0["visits"];
        rb.Playing = data_0["playing"];

        delay(500);
    }
    else
        http.end();

    return rb;
}
