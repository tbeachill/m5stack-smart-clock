#include <M5Core2.h>
#include <Kasa.h>

// draw buttons
void DrawLightControls()
{
    // pos X, pos Y, width, height
    Button toggleButton(25, 25, 75, 75, false, "On/Off", col1, col2);
    Button brightHighButton(125, 25, 75, 75, false, "High", col1, col2);
    Button brightLowButton(225, 25, 75, 75, false, "Low", col1, col2);

    Button colourFuschiaButton(25, 125, 75, 75, false, "Fuschia", col1, col2);
    Button colourYellowButton(125, 125, 75, 75, false, "Yellow", col1, col2);
    Button colourBlueButton(225, 125, 75, 75, false, "Blue", col1, col2);

    // run functions associated with each button on press
    while (!M5.BtnA.isPressed() && !M5.BtnB.isPressed())
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
