#ifndef BUTTON_H
#define BUTTON_H

#endif //BUTTON_H

typedef enum {
    BUTTON_OFF = 0,
    BUTTON_ON = 1,
} ButtonState;

typedef struct {
    int state;
    int pressedCount;
    int stateChanged;
} buttonState;

void check_button_state(buttonState *btnState, int newState);
