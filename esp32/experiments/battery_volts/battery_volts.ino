
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
  // 2128 * 2 = 3726
  // 4256 val = 3726 mv
  // 3276 ÷ 4256 = 0.769736842

  // 2128 = 1863
  // 0.875469925


  // 2096 = 1856
  // 1856 / 2096 = 0.885496183
  float mv = 0.885496183 * val * 2;
  Serial.println(mv);
  delay(500);
}
