#include "lcd.h"
#include "tx.h"
#include "bit.h"

void LCD_int(LCD_TypeDef *lcd) {
  lcd->pins_com0 = 0;
  lcd->pins_com1 = 0;
  lcd->pins_com2 = 0;
  lcd->pins_com3 = 0;
  lcd->digit0 = 11;
  lcd->digit1 = 11;
  lcd->digit2 = 11;
  lcd->digit3 = 11;
  lcd->same_count = 0;
  lcd->weight = 0;
  lcd->last_weight = 0;
  lcd->last_reading_time = 0;
}

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
  case 0b01101111:
    return 9;
  case 0b01111111:
    return 8;
  case 0b00000111:
    return 7;
  case 0b01111101:
    return 6;
  case 0b01101101:
    return 5;
  case 0b01100110:
    return 4;
  case 0b01001111:
    return 3;
  case 0b01011011:
    return 2;
  case 0b00000110:
    return 1;
  case 0b00111111:
    return 0;
  }

  return 11;
}

/**
 * Get the active segments for a digit.
 * Each digit uses only 2 pins.
 */
uint8_t LCD_getSegmentsForDigit(LCD_TypeDef *lcd, uint8_t pin1, uint8_t pin2) {

  uint8_t segs = 0;
  // Place the value for the pins as segments.
  // A, B, C, D, E, F, G
  // 0, 1, 2, 3, 4, 5, 6  = bit numbers for the segments.
  // dots colons etc are ignored

  // COM0:pin1 = A
  bitWrite(segs, 0, bitRead(lcd->pins_com0, pin1));
  // COM0:pin2 = F
  bitWrite(segs, 5, bitRead(lcd->pins_com0, pin2));

  // COM1:pin1 = B
  bitWrite(segs, 1, bitRead(lcd->pins_com1, pin1));
  // COM1:pin2 = G
  bitWrite(segs, 6, bitRead(lcd->pins_com1, pin2));

  // COM2:pin1 = C
  bitWrite(segs, 2, bitRead(lcd->pins_com2, pin1));
  // COM2:pin2 = E
  bitWrite(segs, 4, bitRead(lcd->pins_com2, pin2));

  // COM3:5 = St
  // ignore
  // COM3:pin2 = D
  bitWrite(segs, 3, bitRead(lcd->pins_com3, pin2));

  return segs;
}

/**
 * The value on the screen for digit zero.
 */
void LCD_digitDecode0(LCD_TypeDef *lcd) {
  // Digit zero is pins 5 & 6.
  uint8_t segs = LCD_getSegmentsForDigit(lcd, 5, 6);
  lcd->digit0 = LCD_segmentsAsNumber(segs);
}

/**
 * The value on the screen for digit one.
 */
uint8_t LCD_digitDecode1(LCD_TypeDef *lcd) {
  // Digit zero is pins 7 & 8.
  uint8_t segs = LCD_getSegmentsForDigit(lcd, 7, 8);
  return LCD_segmentsAsNumber(segs);
}

/**
 * The value on the screen for digit 2.
 */
uint8_t LCD_digitDecode2(LCD_TypeDef *lcd) {
  // Digit zero is pins 9 & 10.
  uint8_t segs = LCD_getSegmentsForDigit(lcd, 9, 10);
  return LCD_segmentsAsNumber(segs);
}

/**
 * The value on the screen for digit 3.
 */
uint8_t LCD_digitDecode3(LCD_TypeDef *lcd) {
  // Digit zero is pins 11 & 12.
  uint8_t segs = LCD_getSegmentsForDigit(lcd, 11, 12);
  return LCD_segmentsAsNumber(segs);
}

void LCD_decodeDigits(LCD_TypeDef *lcd) {
  LCD_digitDecode0(lcd);
  LCD_digitDecode1(lcd);
  LCD_digitDecode2(lcd);
  LCD_digitDecode3(lcd);
}

uint8_t LCD_read(LCD_TypeDef *lcd) {
  uint8_t reading = 0;

  if (LCD_frameStart() == 1) {
    /* Read the pin state while on COM0, then wait for the next COM */
    lcd->pins_com0 = LCD_getPinValues();
    HAL_Delay(LCD_DELAY_BETWEEN_COMS);

    /* Read the pin state while on COM1, then wait for the next COM */
    lcd->pins_com1 = LCD_getPinValues();
    HAL_Delay(LCD_DELAY_BETWEEN_COMS);

    /* Read the pin state while on COM2, then wait for the next COM */
    lcd->pins_com2 = LCD_getPinValues();
    HAL_Delay(LCD_DELAY_BETWEEN_COMS);

    /* Read the pin state while on COM3, then wait for the next COM */
    lcd->pins_com3 = LCD_getPinValues();
    HAL_Delay(LCD_DELAY_BETWEEN_COMS);

    /* A new reading has been collected. */
    reading = 1;
  }

  return reading;
}

uint8_t LCD_pollForWeight(LCD_TypeDef *lcd) {
  uint8_t valid = 0;
  uint16_t now = HAL_GetTick();
  uint16_t value = 0;

  /* Wait for a valid weight reading */
  if (now - lcd->last_reading_time >= LCD_READ_INTERVAL) {
    lcd->last_reading_time = now;

    value = LCD_read(lcd);
    if (value == 0) {
      /* Cause another reading to happen. */
      lcd->last_reading_time = 0;
      return valid;
    } else {
      LCD_decodeDigits(lcd);

      // The ones digit has a value.
      if (lcd->digit1 != 11) {
        lcd->weight = (lcd->digit3 * 1000) + (lcd->digit2 * 100) + (lcd->digit1 * 10) + lcd->digit0;

        if (lcd->last_weight == lcd->weight) {
          lcd->same_count++;

          /* Got enough readings the same to qualify as the reading */
          if (lcd->same_count > LCD_SAME_COUNT) {
            lcd->same_count = 0;

            /* Got a useful weight reading */
            valid = 1;
            return valid;
          }

        } else {
          /* Different weight value than before */
          lcd->same_count = 0;
        }
        lcd->last_weight = lcd->weight;
      } else {
        /* Not a real value */
        lcd->last_weight = 0;
      }

    }
  }

  return valid;
}

