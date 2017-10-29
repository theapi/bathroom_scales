
byte edge1 = 0;

void setup() {
  Serial.begin(115200);
  pinMode(GPIO_NUM_34, INPUT);
  pinMode(GPIO_NUM_21, INPUT);
  pinMode(GPIO_NUM_17, INPUT);
  pinMode(GPIO_NUM_16, INPUT);
}

void loop() {

  int com1 = analogRead(A1);

  // Com high = 2.8V
  if (com1 > 3300 && edge1) {
    
    // Wait for overshoot to settle.
    delay(2);

    // If it's still high then we have the real com pulse.
    com1 = analogRead(A1);
    if (com1 > 3300) {
      edge1 = 0;
      
      byte pin7 = digitalRead(GPIO_NUM_21);
      byte pin8 = digitalRead(GPIO_NUM_17);
      
      //Serial.print(" A0: ");
      //Serial.println(com1);
  
      Serial.print(pin7);
      Serial.println(pin8);
  
      uint32_t pins =  GPIO.in; 
      //Serial.println(pins, BIN);
    }
  } 
  // Com mid high level = 2V
  else if (com1 < 2300) {

    edge1 = 1;
  }

}
