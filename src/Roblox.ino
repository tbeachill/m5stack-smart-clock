#include <WiFi.h>
#include <Config.h>
#include <HTTPClient.h>
#include <Roblox.h>
#include <ArduinoJson.h>
#include <ssl_client.h>
#include <WiFiClientSecure.h>
#include <M5Core2.h>

RblxGameInfo obbyInfo;
RblxGameInfo clubInfo;

// update the currently held information
void RblxUpdate()
{
    obbyInfo = RblxGetInfo(Obby);
    clubInfo = RblxGetInfo(Club);
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
    FormatNumber(obbyInfo.Playing, true);
    FormatNumber(clubInfo.Playing, false);
    M5.Lcd.println();


    M5.Lcd.print("|visits  | ");
    FormatNumber(obbyInfo.Visits, true);
    FormatNumber(clubInfo.Visits, false);
    M5.Lcd.println();

    M5.Lcd.print("|favs    | ");
    FormatNumber(obbyInfo.Favourites, true);
    FormatNumber(clubInfo.Favourites, false);
    M5.Lcd.println();

    M5.Lcd.println("--------------------------");
}

// format a number to 0.0k if 1000 or over
void FormatNumber(int number, bool space)
{
    number > 999 ? M5.Lcd.printf("%4.1fk |", (float) number / 1000) : M5.Lcd.printf("%4d  |", number);
    if (space) M5.Lcd.print(" ");
}

// get current info on own roblox games
RblxGameInfo RblxGetInfo(Place place)
{
    RblxGameInfo rb;

    // check that wifi is connected
    if (WiFi.status() != WL_CONNECTED)
    {
        return rb;
    }

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

        delay(1000);

        return rb;
    }
    else
    {
        http.end();
        return rb;
    }
}
