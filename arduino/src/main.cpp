#include <Arduino.h>
#include <DIYables_4Digit7Segment_74HC595.h> // DIYables_4Digit7Segment_74HC595 library

#define SCLK  4  // The Arduino pin connected to SCLK
#define RCLK  3  // The Arduino pin connected to RCLK
#define DIO   2  // The Arduino pin connected to DIO

constexpr int redBtnPin = 11;
constexpr int yellowBtnPin = 12;
constexpr int ledPin = 13; // the number of the LED pin

int commandIndex = 0;
int commands[4] = {1, 2, 3, 4};

int redBtnState = LOW;
int yellowBtnState = LOW;
int yellowBtnLastState = LOW;
int yellowBtnPressTime = 0;

bool isPressingRed = false;
bool isPressingYellow = false;

DIYables_4Digit7Segment_74HC595 display(SCLK, RCLK, DIO);


String readSerialCommand() {
    if (Serial1.available() > 0) {
        return Serial1.readStringUntil('\n');
    }
    return "";
}

void printCommand() {
    int command = commands[yellowBtnPressTime % 4];
    display.printInt(command, false);
    Serial.println(yellowBtnPressTime);
}

void setup() {
    Serial.begin(9600);
    Serial1.begin(9600); // Connect to 0RX,1TX

    pinMode(redBtnPin, INPUT);
    pinMode(yellowBtnPin, INPUT);
    pinMode(ledPin, OUTPUT);

    printCommand();
}


void loop() {
    display.loop();

    String command = readSerialCommand();
    if (command.length() > 0) {
        Serial.println(command);
        commandIndex++;
        commands[commandIndex % 4] = command.toInt();
        printCommand();
    }

    yellowBtnState = digitalRead(yellowBtnPin);
    if (yellowBtnState == HIGH) {
        isPressingYellow = true;
    } else {
        if (isPressingYellow) {
            yellowBtnPressTime++;
            printCommand();
        }
        isPressingYellow = false;
    }

    redBtnState = digitalRead(redBtnPin);
    if (redBtnState == HIGH) {
        isPressingRed = true;
    } else {
        isPressingRed = false;
    }

    // display.setDot(1);
    // display.setDot(2);
    // display.setDot(3);
    // display.setDot(4);
}
