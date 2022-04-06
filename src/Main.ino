#include <M5Core2.h>
#include <Clock.h>
#include <Kasa.h>
#include <Roblox.h>
#include <Weather.h>
#include <Alarm.h>

RTC_TimeTypeDef TimeStruct;
RTC_DateTypeDef DateStruct;
int LastPressed = 0;
bool AlarmSet = false;
HourMin AlarmTime = {0, 0};

/* After M5Core2 is started or reset, the program in the setup() function will be executed, and this part will only be executed once. */
void setup(){
  M5.begin();
  M5.Rtc.begin();

  // attempt to connect to Wifi network:
  M5.Lcd.print("WIFI ");
  WifiConnect();
  M5.Lcd.setTextColor(TFT_GREEN);
  M5.Lcd.println("SUCCESS");
  M5.Lcd.setTextColor(TFT_WHITE);

  // Set the current time and date
  M5.Lcd.print("SETTING TIME: ");
  std::pair<RTC_DateTypeDef, RTC_TimeTypeDef> packed = InitTime();
  DateStruct = packed.first;
  TimeStruct = packed.second;
  M5.Rtc.SetTime(&TimeStruct);
  M5.Rtc.SetDate(&DateStruct);
  M5.Lcd.setTextColor(TFT_GREEN);
  M5.Lcd.println("SUCCESS");
  M5.Lcd.setTextColor(TFT_WHITE);

  ClearScreen();

  // turn off led
  M5.Axp.SetLed(0);
  // set vibration intensity
  M5.Axp.SetLDOVoltage(3, 3);
}

/* After the program in the setup() function is executed, the program in the loop() function will be executed
The loop() function is an endless loop, in which the program will continue to run repeatedly */
void loop() {
  M5.update();    
  AutoBrightness(&TimeStruct);

  // listener for button presses
  if (M5.BtnA.isPressed())
    LastPressed = 0;
  else if (M5.BtnB.isPressed())
    LastPressed = 1;
  else if (M5.BtnC.isPressed())
    LastPressed = 2;

  // display one of the screens depending on which button was last pressed
  if (LastPressed == 0)
  {
    WeatherUpdate(&TimeStruct);
    WeatherPrintInfo();

    while (!M5.BtnB.isPressed() && !M5.BtnC.isPressed())
    {
      // update every 2 hours
      if (TimeStruct.Hours % 2 == 0 && TimeStruct.Minutes == 0)
      {
        WeatherUpdate(&TimeStruct);
        WeatherPrintInfo();
      }

      // if the screen is touched, open the alarm set screen
      if (M5.Touch.ispressed())
      {
        ClearScreen();
        AlarmControl(&AlarmTime, &AlarmSet);
      }
      
      DisplayTime(&DateStruct, &TimeStruct, &AlarmSet);
      //WeatherPrintInfo();
      AutoBrightness(&TimeStruct);
      AlarmListener(&TimeStruct, &AlarmTime, &AlarmSet);

      delay(500);
      M5.update();
    }

    ClearScreen();
  }
  else if (LastPressed == 1)
  {
    RblxUpdate(&TimeStruct);
    RblxPrintInfo();

    // don't do anything unless a button is pressed
    while (!M5.BtnA.isPressed() && !M5.BtnC.isPressed())
    {
      // update every 5 minutes
      if (TimeStruct.Minutes % 5 == 0)
        RblxUpdate(&TimeStruct);
      
      RblxPrintInfo();
      AutoBrightness(&TimeStruct);
      AlarmListener(&TimeStruct, &AlarmTime, &AlarmSet);

      delay(500);
      M5.update();
    }

    // clear the screen when a button has been pressed
    ClearScreen();
  }
  else if (LastPressed == 2)
  {
    DrawLightControls();

    while (!M5.BtnA.isPressed() && !M5.BtnB.isPressed())
    {
      AutoBrightness(&TimeStruct);
      AlarmListener(&TimeStruct, &AlarmTime, &AlarmSet);

      delay(500);
      M5.update();
    }

    ClearScreen();
  }
}
