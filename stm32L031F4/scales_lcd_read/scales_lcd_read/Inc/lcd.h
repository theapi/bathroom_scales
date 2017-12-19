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
 * The analog reading that indicates active on the com line.
 */
#define LCD_COM_HIGH 3300
/**
 * How long before the next com is ready for reading.
 */
#define LCD_DELAY_BETWEEN_COMS 4
/**
 * How long to wait between lcd reads.
 */
#define LCD_READ_INTERVAL 250
/**
 * How many times the reading is the same to qualify as the steady weight.
 */
#define LCD_SAME_COUNT 32

/**
 * @brief Scales_TypeDef
 */
typedef struct {
    uint8_t pins_com0;
    uint8_t pins_com1;
    uint8_t pins_com2;
    uint8_t pins_com3;
    uint8_t digit0;
    uint8_t digit1;
    uint8_t digit2;
    uint8_t digit3;
    uint8_t same_count;
    uint16_t weight;
    uint16_t last_weight;
    uint16_t last_reading_time;
} LCD_TypeDef;

//extern LCD_TypeDef lcd;

extern ADC_HandleTypeDef hadc;

/**
 * Get the current pin values.
 */
uint8_t LCD_getPinValues(void);

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
uint8_t LCD_getSegmentsForDigit(LCD_TypeDef *lcd, uint8_t pin1, uint8_t pin2);

/**
 * The value on the screen for digit zero.
 */
void LCD_digitDecode0(LCD_TypeDef *lcd);

/**
 * The value on the screen for digit one.
 */
uint8_t LCD_digitDecode1(LCD_TypeDef *lcd);

/**
 * The value on the screen for digit 2.
 */
uint8_t LCD_digitDecode2(LCD_TypeDef *lcd);

/**
 * The value on the screen for digit 3.
 */
uint8_t LCD_digitDecode3(LCD_TypeDef *lcd);

uint8_t LCD_read(LCD_TypeDef *lcd);

uint8_t LCD_pollForWeight(LCD_TypeDef *lcd);

void LCD_decodeDigits(LCD_TypeDef *lcd);

void LCD_int(LCD_TypeDef *lcd);

#ifdef __cplusplus
}
#endif
#endif /*__ lcd_H */
