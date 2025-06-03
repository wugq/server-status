#include "button.h"
#include <Arduino.h>

// ============= public methods =============
void buttonCheckState(buttonState *btnState, const int newState) {
    int changed = 0;
    if (newState == LOW && btnState->state == HIGH) {
        btnState->pressedCount += 1;
        changed = 1;
    }
    btnState->state = newState;
    btnState->stateChanged = changed;
}

void buttonOnRelease(buttonState *btnState) {
    btnState->pressedCount += 1;
    btnState->state = LOW;
    btnState->stateChanged = 1;
}
