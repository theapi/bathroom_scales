
HardwareSerial Serial1(2);

void setup() {
  // Main usb serail for debug.
  Serial.begin(115200);
  
  // Listen to the lcd reader.
  Serial1.begin(57600);

  Serial.println("Started");

}

void loop() {

  // Listen for the lcd reader output.
  while (Serial1.available()) {
    byte c = Serial1.read();
    // The weight reading starts with #
    if (c == '#') {
      // Grab the weight
      int weight = Serial1.parseInt();
      Serial.println(weight);
    }

    // Passthru the rest of the data.
    Serial.write(c);
  }

}

