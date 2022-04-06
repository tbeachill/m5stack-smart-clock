#include <M5Core2.h>
#include <Alarm.h>
#include <Utilities.h>

// choose a time and set/unset the alarm
void AlarmControl(HourMin *alarm, bool *set)
{
    Button hourUpButton(60, 20, 75, 50, false, "+", col1, col2);
    Button hourDownButton(60, 155, 75, 50, false, "-", col1, col2);
    Button minuteUpButton(185, 20, 75, 50, false, "+", col1, col2);
    Button minuteDownButton(185, 155, 75, 50, false, "-", col1, col2);

    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(30, 230);
    M5.Lcd.print("Back");

    while (true)
    {
        // button controls
        if (M5.BtnA.isPressed())
        {
            break;
        }
        else if (M5.BtnC.isPressed())
        {
            *set = *set ? false : true;
            delay(200);
            // draw black rectangle to get rid of previous text
            M5.Lcd.fillRect(250, 210, 50, 25, TFT_BLACK);
        }
        else if (hourUpButton.isPressed())
        {
            alarm->Hour == 23 ? alarm->Hour = 0 : alarm->Hour += 1;
            M5.Lcd.fillRect(50, 70, 250, 80, TFT_BLACK);
        }
        else if (hourDownButton.isPressed())
        {
            alarm->Hour == 0 ? alarm->Hour = 23 : alarm->Hour -= 1;
            M5.Lcd.fillRect(50, 70, 250, 80, TFT_BLACK);
        }
        else if (minuteUpButton.isPressed())
        {
            alarm->Minute == 59 ? alarm->Minute = 0 : alarm->Minute += 1;
            M5.Lcd.fillRect(60, 70, 250, 80, TFT_BLACK);
        }
        else if (minuteDownButton.isPressed())
        {
            alarm->Minute == 0 ? alarm->Minute = 59 : alarm->Minute -= 1;
            M5.Lcd.fillRect(60, 70, 250, 80, TFT_BLACK);
        }

        // write set/unset button
        M5.Lcd.setTextSize(1);
        M5.Lcd.setCursor(250, 230);
        M5.Lcd.printf("%s", *set ? "Unset" : "Set");
        
        // write out time
        M5.Lcd.setTextSize(5);
        M5.Lcd.setCursor(45, 140);
        M5.Lcd.printf("%02d:%02d", alarm->Hour, alarm->Minute);

        M5.update();
        delay(100);
    }

    ClearScreen();

    return;
}

// check whether it is time to play the alarm
void AlarmListener(RTC_TimeTypeDef *time, HourMin *alarm, bool *set)
{
    if ((alarm->Hour == time->Hours) && (alarm->Minute == time->Minutes) && *set == true)
    {
        // cancel the alarm on any touch
        while (!M5.BtnA.isPressed() && !M5.BtnB.isPressed() && !M5.BtnC.isPressed() && !M5.Touch.ispressed())
        {
            // vibrate for alarm
            M5.Axp.SetLDOEnable(3, true);
            delay(500);
            M5.Axp.SetLDOEnable(3, false);
            delay(500);
        }

        M5.Axp.SetLDOEnable(3, false);
        *set = false;
    }

    return;
}
