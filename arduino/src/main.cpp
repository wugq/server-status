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

displayFourBitLedConfig DISPLAY_FOUR_BIT_LED_CONFIG;

buttonState YELLOW_BTN_STATE = {
    .state = LOW,
    .pressedCount = 0,
};
buttonState RED_BTN_STATE = {
    .state = LOW,
    .pressedCount = 0,
};

serverInfoData SERVER_INFO_Data = {
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
    constexpr int commandCount = 4;
    const int command = commands[pressTime % commandCount];
}

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600); // Connect to 0RX,1TX

    pinMode(RED_BTN_PIN, INPUT);
    pinMode(YELLOW_BTN_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    displayFourBitLedInit(&DISPLAY_FOUR_BIT_LED_CONFIG, SCLK, RCLK, DIO);

    printCommand(YELLOW_BTN_STATE.pressedCount);
}


void loop() {
    // displayFourBitLedSetString(&DISPLAY_FOUR_BIT_LED_CONFIG, "CP90");
    displayFourBitLedSetIntNumber(&DISPLAY_FOUR_BIT_LED_CONFIG, 9);
    displayFourBitLedRender(&DISPLAY_FOUR_BIT_LED_CONFIG);

    const serverInfoData newInfo = {
        .cpuLoad = SERVER_INFO_Data.cpuLoad + 1,
        .ipAddress = SERVER_INFO_Data.ipAddress + 1,
    };

    serverInfoSet(&SERVER_INFO_Data, &newInfo);

    String command = readSerialCommand();
    if (command.length() > 0) {
        Serial.println(command);
        commandIndex++;
        commands[commandIndex % 4] = command.toInt();
        printCommand(YELLOW_BTN_STATE.pressedCount);
    }

    buttonCheckState(&YELLOW_BTN_STATE, digitalRead(YELLOW_BTN_PIN));
    if (YELLOW_BTN_STATE.stateChanged) {
        printCommand(YELLOW_BTN_STATE.pressedCount);
    }

    buttonCheckState(&RED_BTN_STATE, digitalRead(RED_BTN_PIN));
}
