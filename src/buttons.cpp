#include "buttons.h"
#include "relays.h"
#include "main.h"

Button2 btnBoost;

void ButtonClickHandler(Button2 &btn)
{
    if (btn == btnBoost)
    {
        StartRelay(appSettings.duration * 60);
    }
}

void TripleClickHandler(Button2 &btn)
{
    StopRelay();
}

void setupButtons()
{
    btnBoost.begin(BOOST_GPIO, INPUT_PULLUP, true);
    btnBoost.setClickHandler(ButtonClickHandler);
    btnBoost.setTripleClickHandler(TripleClickHandler);
}

void loopButtons()
{
    btnBoost.loop();
}
