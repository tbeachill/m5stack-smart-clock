#include <WiFi.h>
#include <Config.h>
#include <HTTPClient.h>
#include <Roblox.h>
#include <ArduinoJson.h>
#include <ssl_client.h>
#include <WiFiClientSecure.h>

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
    M5.Lcd.clear();
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("Obby visitors: %i\n", obbyInfo.Visits);
    M5.Lcd.printf("Club visitors: %i\n", clubInfo.Visits);

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

        return rb;
    }
    else
    {
        http.end();
        return rb;
    }
}
