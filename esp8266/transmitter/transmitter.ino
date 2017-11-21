/**
 * Takes serial input and sends rthe weight to a server
 */

#include <WiFi.h>
#include "credentials.h"

#define PIN_COM D8

byte tx = 0;

const char* host = "192.168.0.22";

void setup() {
  pinMode(PIN_COM, OUTPUT);
  digitalWrite(PIN_COM, HIGH);

  // Listen to the lcd reader.
  Serial.begin(57600);

  delay(10);

  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  WiFi.begin(WIFI_SID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }


  // Tell the reader the transmitter is ready.
  digitalWrite(PIN_COM, LOW);

}

void loop() {

  // Listen for the lcd reader output.
  while (Serial.available()) {
    byte c = Serial.read();

    // Transmit only once. The reader will then cut the power.
    if (tx == 0) {
      // The weight reading starts with #
      if (c == '#') {
        // Grab the weight
        int weight = Serial.parseInt();
        tx = 1;
        //transmit(weight);
  
        // Tell the reader the transmitter is finished.
        digitalWrite(PIN_COM, HIGH);
      }
    }
  }
}

void transmit(int weight) {

    // Read the battery voltage.
    int battery = battery_mv();

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        return;
    }

    char url[100];
    snprintf(url, 100, "http://192.168.0.22/bathroom_scales.php?w=%d&b=%d", weight, battery);


    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            client.stop();
            return;
        }
    }


}

int battery_mv() { return 1234;
  int val = 0;
  float mv = 0;

  // Junk the first reading
  val = analogRead(35);
  val = analogRead(35);
  //float mv = (3.287 / 4095.0) * val * 2;
  // Calibration:
  // 2123 * 2 = 3865 mV
  // 3865 / 4246 = 0.910268488
  mv = 0.910268488 * val * 2;
  return mv;
}

