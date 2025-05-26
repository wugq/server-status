#include "button.h"
#include <Arduino.h>

void buttonCheckState(buttonState *btnState, const int newState) {
    int changed = 0;
    if (newState == BUTTON_OFF && btnState->state == BUTTON_ON) {
        btnState->pressedCount += 1;
        changed = 1;
    }
    btnState->state = newState;
    btnState->stateChanged = changed;
}
