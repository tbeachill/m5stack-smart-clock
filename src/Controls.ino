#include <M5Core2.h>
#include <Kasa.h>

ButtonColors col = {DARKGREY, WHITE, WHITE};
ButtonColors col2 = {ORANGE, WHITE, WHITE};


void DrawControls()
{
    // pos X, pos Y, width, height
    Button toggleButton(25, 25, 75, 75, false, "On/Off", col, col2);
    Button brightHighButton(125, 25, 75, 75, false, "High", col, col2);
    Button brightLowButton(225, 25, 75, 75, false, "Low", col, col2);

    Button colourFuschiaButton(25, 125, 75, 75, false, "Fuschia", col, col2);
    Button colourYellowButton(125, 125, 75, 75, false, "Yellow", col, col2);
    Button colourBlueButton(225, 125, 75, 75, false, "Blue", col, col2);

    while (!M5.BtnA.isPressed() && !M5.BtnB.isPressed() && !M5.BtnC.isPressed())
    {
        if (toggleButton.isPressed())
        {
            KasaEvent(Toggle);
        }
        else if (brightHighButton.isPressed())
        {
            KasaEvent(Dim100);
        }
        else if (brightLowButton.isPressed())
        {
            KasaEvent(Dim10);
        }
        else if (colourFuschiaButton.isPressed())
        {
            KasaEvent(kFuschia);
        }
        else if (colourYellowButton.isPressed())
        {
            KasaEvent(kYellow);
        }
        else if (colourBlueButton.isPressed())
        {
            KasaEvent(kBlue);
        }

        M5.update();
    }
    
    return;
}
