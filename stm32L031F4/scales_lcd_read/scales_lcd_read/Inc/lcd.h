/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __lcd_H
#define __lcd_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l0xx_hal.h"
#include "main.h"
#include "stdint.h"

/**
 * Get the current pin values.
 */
uint16_t LCD_getPinValues(void);

/**
 * Check COM0 for a high to indicate the start of the frame.
 */
uint8_t LCD_frameStart(void);

/**
 * Translate the segment pattern to the number it represents.
 */
uint8_t LCD_segmentsAsNumber(uint8_t segs);

/**
 * Get the active segments for a digit.
 * Each digit uses only 2 pins.
 */
uint8_t LCD_getSegmentsForDigit(uint8_t pin1, uint8_t pin2,
        uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins);

/**
 * The value on the screen for digit zero.
 */
uint8_t LCD_digitDecode0(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins);

/**
 * The value on the screen for digit one.
 */
uint8_t LCD_digitDecode1(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins);

/**
 * The value on the screen for digit 2.
 */
uint8_t LCD_digitDecode2(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins);

/**
 * The value on the screen for digit 3.
 */
uint8_t LCD_digitDecode3(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins);

void LCD_read(void);

#ifdef __cplusplus
}
#endif
#endif /*__ lcd_H */
