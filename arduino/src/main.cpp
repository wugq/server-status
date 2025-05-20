#include <Arduino.h>
#include <DIYables_4Digit7Segment_74HC595.h> // DIYables_4Digit7Segment_74HC595 library

#define SCLK  4  // The Arduino pin connected to SCLK
#define RCLK  3  // The Arduino pin connected to RCLK
#define DIO   2  // The Arduino pin connected to DIO

constexpr int redBtnPin = 11;
constexpr int yellowBtnPin = 12;
constexpr int ledPin = 13; // the number of the LED pin


int redBtnState = 0;
int yellowBtnState = 0;

unsigned long longPressAt = 0;
bool isPressing = false;
bool isLongPress = false;

bool isPressingYellow = false;

DIYables_4Digit7Segment_74HC595 display(SCLK, RCLK, DIO);

void setup() {
    pinMode(redBtnPin, INPUT);
    pinMode(yellowBtnPin, INPUT);
    pinMode(ledPin, OUTPUT);
    display.printFloat(-9.2, 2, false);
}

void loop() {
    redBtnState = digitalRead(redBtnPin);
    if (redBtnState == HIGH) {
        if (!isPressing) {
            longPressAt = millis();
        }
        isPressing = true;
        isLongPress = (millis() - longPressAt) > 1000;
    } else {
        isPressing = false;
        isLongPress = false;
        longPressAt = 0;
    }

    if (isLongPress) {
        display.printInt(2, false);
    } else if (isPressing) {
        display.printInt(1, false);
    } else {
        display.printInt(0, false);
    }

    yellowBtnState = digitalRead(yellowBtnPin);
    if (yellowBtnState == HIGH) {
        isPressingYellow = true;
        digitalWrite(ledPin, HIGH);
    } else {
        isPressingYellow = false;
        digitalWrite(ledPin, LOW);
    }

    if (isLongPress && isPressingYellow) {
        display.printInt(12, false);
    } else if (isPressingYellow && isPressing) {
        display.printInt(11, false);
    }


    display.loop();
}
