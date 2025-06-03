#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#endif //BUTTON_H

typedef struct {
    int state;
    int pressedCount;
    int stateChanged;
} buttonState;

void buttonCheckState(buttonState *btnState, int newState);

void buttonOnRelease(buttonState *btnState);
