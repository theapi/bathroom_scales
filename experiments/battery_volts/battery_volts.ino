
/**
 * Read the battery voltage.
 */

void setup() {
  Serial.begin(115200);
  Serial.println();

  analogReadResolution(12); //12 bits
}

void loop() {
  // Voltage divider halves the input.
  int val = analogRead(35);
  Serial.print(val);
  Serial.print(" : ");
  //float mv = (3.287 / 4095.0) * val * 2;
  //float mv = 0.805860806 * val * 2;

  // Calibration:
  // 2123 * 2 = 3865 mV
  // 3865 / 4246 = 0.910268488
  
  float mv = 0.910268488 * val * 2;
  Serial.println(mv);
  delay(500);
}
