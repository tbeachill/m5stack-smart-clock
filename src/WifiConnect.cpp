#include <WiFi.h>
#include <Config.h>
#include <M5Core2.h>

int status = WL_IDLE_STATUS;     // the Wifi radio's status

void WifiConnect()
{

  // connect to the wifi network in Config.h

  M5.Lcd.printf("%s: ", WIFI_SSID);

  while (status != WL_CONNECTED) {
    status = WiFi.begin(WIFI_SSID, WIFI_PW);
    // wait 10 seconds for connection:
    delay(10000);
  }
}  
