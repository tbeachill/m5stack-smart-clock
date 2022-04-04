#include <M5Core2.h>
#include <Alarm.h>

// button colours
ButtonColors col1 = {DARKGREY, WHITE, WHITE};
ButtonColors col2 = {ORANGE, WHITE, WHITE};

HourMin setTime;
bool isSet = true;

void DrawAlarmControls()
{
    Button hourUpButton    (60, 20, 75, 50, false, "+", col1, col2);
    Button hourDownButton  (60, 155, 75, 50, false, "-", col1, col2);
    Button minuteUpButton  (185, 20, 75, 50, false, "+", col1, col2);
    Button minuteDownButton(185, 155, 75, 50, false, "-", col1, col2);

    setTime.Hour = 0;
    setTime.Minute = 0;

    M5.Lcd.setTextSize(5);
    M5.Lcd.setCursor(45, 140);
    M5.Lcd.printf("%02d", setTime.Hour);
    M5.Lcd.print(":");
    M5.Lcd.printf("%02d", setTime.Minute);

    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(30, 230);
    M5.Lcd.print("Back");

    M5.Lcd.setCursor(250, 230);
    M5.Lcd.printf("%s", isSet ? "Unset" : "Set");
}
