#include "lcd.h"

/**
 * Get the current pin values.
 */
uint16_t LCD_getPinValues(void) {
    uint16_t pins = 0;
    // pins:    x, x, x, x, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
    // 16 bits: 0  0  0  0  0   0   0   0  0  0  0  0  0  0  0  0  0

    uint32_t pin_values = GPIOA->IDR;
}

/**
 * Check COM0 for a high to indicate the start of the frame.
 */
uint8_t LCD_frameStart(void) {

}

/**
 * Translate the segment pattern to the number it represents.
 */
uint8_t LCD_segmentsAsNumber(uint8_t segs) {

}

/**
 * Get the active segments for a digit.
 * Each digit uses only 2 pins.
 */
uint8_t LCD_getSegmentsForDigit(uint8_t pin1, uint8_t pin2,
        uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins) {

}

/**
 * The value on the screen for digit zero.
 */
uint8_t LCD_digitDecode0(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins) {

}

/**
 * The value on the screen for digit one.
 */
uint8_t LCD_digitDecode1(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins) {

}

/**
 * The value on the screen for digit 2.
 */
uint8_t LCD_digitDecode2(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins) {

}

/**
 * The value on the screen for digit 3.
 */
uint8_t LCD_digitDecode3(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins) {

}

void LCD_read(void) {

}

