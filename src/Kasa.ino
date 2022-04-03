#include <WiFi.h>
#include <Config.h>
#include <HTTPClient.h>
#include <Kasa.h>

// send a webhook request to IFTTT for a Kasa smart bulb
void KasaEvent(Action action)
{
    // check that wifi is connected
    if (WiFi.status() != WL_CONNECTED)
    {
        return;
    }

    // select the correct webhook url
    String actionURL;
    switch (action) 
    {
        case Toggle:
            actionURL = KASA_TOGGLE;
            break;
        case Dim10:
            actionURL = KASA_BRIGHTNESS_10;
            break;
        case Dim100:
            actionURL = KASA_BRIGHTNESS_100;
            break;
    }

    WiFiClient client;
    HTTPClient http;

    // send the GET request
    http.begin(client, actionURL);
    int httpResponse = http.GET();

    http.end();

    return;
}

