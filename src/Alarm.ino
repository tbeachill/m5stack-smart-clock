#include <M5Core2.h>
#include <Alarm.h>

// button colours
ButtonColors col1 = {DARKGREY, WHITE, WHITE};
ButtonColors col2 = {ORANGE, WHITE, WHITE};

HourMin setTime = {0,0};
bool isSet = false;

HourMin DrawAlarmControls()
{
    Button hourUpButton    (60, 20, 75, 50, false, "+", col1, col2);
    Button hourDownButton  (60, 155, 75, 50, false, "-", col1, col2);
    Button minuteUpButton  (185, 20, 75, 50, false, "+", col1, col2);
    Button minuteDownButton(185, 155, 75, 50, false, "-", col1, col2);

    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(30, 230);
    M5.Lcd.print("Back");

    while (true)
    {
        if (M5.BtnA.isPressed())
        {
            break;
        }
        else if (M5.BtnC.isPressed())
        {
            isSet = isSet ? false : true;
            M5.Lcd.fillRect(250, 210, 50, 25, TFT_BLACK);
        }
        else if (hourUpButton.isPressed())
        {
            setTime.Hour == 23 ? setTime.Hour = 0 : setTime.Hour += 1;
            M5.Lcd.fillRect(50, 70, 250, 80, TFT_BLACK);
        }
        else if (hourDownButton.isPressed())
        {
            setTime.Hour == 0 ? setTime.Hour = 23 : setTime.Hour -= 1;
            M5.Lcd.fillRect(50, 70, 250, 80, TFT_BLACK);
        }
        else if (minuteUpButton.isPressed())
        {
            setTime.Minute == 59 ? setTime.Minute = 0 : setTime.Minute += 1;
            M5.Lcd.fillRect(60, 70, 250, 80, TFT_BLACK);
        }
        else if (minuteDownButton.isPressed())
        {
            setTime.Minute == 0 ? setTime.Minute = 59 : setTime.Minute -= 1;
            M5.Lcd.fillRect(60, 70, 250, 80, TFT_BLACK);
        }

        
        M5.Lcd.setTextSize(1);
        M5.Lcd.setCursor(250, 230);
        M5.Lcd.printf("%s", isSet ? "Unset" : "Set");
        
        // write out time
        M5.Lcd.setTextSize(5);
        M5.Lcd.setCursor(45, 140);
        M5.Lcd.printf("%02d:%02d", setTime.Hour, setTime.Minute);

        M5.update();
        delay(100);
    }

    ClearScreen();

    return setTime;
}
