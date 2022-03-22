#include <M5Core2.h>
#include <WifiConnect.h>
#include <Clock.h>

RTC_TimeTypeDef TimeStruct;
RTC_DateTypeDef DateStruct;

/* After M5Core2 is started or reset, the program in the setup() function will be executed, and this part will only be executed once. */
void setup(){
  M5.begin();
  M5.Rtc.begin();

  // attempt to connect to Wifi network:
  M5.Lcd.print("WIFI ");
  WifiConnect();
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("SUCCESS");
  M5.Lcd.setTextColor(WHITE);

  // Set the current time and date
  M5.Lcd.print("SETTING TIME: ");
  std::pair<RTC_DateTypeDef, RTC_TimeTypeDef> packed = InitTime();
  DateStruct = packed.first;
  TimeStruct = packed.second;
  M5.Rtc.SetTime(&TimeStruct);
  M5.Rtc.SetDate(&DateStruct);
  M5.Lcd.setTextColor(GREEN);
  M5.Lcd.println("SUCCESS");
  M5.Lcd.setTextColor(WHITE);

  M5.Lcd.clear();
}

/* After the program in the setup() function is executed, the program in the loop() function will be executed
The loop() function is an endless loop, in which the program will continue to run repeatedly */
void loop() {
  DisplayTime(DateStruct, TimeStruct);
  delay(1000);
}
