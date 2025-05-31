#ifndef DISPLAY4BITLED_H
#define DISPLAY4BITLED_H

#endif //DISPLAY4BITLED_H

// ST_CP | RCLK | Latch Pin | Register Clock pin
// SH_CP | SCLK | Clock Pin | Shift Clock Pin.
// DS    | DIO  | Data Pin  | Data Pin
typedef struct {
    int sclk_pin;
    int rclk_pin;
    int dio_pin;
    uint8_t *buffer;
} displayFourBitLedConfig;

typedef enum {

} SegmentChar;


// constexpr uint8_t ARRAY_SIZE = 27;
// inline uint8_t segment_codes[ARRAY_SIZE];
// inline char available_chars[ARRAY_SIZE];
// available_chars[0] = '0';

// available_chars[0] = "0";
// available_chars[1] = "1";
// available_chars[2] = "2";
// available_chars[3] = "3";
// available_chars[4] = "4";
// available_chars[5] = "5";
// available_chars[6] = "6";
// available_chars[7] = "7";
// available_chars[8] = "8";
// available_chars[9] = "9";
// available_chars[10] = "A";
// available_chars[11] = "b";
// available_chars[12] = "D";
// available_chars[13] = "c";
// available_chars[14] = "d";
// available_chars[15] = "E";
// available_chars[16] = "F";
// available_chars[17] = "H";
// available_chars[18] = "h";
// available_chars[19] = "L";
// available_chars[20] = "n";
// available_chars[21] = "I";
// available_chars[22] = "O";
// available_chars[23] = "o";
// available_chars[24] = "P";
// available_chars[25] = "S";
// available_chars[26] = " ";

/**
 * Initialize the display config and set pinMode
 * @param config Display Config instance
 * @param sclk Latch Pin or Register Clock pin
 * @param rclk Clock Pin or Shift Clock Pin.
 * @param dio Data Pin or Data Pin
 */
void displayFourBitLedInit(displayFourBitLedConfig *config, int sclk, int rclk, int dio);

/**
 * Set the string to display
 * @param config Display Config instance
 * @param str the string, maximum 4 bytes
 * @return the length of the string
 */
void displayFourBitLedSetString(const displayFourBitLedConfig *config, const char *str);

void displayFourBitLedRender(const displayFourBitLedConfig *config);
