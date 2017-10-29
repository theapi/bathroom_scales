

#define LCD_PIN_7 GPIO_NUM_21
#define LCD_PIN_8 GPIO_NUM_17
#define COM_HIGH 3300 // The analog reading that indicates active on the com line.


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
  // pins:    x, x, x, x, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
  // 16 bits: 0  0  0  0  0   0   0   0  0  0  0  0  0  0  0  0  0
  // So bit 12 is pin 12.

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

uint8_t segmentsAsNumber(uint8_t segs) {
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
uint8_t getSegmentsForDigit(uint8_t pin1, uint8_t pin2, 
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
 * The value on the screen for digit one.
 */
uint8_t digitDecode0(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins) {
  // Digit zero is pins 5 & 6.
  uint8_t segs = getSegmentsForDigit(5, 6, com3_pins, com2_pins, com1_pins, com0_pins);
  
  return segmentsAsNumber(segs);
}

/**
 * The value on the screen for digit one.
 */
uint8_t digitDecode1(uint16_t com3_pins, uint16_t com2_pins, uint16_t com1_pins, uint16_t com0_pins) {
//  // Digit one is just pins 7 & 8.
//  uint8_t segs = 0;
//  // Place the value for the pins as segments.
//  // A, B, C, D, E, F, G
//  // 0, 1, 2, 3, 4, 5, 6  = bit numbers for the segments.
//  // dots colons etc are ignored
//
//  // COM0:7 = A
//  bitWrite(segs, 0, bitRead(com0_pins, 7));
//  // COM0:8 = F
//  bitWrite(segs, 5, bitRead(com0_pins, 8));
//
//  // COM1:7 = B
//  bitWrite(segs, 1, bitRead(com1_pins, 7));
//  // COM1:8 = G
//  bitWrite(segs, 6, bitRead(com1_pins, 8));
//
//  // COM2:7 = C
//  bitWrite(segs, 2, bitRead(com2_pins, 7));
//  // COM2:8 = E
//  bitWrite(segs, 4, bitRead(com2_pins, 8));
//
//  // COM3:7 = dot
//  // ignore dot
//  // COM3:8 = D
//  bitWrite(segs, 3, bitRead(com3_pins, 8));

  uint8_t segs = getSegmentsForDigit(7, 8, com3_pins, com2_pins, com1_pins, com0_pins);

  return segmentsAsNumber(segs);
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
    
    uint8_t digit1 = digitDecode1(com3_pins, com2_pins, com1_pins, com0_pins);
    Serial.print("DIGIT 1: "); 
    Serial.println(digit1, DEC);
    
    Serial.println();
  }

}

