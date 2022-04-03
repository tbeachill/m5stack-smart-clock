#include <WiFi.h>
#include <Config.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFiClientSecure.h>
#include <Weather.h>

WeatherStruct currentWeather;

// update the currently held information
void WeatherUpdate()
{
    currentWeather = GetWeather();
}

// print the information to the screen
void WeatherPrintInfo()
{
    M5.Lcd.setTextSize(2);
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.printf("%f\n", currentWeather.MinTemp);
    M5.Lcd.printf("%f\n", currentWeather.MaxTemp);

}

// get the current weather from the internet
WeatherStruct GetWeather()
{
    WeatherStruct weather;

    // check that wifi is connected
    if (WiFi.status() != WL_CONNECTED)
    {
        return weather;
    }

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

        return weather;
    }
    else
    {
        http.end();
        return weather;
    }
}
