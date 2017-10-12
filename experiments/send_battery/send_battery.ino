/**
 * Basic Http client with deep sleep
 */

#include <Arduino.h>

#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include "soc/rtc.h"
#include "credentials.h"

WiFiMulti wifiMulti;

#define uS_TO_S_FACTOR 1000000  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  60        /* Time ESP32 will go to sleep (in seconds) */


void setup() {
    // Slow down the cpu for use with the hx711 library
    rtc_clk_cpu_freq_set(RTC_CPU_FREQ_80M);
    
    Serial.begin(115200);
    Serial.println();
    
    

    // Perform everything needed while awake.
    awake();

    // Get ready to sleep
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    // Now sleep
    Serial.print("Awake for: "); Serial.println(millis());
    esp_deep_sleep_start();

}

void loop() {
  // This is not going to be called
}

void awake() {

    // Read the battery voltage.
    int battery = battery_mv();
    Serial.print("Batt: ");
    Serial.println(battery);

    int weight = 99;

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


