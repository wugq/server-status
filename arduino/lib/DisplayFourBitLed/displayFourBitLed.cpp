#include "displayFourBitLed.h"
#include <Arduino.h>

// ============= values =============

/*
 * common labeling:
 *   aaa    |   000
 *  f   b   |  5   1
 *  f   b   |  5   1
 *   ggg    |   666
 *  e   c   |  4   2
 *  e   c   |  4   2
 *   ddd dp |   333 77
 *
 * bits mapping
 * 0 | a
 * 1 | b
 * 2 | c
 * 3 | d
 * 4 | e
 * 5 | f
 * 6 | g
 * 7 | dp
*/

// 0 is on, 1 is off;

#define DISPLAY_FONT_ICON_SPACE 0b11111111
#define DISPLAY_FONT_ICON_DASH 0b10111111
#define DISPLAY_FONT_ICON_DOT 0b01111111
#define DISPLAY_FONT_ICON_UNDERSCORE 0b11110111
#define DISPLAY_FONT_NUMBER_0 0b11000000
#define DISPLAY_FONT_NUMBER_1 0b11111001
#define DISPLAY_FONT_NUMBER_2 0b10100100
#define DISPLAY_FONT_NUMBER_3 0b10110000
#define DISPLAY_FONT_NUMBER_4 0b10011001
#define DISPLAY_FONT_NUMBER_5 0b10010010
#define DISPLAY_FONT_NUMBER_6 0b10000011
#define DISPLAY_FONT_NUMBER_7 0b11111000
#define DISPLAY_FONT_NUMBER_8 0b10000000
#define DISPLAY_FONT_NUMBER_9 0b10011000
#define DISPLAY_FONT_LETTER_A 0b10001000
#define DISPLAY_FONT_LETTER_B 0b10000011
#define DISPLAY_FONT_LETTER_C 0b10100111
#define DISPLAY_FONT_LETTER_D 0b10100001
#define DISPLAY_FONT_LETTER_E 0b10000110
#define DISPLAY_FONT_LETTER_F 0b10001110
#define DISPLAY_FONT_LETTER_G 0b10010000
#define DISPLAY_FONT_LETTER_H 0b10001001
#define DISPLAY_FONT_LETTER_I 0b11111001
#define DISPLAY_FONT_LETTER_J 0b11100001
#define DISPLAY_FONT_LETTER_K 0b10001111
#define DISPLAY_FONT_LETTER_L 0b11000111
#define DISPLAY_FONT_LETTER_M 0b11001000
#define DISPLAY_FONT_LETTER_N 0b10101011
#define DISPLAY_FONT_LETTER_O 0b10100011
#define DISPLAY_FONT_LETTER_P 0b10001100
#define DISPLAY_FONT_LETTER_Q DISPLAY_FONT_NUMBER_9
#define DISPLAY_FONT_LETTER_R 0b10101111
#define DISPLAY_FONT_LETTER_S 0b10010010
#define DISPLAY_FONT_LETTER_T 0b10000111
#define DISPLAY_FONT_LETTER_U 0b11000001
#define DISPLAY_FONT_LETTER_V 0b11100011
#define DISPLAY_FONT_LETTER_W 0b11000001
#define DISPLAY_FONT_LETTER_X 0b11001001
#define DISPLAY_FONT_LETTER_Y 0b10010001
#define DISPLAY_FONT_LETTER_Z 0b10100100

// ============= private methods =============
void shift(const displayFourBitLedConfig *config, uint8_t value) {
    for (uint8_t i = 8; i >= 1; i--) {
        if (value & 0x80) {
            digitalWrite(config->dio_pin, HIGH);
        } else {
            digitalWrite(config->dio_pin, LOW);
        }
        value <<= 1;
        digitalWrite(config->sclk_pin, LOW);
        digitalWrite(config->sclk_pin, HIGH);
    }
}

void render(const displayFourBitLedConfig *config, const uint8_t value, const uint8_t position) {
    shift(config, value);
    const int digit = 0x08 >> position;
    shift(config, digit);
    digitalWrite(config->rclk_pin, LOW);
    digitalWrite(config->rclk_pin, HIGH);
}

