
/**
 * Read the battery voltage.
 */

void setup() {
  Serial.begin(115200);
  Serial.println();
}

void loop() {
  // Voltage divider halves the input.
  Serial.println(analogRead(26) * 2);
  delay(500);
}
