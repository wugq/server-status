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
uint8_t displayFourBitLedSetString(const displayFourBitLedConfig *config, const char *str);

/**
 * Clear the display
 * @param config Display Config instance
 */
void displayFourBitLedClear(const displayFourBitLedConfig *config);

/**
 * Set the integer number to display
 * @param config Display Config instance
 * @param number the number
 */
void displayFourBitLedSetIntNumber(const displayFourBitLedConfig *config, const int number);

/**
 * Render the content of the display
 * @param config Display Config instance
 */
void displayFourBitLedRender(const displayFourBitLedConfig *config);
