#include <Arduino.h>
#include <DIYables_4Digit7Segment_74HC595.h> // DIYables_4Digit7Segment_74HC595 library

#include "button.h"

#define SCLK  4  // The Arduino pin connected to SCLK
#define RCLK  3  // The Arduino pin connected to RCLK
#define DIO   2  // The Arduino pin connected to DIO

constexpr int RED_BTN_PIN = 11;
constexpr int YELLOW_BTN_PIN = 12;
constexpr int LED_PIN = 13; // the number of the LED pin

int commandIndex = 0;
int commands[4] = {1, 2, 3, 4};

DIYables_4Digit7Segment_74HC595 display(SCLK, RCLK, DIO);

buttonState YELLOW_BTN_STATE = {
    .state = LOW,
    .pressedCount = 0,
};
buttonState RED_BTN_STATE = {
    .state = LOW,
    .pressedCount = 0,
};

String readSerialCommand() {
    if (Serial1.available() > 0) {
        return Serial1.readStringUntil('\n');
    }
    return "";
}

void printCommand(const int pressTime) {
    constexpr int commandCount = 4;
    const int command = commands[pressTime % commandCount];
    display.printInt(command, false);
}

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600); // Connect to 0RX,1TX

    pinMode(RED_BTN_PIN, INPUT);
    pinMode(YELLOW_BTN_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    printCommand(YELLOW_BTN_STATE.pressedCount);
}


void loop() {
    display.loop();

    String command = readSerialCommand();
    if (command.length() > 0) {
        Serial.println(command);
        commandIndex++;
        commands[commandIndex % 4] = command.toInt();
        printCommand(YELLOW_BTN_STATE.pressedCount);
    }

    check_button_state(&YELLOW_BTN_STATE, digitalRead(YELLOW_BTN_PIN));
    if (YELLOW_BTN_STATE.stateChanged) {
        printCommand(YELLOW_BTN_STATE.pressedCount);
    }

    check_button_state(&RED_BTN_STATE, digitalRead(RED_BTN_PIN));


    // display.setDot(1);
    // display.setDot(2);
    // display.setDot(3);
    // display.setDot(4);
}
