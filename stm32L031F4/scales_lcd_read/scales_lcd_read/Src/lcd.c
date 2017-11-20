#include "lcd.h"

/**
 * Get the current pin values.
 */
uint8_t LCD_getPinValues(void) {
    // Of the GPIOA register, of interest are pins 1-7 & 10
    // so of the 32bit registry: xxxx xxxx xxxx xxxx xxxx x1xx 1111 111x

    uint32_t port = GPIOA->IDR;
    // pins 1-7 & pin 10
    uint8_t pins = 0;
    pins = (port >> 1);
    // Read bit 10 and set its value in the pin variable.
    if (port & GPIO_PIN_10) {
        pins |= 1 << 7;
    } else {
        pins &= ~(1 << 7);
    }

    return pins;
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

