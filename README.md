# M5Stack Smart Clock

## About
 - This was done as my final project for CS50x.
 - I used PlatformIO and Arduino libraries to program an M5Stack Core 2.

### Clock / Weather
 - Displays the current time, date and day of the week.
 - Weather information is shown for the current day.
   - High temperature
   - Low temperature
   - Amount of rain
   - Chance of rain
 - An alarm can be set by touching the screen.
   - On this screen the time of the alarm can be chosen using the + and - buttons
   - The alarm is set or unset using the right button on the M5Stack.
   - The alarm causes the device to vibrate until a button or the screen is pressed.
   - The screen is exited by pressing the left button.

### Game Statistics
 - The second page shows the following statistics of Roblox games I have created:
   - People currently playing
   - Number of total visits
   - Number of favourites
 - The stats are updated every 5 minutes while the page is open.
 - If more people are playing now than the previous 5 minutes, a short vibration notification is played.

### Smart Bulb Control
 - This page contains six buttons for control of a TP-Link Kasa smartbulb.
 - Each button performs a web request which produces the desired outcome through IFTTT.
