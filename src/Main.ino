#include <M5Core2.h>
#include <Clock.h>
#include <Kasa.h>
#include <Roblox.h>
#include<Weather.h>

RTC_TimeTypeDef TimeStruct;
RTC_DateTypeDef DateStruct;
int lastPressed = 2;
bool set = false;

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

  // turn off LED
  M5.Axp.SetLed(0);

}

/* After the program in the setup() function is executed, the program in the loop() function will be executed
The loop() function is an endless loop, in which the program will continue to run repeatedly */
void loop() {
  M5.update();    
  AutoBrightness(TimeStruct);
  
  // listener for button presses
  if (M5.BtnA.isPressed())
  {
    lastPressed = 0;
  }
  else if (M5.BtnB.isPressed())
  {
    lastPressed = 1;
  }
  else if (M5.BtnC.isPressed())
  {
    lastPressed = 2;
  }

  // display one of the screens depending on which button was last pressed
  if (lastPressed == 0)
  {
    WeatherUpdate();

    while (!M5.BtnA.isPressed() && !M5.BtnB.isPressed() && !M5.BtnC.isPressed())
    {
      // update every 2 hours
      if (TimeStruct.Hours % 2 == 0 && TimeStruct.Minutes == 0 && TimeStruct.Seconds == 0)
      {
        WeatherUpdate();
        WeatherPrintInfo();
      }
      
      DisplayTime(DateStruct, TimeStruct);
      WeatherPrintInfo();
      delay(500);
      M5.update();
    }

  }
  else if (lastPressed == 1)
  {
    RblxUpdate();
    delay(1000);
    RblxPrintInfo();

    // don't do anything unless a button is pressed
    while (!M5.BtnA.isPressed() && !M5.BtnB.isPressed() && !M5.BtnC.isPressed())
    {
      // update every 15 minutes
      if (TimeStruct.Minutes % 15 == 0 && TimeStruct.Seconds == 0)
      {
        RblxUpdate();
        RblxPrintInfo();
      }
      
      delay(500);
      M5.update();
    }

    // clear the screen when a button has been pressed
    M5.Lcd.clear();
  }
  else if (lastPressed == 2)
  {
    M5.Lcd.clear();
    DrawControls();

    while (!M5.BtnA.isPressed() && !M5.BtnB.isPressed() && !M5.BtnC.isPressed())
    {     
      
      delay(500);
      M5.update();
    }
  }

}
