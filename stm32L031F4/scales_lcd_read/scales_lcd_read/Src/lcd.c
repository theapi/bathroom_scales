#include "lcd.h"
#include "bit.h"

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
    uint8_t start = 0;

    HAL_ADC_PollForConversion(&hadc, 100);
    uint32_t com = HAL_ADC_GetValue(&hadc);
    if (com > LCD_COM_HIGH) {
        // Wait for overshoot to settle.
        HAL_Delay(2);

        // If it's still high then we have the real com pulse.
        HAL_ADC_PollForConversion(&hadc, 100);
        com = HAL_ADC_GetValue(&hadc);
        if (com > LCD_COM_HIGH) {
          start = 1;
        }
    }

    return start;
}

/**
 * Translate the segment pattern to the number it represents.
 */
uint8_t LCD_segmentsAsNumber(uint8_t segs) {
    switch (segs) {
        //     .GFEDCBA
        case 0b01101111: return 9;
        case 0b01111111: return 8;
        case 0b00000111: return 7;
        case 0b01111101: return 6;
        case 0b01101101: return 5;
        case 0b01100110: return 4;
        case 0b01001111: return 3;
        case 0b01011011: return 2;
        case 0b00000110: return 1;
        case 0b00111111: return 0;
    }

    return 11;
}

/**
 * Get the active segments for a digit.
 * Each digit uses only 2 pins.
 */
uint8_t LCD_getSegmentsForDigit(uint8_t pin1, uint8_t pin2,
        uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins) {

      uint8_t segs = 0;
      // Place the value for the pins as segments.
      // A, B, C, D, E, F, G
      // 0, 1, 2, 3, 4, 5, 6  = bit numbers for the segments.
      // dots colons etc are ignored

      // COM0:pin1 = A
      bitWrite(segs, 0, bitRead(com0_pins, pin1));
      // COM0:pin2 = F
      bitWrite(segs, 5, bitRead(com0_pins, pin2));

      // COM1:pin1 = B
      bitWrite(segs, 1, bitRead(com1_pins, pin1));
      // COM1:pin2 = G
      bitWrite(segs, 6, bitRead(com1_pins, pin2));

      // COM2:pin1 = C
      bitWrite(segs, 2, bitRead(com2_pins, pin1));
      // COM2:pin2 = E
      bitWrite(segs, 4, bitRead(com2_pins, pin2));

      // COM3:5 = St
      // ignore
      // COM3:pin2 = D
      bitWrite(segs, 3, bitRead(com3_pins, pin2));

      return segs;
}

/**
 * The value on the screen for digit zero.
 */
uint8_t LCD_digitDecode0(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins) {
    // Digit zero is pins 5 & 6.
    uint8_t segs = getSegmentsForDigit(5, 6, com3_pins, com2_pins, com1_pins, com0_pins);
    return segmentsAsNumber(segs);
}

/**
 * The value on the screen for digit one.
 */
uint8_t LCD_digitDecode1(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins) {
    // Digit zero is pins 7 & 8.
    uint8_t segs = getSegmentsForDigit(7, 8, com3_pins, com2_pins, com1_pins, com0_pins);
    return segmentsAsNumber(segs);
}

/**
 * The value on the screen for digit 2.
 */
uint8_t LCD_digitDecode2(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins) {
    // Digit zero is pins 9 & 10.
    uint8_t segs = getSegmentsForDigit(9, 10, com3_pins, com2_pins, com1_pins, com0_pins);
    return segmentsAsNumber(segs);
}

/**
 * The value on the screen for digit 3.
 */
uint8_t LCD_digitDecode3(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins) {
    // Digit zero is pins 11 & 12.
    uint8_t segs = getSegmentsForDigit(11, 12, com3_pins, com2_pins, com1_pins, com0_pins);
    return segmentsAsNumber(segs);
}

uint8_t LCD_read(void) {
    uint8_t reading = 0;

    if (LCD_frameStart() == 1) {
        /* Read the pin state while on COM0, then wait for the next COM */
        lcd.pins_com0 = LCD_getPinValues();
        HAL_Delay(LCD_DELAY_BETWEEN_COMS);

        /* Read the pin state while on COM1, then wait for the next COM */
        lcd.pins_com1 = LCD_getPinValues();
        HAL_Delay(LCD_DELAY_BETWEEN_COMS);

        /* Read the pin state while on COM2, then wait for the next COM */
        lcd.pins_com2 = LCD_getPinValues();
        HAL_Delay(LCD_DELAY_BETWEEN_COMS);

        /* Read the pin state while on COM3, then wait for the next COM */
        lcd.pins_com3 = LCD_getPinValues();
        HAL_Delay(LCD_DELAY_BETWEEN_COMS);

        /* A new reading has been collected. */
        reading = 1;
    }

    return reading;
}

