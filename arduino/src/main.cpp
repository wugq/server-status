#include <Arduino.h>

#include "button.h"
#include "displayFourBitLed.h"
#include "serverInfo.h"

#define SCLK  4  // The Arduino pin connected to SCLK
#define RCLK  3  // The Arduino pin connected to RCLK
#define DIO   2  // The Arduino pin connected to DIO

constexpr int RED_BTN_PIN = 11;
constexpr int YELLOW_BTN_PIN = 12;
constexpr int LED_PIN = 13; // The number of the LED pin

int commandIndex = 0;
int commands[4] = {1, 2, 3, 4};

uint8_t LED_BUFFER[4];
displayFourBitLedConfig DISPLAY_FOUR_BIT_LED_CONFIG = {
    .sclk_pin = 0,
    .rclk_pin = 0,
    .dio_pin = 0,
    .buffer = LED_BUFFER
};

buttonState YELLOW_BTN_STATE = {
    .state = LOW,
    .pressedCount = 0,
};
buttonState RED_BTN_STATE = {
    .state = LOW,
    .pressedCount = 0,
};

serverInfoData SERVER_INFO_DATA = {
    .cpuLoad = 0,
    .ipAddress = 0,
};

String readSerialCommand() {
    if (Serial1.available() > 0) {
        return Serial1.readStringUntil('\n');
    }
    return "";
}

void printCommand(const int pressTime) {
    constexpr int commandCount = 3;
    const int cmdIndex = pressTime % commandCount;
    if (cmdIndex == 0) {
        displayFourBitLedSetFloatNumber(&DISPLAY_FOUR_BIT_LED_CONFIG, 12367.9000, 1);
    } else if (cmdIndex == 1) {
        displayFourBitLedSetString(&DISPLAY_FOUR_BIT_LED_CONFIG, "CP90");
    } else if (cmdIndex == 2) {
        displayFourBitLedSetIntNumber(&DISPLAY_FOUR_BIT_LED_CONFIG, 9);
    }
    // const int command = commands[pressTime % commandCount];
}


void checkYellowBtn() {
    // buttonCheckState(&YELLOW_BTN_STATE, digitalRead(YELLOW_BTN_PIN));
    buttonOnRelease(&YELLOW_BTN_STATE);
    if (YELLOW_BTN_STATE.stateChanged) {
        printCommand(YELLOW_BTN_STATE.pressedCount);
    }
}

void checkRedBtn() {
    buttonCheckState(&RED_BTN_STATE, digitalRead(RED_BTN_PIN));
}

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600); // Connect to 0RX,1TX

    pinMode(RED_BTN_PIN, INPUT);
    pinMode(YELLOW_BTN_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    displayFourBitLedInit(&DISPLAY_FOUR_BIT_LED_CONFIG, SCLK, RCLK, DIO);

    attachInterrupt(digitalPinToInterrupt(YELLOW_BTN_PIN), checkYellowBtn, FALLING);
    attachInterrupt(digitalPinToInterrupt(RED_BTN_PIN), checkRedBtn, CHANGE);

    printCommand(YELLOW_BTN_STATE.pressedCount);
}


void loop() {
    displayFourBitLedRender(&DISPLAY_FOUR_BIT_LED_CONFIG);

    const serverInfoData newInfo = {
        .cpuLoad = SERVER_INFO_DATA.cpuLoad + 1,
        .ipAddress = SERVER_INFO_DATA.ipAddress + 1,
    };

    serverInfoSet(&SERVER_INFO_DATA, &newInfo);

    String command = readSerialCommand();
    if (command.length() > 0) {
        Serial.println(command);
        commandIndex++;
        commands[commandIndex % 4] = command.toInt();
        printCommand(YELLOW_BTN_STATE.pressedCount);
    }
}
