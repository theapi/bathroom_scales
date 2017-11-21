/**
 * Takes serial input and sends rthe weight to a server
 */

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include "soc/rtc.h"
#include "credentials.h"

#define PIN_COM  GPIO_NUM_21 // for basic communication with the lcd reader.

HardwareSerial Serial1(2);
WiFiMulti wifiMulti;

byte tx = 0;

void setup() {
  // Slow down the cpu fora bit of power saving.
  rtc_clk_cpu_freq_set(RTC_CPU_FREQ_80M);
    
  // Main usb serail for debug.
  Serial.begin(115200);
  
  // Listen to the lcd reader.
  Serial1.begin(57600);

  pinMode(PIN_COM, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.println("Started");

  // Tell the reader the transmitter is ready.
  digitalWrite(PIN_COM, HIGH);

}

void loop() {

  // Listen for the lcd reader output.
  while (Serial1.available()) {
    byte c = Serial1.read();

    // Transmit only once. The reader will then cut the power.
    if (tx == 0) {
      // The weight reading starts with #
      if (c == '#') {
        // Grab the weight
        int weight = Serial1.parseInt();
        tx = 1;
        Serial.println(weight);
        transmit(weight);
  
        // Tell the reader the transmitter is finished.
        digitalWrite(PIN_COM, LOW);
      }
    }

    // Passthru the rest of the data.
    Serial.write(c);
  }

}

void transmit(int weight) {

    // Read the battery voltage.
    int battery = battery_mv();
    Serial.print("Batt: ");
    Serial.println(battery);

    // Connect to wifi.
    wifiMulti.addAP(WIFI_SID, WIFI_PASSWORD);
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;
        char url[100];
        snprintf(url, 100, "http://192.168.0.22/bathroom_scales.php?w=%d&b=%d", weight, battery);
        //String url = String("http://192.168.0.22/bathroom_scales.php?w=" + weight );
        //url = url +  String("b=" + battery_mv);
        
        http.begin(url); 

        // start connection and send HTTP header
        int httpCode = http.GET();
        // httpCode will be negative on error
        if (httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if (httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }

}

int battery_mv() {
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

