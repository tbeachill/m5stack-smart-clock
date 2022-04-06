#include <WiFi.h>
#include <Config.h>
#include <M5Core2.h>

int Status = WL_IDLE_STATUS;     // the Wifi radio's status

// connect to the wifi network
void WifiConnect()
{
  M5.Lcd.printf("%s: ", WIFI_SSID);

  while (Status != WL_CONNECTED) 
  {
    Status = WiFi.begin(WIFI_SSID, WIFI_PW);
    // wait 5 seconds for connection:
    delay(5000);
  }

  return;
}  
