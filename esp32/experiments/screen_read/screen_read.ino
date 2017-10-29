
#include <driver/adc.h>

#define LCD_PIN_7 GPIO_NUM_21
#define LCD_PIN_8 GPIO_NUM_17
#define COM_HIGH 3300 // The analog reading that indicates active on the com line.
#define COM_LOW 3300 // The analog reading that indicates the com line is no longer active.

// pins:    x, x, x, x, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
// 16 bits: 0  0  0  0  0   0   0   0  0  0  0  0  0  0  0  0  0
// So bit 12 is pin 12.

/**
 * How long to wait before updating the read out.
 */
const long read_out_interval = 500;

/**
 * Get the current pin values.
 */
uint16_t getPinValues() {
  //uint32_t vals =  GPIO.in; 
  uint16_t pins = 0;
  
//  bitWrite(pins, 5, digitalRead(LCD_PIN_5));
//  bitWrite(pins, 6, digitalRead(LCD_PIN_6));
  bitWrite(pins, 7, digitalRead(LCD_PIN_7));
  bitWrite(pins, 8, digitalRead(LCD_PIN_8));
//  bitWrite(pins, 9, digitalRead(LCD_PIN_9));
//  bitWrite(pins, 10, digitalRead(LCD_PIN_10));
//  bitWrite(pins, 11, digitalRead(LCD_PIN_11));
//  bitWrite(pins, 12, digitalRead(LCD_PIN_12));

  return pins;
}

/**
 * Check COM0 for a high to indicate the start of the frame.
 */
uint8_t frameStart() {
  static byte edge = 0;
  uint8_t start = 0;

  // Com high = 2.8V
  int com = analogRead(A0); 
  if (com > COM_HIGH) {
    // Wait for overshoot to settle.
    delay(2);

    // If it's still high then we have the real com pulse.
    com = analogRead(A0);
    if (com > COM_HIGH) {
      edge = 0;
      start = 1;
    }
  } 

  return start;
}

void setup() {
  Serial.begin(115200);
  pinMode(LCD_PIN_7, INPUT);
  pinMode(LCD_PIN_8, INPUT);
}

void loop() {
  static unsigned long read_out_last = 0;

  static uint16_t com0_pins = 0;
  static uint16_t com1_pins = 0;
  static uint16_t com2_pins = 0;
  static uint16_t com3_pins = 0;

  uint8_t start = frameStart();
  if (start) {
    // COM0 at the start;
    com0_pins = getPinValues();

    // 4 ms between COMs
    delay(4);
    // COM1
    com1_pins = getPinValues();
    delay(4);
    // COM2
    com2_pins = getPinValues();
    delay(4);
    // COM3
    com3_pins = getPinValues();
    
  }

  unsigned long now = millis();
  if (now - read_out_last >= read_out_interval) {
    read_out_last = now;

    Serial.print("COM0: "); 
    Serial.println(com0_pins, BIN);
    Serial.print("COM1: "); 
    Serial.println(com1_pins, BIN);
    Serial.print("COM2: "); 
    Serial.println(com2_pins, BIN);
    Serial.print("COM3: "); 
    Serial.println(com3_pins, BIN);
    Serial.println();
  }

}