uint8_t getChar(const char ch) {
    if (ch == 'a' || ch == 'A') {
        return DISPLAY_FONT_LETTER_A;
    } else if (ch == 'b' || ch == 'B') {
        return DISPLAY_FONT_LETTER_B;
    } else if (ch == 'c' || ch == 'C') {
        return DISPLAY_FONT_LETTER_C;
    } else if (ch == 'd' || ch == 'D') {
        return DISPLAY_FONT_LETTER_D;
    } else if (ch == 'e' || ch == 'E') {
        return DISPLAY_FONT_LETTER_E;
    } else if (ch == 'f' || ch == 'F') {
        return DISPLAY_FONT_LETTER_F;
    } else if (ch == 'g' || ch == 'G') {
        return DISPLAY_FONT_LETTER_G;
    } else if (ch == 'h' || ch == 'H') {
        return DISPLAY_FONT_LETTER_H;
    } else if (ch == 'i' || ch == 'I') {
        return DISPLAY_FONT_LETTER_I;
    } else if (ch == 'j' || ch == 'J') {
        return DISPLAY_FONT_LETTER_J;
    } else if (ch == 'k' || ch == 'K') {
        return DISPLAY_FONT_LETTER_K;
    } else if (ch == 'l' || ch == 'L') {
        return DISPLAY_FONT_LETTER_L;
    } else if (ch == 'm' || ch == 'M') {
        return DISPLAY_FONT_LETTER_M;
    } else if (ch == 'n' || ch == 'N') {
        return DISPLAY_FONT_LETTER_N;
    } else if (ch == 'o' || ch == 'O') {
        return DISPLAY_FONT_LETTER_O;
    } else if (ch == 'p' || ch == 'P') {
        return DISPLAY_FONT_LETTER_P;
    } else if (ch == 'q' || ch == 'Q') {
        return DISPLAY_FONT_LETTER_Q;
    } else if (ch == 'r' || ch == 'R') {
        return DISPLAY_FONT_LETTER_R;
    } else if (ch == 's' || ch == 'S') {
        return DISPLAY_FONT_LETTER_S;
    } else if (ch == 't' || ch == 'T') {
        return DISPLAY_FONT_LETTER_T;
    } else if (ch == 'u' || ch == 'U') {
        return DISPLAY_FONT_LETTER_U;
    } else if (ch == 'v' || ch == 'V') {
        return DISPLAY_FONT_LETTER_V;
    } else if (ch == 'w' || ch == 'W') {
        return DISPLAY_FONT_LETTER_W;
    } else if (ch == 'x' || ch == 'X') {
        return DISPLAY_FONT_LETTER_X;
    } else if (ch == 'y' || ch == 'Y') {
        return DISPLAY_FONT_LETTER_Y;
    } else if (ch == 'z' || ch == 'Z') {
        return DISPLAY_FONT_LETTER_Z;
    } else if (ch == ' ') {
        return DISPLAY_FONT_ICON_SPACE;
    } else if (ch == '-') {
        return DISPLAY_FONT_ICON_DASH;
    } else if (ch == '_') {
        return DISPLAY_FONT_ICON_UNDERSCORE;
    } else if (ch == '0') {
        return DISPLAY_FONT_NUMBER_0;
    } else if (ch == '1') {
        return DISPLAY_FONT_NUMBER_1;
    } else if (ch == '2') {
        return DISPLAY_FONT_NUMBER_2;
    } else if (ch == '3') {
        return DISPLAY_FONT_NUMBER_3;
    } else if (ch == '4') {
        return DISPLAY_FONT_NUMBER_4;
    } else if (ch == '5') {
        return DISPLAY_FONT_NUMBER_5;
    } else if (ch == '6') {
        return DISPLAY_FONT_NUMBER_6;
    } else if (ch == '7') {
        return DISPLAY_FONT_NUMBER_7;
    } else if (ch == '8') {
        return DISPLAY_FONT_NUMBER_8;
    } else if (ch == '9') {
        return DISPLAY_FONT_NUMBER_9;
    } else if (ch == '~' || ch == ':') {
        return DISPLAY_FONT_ICON_DASH;
    } else {
        return DISPLAY_FONT_ICON_SPACE;
    }
}

