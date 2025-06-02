#include <Arduino.h>

#include "button.h"
#include "displayFourBitLed.h"
#include "serverInfo.h"
#include "serverInfoDisplay.h"
#include "messageParser.h"

#define SCLK  4  // The Arduino pin connected to SCLK
#define RCLK  3  // The Arduino pin connected to RCLK
#define DIO   2  // The Arduino pin connected to DIO

constexpr int RED_BTN_PIN = 11;
constexpr int YELLOW_BTN_PIN = 12;
constexpr int LED_PIN = 13; // The number of the LED pin

int commandIndex = 0;
int commands[4] = {1, 2, 3, 4};

/********************************************************/
uint8_t LED_BUFFER[4];
displayFourBitLedConfig DISPLAY_FOUR_BIT_LED_CONFIG = {
    .sclk_pin = 0,
    .rclk_pin = 0,
    .dio_pin = 0,
    .buffer = LED_BUFFER
};

/********************************************************/
buttonState YELLOW_BTN_STATE = {
    .state = LOW,
    .pressedCount = 0,
};
buttonState RED_BTN_STATE = {
    .state = LOW,
    .pressedCount = 0,
};

/********************************************************/
char SERVER_INFO_IP_ADDRESS[IPADDRESS_SIZE] = "";
serverInfoData SERVER_INFO_DATA = {
    .functionCount = 0,
    .cpuLoad = 0,
    .ipAddress = SERVER_INFO_IP_ADDRESS,
};

/********************************************************/
char SERVER_INFO_DISPLAY_MESSAGE[20] = "____";
serverInfoDisplayData SERVER_INFO_DISPLAY_DATA = {
    .index = 0,
    .message = SERVER_INFO_DISPLAY_MESSAGE,
};

/********************************************************/
uint8_t messageBuffer[MESSAGE_PARSER_BUFFER_SIZE];
messageParserBuffer MESSAGE_PARSER_BUFFER = {
    .message = messageBuffer,
    .currentIndex = 0
};

void readSerialData() {
    if (Serial1.available() <= 0) {
        return;
    }
    const int c = Serial1.read();
    messageParserDoParse(&SERVER_INFO_DATA, &MESSAGE_PARSER_BUFFER, c);
}

void onReleaseYellowBtn() {
    buttonOnRelease(&YELLOW_BTN_STATE);

    serverInfoDisplaySetMessage(&SERVER_INFO_DISPLAY_DATA, &SERVER_INFO_DATA, &YELLOW_BTN_STATE);
    serverInfoDisplaySetDisplay(&SERVER_INFO_DISPLAY_DATA, &DISPLAY_FOUR_BIT_LED_CONFIG);
}

void onReleaseRedBtn() {
    buttonCheckState(&RED_BTN_STATE, digitalRead(RED_BTN_PIN));
    serverInfoDisplaySetDisplay(&SERVER_INFO_DISPLAY_DATA, &DISPLAY_FOUR_BIT_LED_CONFIG);
}

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600); // Connect to 0RX,1TX

    pinMode(RED_BTN_PIN, INPUT);
    pinMode(YELLOW_BTN_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);

    serverInfoInit(&SERVER_INFO_DATA);

    displayFourBitLedInit(&DISPLAY_FOUR_BIT_LED_CONFIG, SCLK, RCLK, DIO);

    attachInterrupt(digitalPinToInterrupt(YELLOW_BTN_PIN), onReleaseYellowBtn, FALLING);
    attachInterrupt(digitalPinToInterrupt(RED_BTN_PIN), onReleaseRedBtn, FALLING);

    serverInfoDisplaySetDisplay(&SERVER_INFO_DISPLAY_DATA, &DISPLAY_FOUR_BIT_LED_CONFIG);
}


void loop() {
    displayFourBitLedRender(&DISPLAY_FOUR_BIT_LED_CONFIG);

    readSerialData();
}
