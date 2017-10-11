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
    
    wifiMulti.addAP(WIFI_SID, WIFI_PASSWORD);

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

    esp_sleep_wakeup_cause_t wakeup_reason;

    wakeup_reason = esp_sleep_get_wakeup_cause();
  
    switch(wakeup_reason) {
      case 1  : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
      case 2  : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
      case 3  : Serial.println("Wakeup caused by timer"); break;
      case 4  : Serial.println("Wakeup caused by touchpad"); break;
      case 5  : Serial.println("Wakeup caused by ULP program"); break;
      default : Serial.println("Wakeup was not caused by deep sleep"); break;
    }
  
    // wait for WiFi connection
    if((wifiMulti.run() == WL_CONNECTED)) {

        HTTPClient http;
        http.begin("http://192.168.0.22/bathroom_scales.php?w=99&b=1234"); 
        Serial.print("[HTTP] GET...\n");
        
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