uint8_t getNumber(const int number) {
    if (number == 0) {
        return DISPLAY_FONT_NUMBER_0;
    } else if (number == 1) {
        return DISPLAY_FONT_NUMBER_1;
    } else if (number == 2) {
        return DISPLAY_FONT_NUMBER_2;
    } else if (number == 3) {
        return DISPLAY_FONT_NUMBER_3;
    } else if (number == 4) {
        return DISPLAY_FONT_NUMBER_4;
    } else if (number == 5) {
        return DISPLAY_FONT_NUMBER_5;
    } else if (number == 6) {
        return DISPLAY_FONT_NUMBER_6;
    } else if (number == 7) {
        return DISPLAY_FONT_NUMBER_7;
    } else if (number == 8) {
        return DISPLAY_FONT_NUMBER_8;
    } else if (number == 9) {
        return DISPLAY_FONT_NUMBER_9;
    } else {
        return DISPLAY_FONT_ICON_SPACE;
    }
}

// ============= public methods =============
void displayFourBitLedInit(displayFourBitLedConfig *config, const int sclk, const int rclk, const int dio) {
    config->sclk_pin = sclk;
    config->rclk_pin = rclk;
    config->dio_pin = dio;
    config->buffer[0] = DISPLAY_FONT_ICON_SPACE;
    config->buffer[1] = DISPLAY_FONT_ICON_SPACE;
    config->buffer[2] = DISPLAY_FONT_ICON_SPACE;
    config->buffer[3] = DISPLAY_FONT_ICON_SPACE;

    pinMode(config->sclk_pin, OUTPUT);
    pinMode(config->rclk_pin, OUTPUT);
    pinMode(config->dio_pin, OUTPUT);
}

void displayFourBitLedRender(const displayFourBitLedConfig *config) {
    for (int i = 0; i < 4; i++) {
        render(config, config->buffer[i], i);
    }
}

uint8_t displayFourBitLedSetString(const displayFourBitLedConfig *config, const char *str) {
    uint8_t index = 0;
    uint8_t position = 0;
    uint8_t previousIsNumber = 0;

    for (; index < 8 && position < 4; index++) {
        if (str[index] == '\0') {
            break;
        }

        if (previousIsNumber == 1 && str[index] == '.') {
            config->buffer[position - 1] &= DISPLAY_FONT_ICON_DOT;
            previousIsNumber = 0;
            continue;
        }

        config->buffer[position] = getChar(str[index]);
        position++;
        if (str[index] <= '9' && str[index] >= '0') {
            previousIsNumber = 1;
        }
    }

    if (position == 4 && previousIsNumber == 1 && str[index] == '.') {
        config->buffer[position - 1] &= DISPLAY_FONT_ICON_DOT;
        index++;
    }

    for (; position < 4; position++) {
        config->buffer[position] = DISPLAY_FONT_ICON_SPACE;
    }

    return index;
}

void displayFourBitLedClear(const displayFourBitLedConfig *config) {
    for (uint8_t i = 0; i < 4; i++) {
        config->buffer[i] = DISPLAY_FONT_ICON_SPACE;
    }
}

void displayFourBitLedSetIntNumber(const displayFourBitLedConfig *config, const int number) {
    int base = 10000;
    int theNumber = number % base;
    uint8_t isNumberStarted = 0;

    base /= 10;
    for (int i = 0; i < 4; i++) {
        const int num = theNumber / base;

        if (num != 0) {
            isNumberStarted = 1;
        }

        theNumber %= base;
        base /= 10;
        if (num == 0 && isNumberStarted == 0 && i != 3) {
            config->buffer[i] = DISPLAY_FONT_ICON_SPACE;
        } else {
            config->buffer[i] = getNumber(num);
        }
    }
}


void displayFourBitLedSetFloatNumber(const displayFourBitLedConfig *config, const float number, int precision) {
    const float divisor = pow(10, 4);
    const float remainder = fmod(number, divisor);

    if (precision > 3) {
        precision = 3;
    } else if (precision < 0) {
        precision = 0;
    }

    const int theNumber = remainder * pow(10, precision);
    displayFourBitLedSetIntNumber(config, theNumber);
    config->buffer[3 - precision] &= DISPLAY_FONT_ICON_DOT;
}
