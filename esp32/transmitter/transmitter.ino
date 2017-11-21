/**
 * Takes serial input and sends rthe weight to a server
 */

#include <WiFi.h>
#include "credentials.h"

#define PIN_COM  GPIO_NUM_21 // for basic communication with the lcd reader.


HardwareSerial Serial1(2);

byte c = 0;
byte tx = 0;
int weight = 0;
const char* host = "192.168.0.22";

unsigned long previousMillis = 0; 
const long timeout = 10000; 

byte rx_state = 0;
byte weight_byte_high = 0;
byte weight_byte_low = 0;

void setup() {

    
  // Main usb serial for debug.
  Serial.begin(115200);
  
  

  delay(10);

  pinMode(PIN_COM, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  WiFi.begin(WIFI_SID, WIFI_PASSWORD);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

  // Listen to the lcd reader.
  Serial1.begin(9600);
  
  Serial.println("Started on:");
  Serial.println(WiFi.localIP());

  // Tell the reader the transmitter is ready.
  digitalWrite(PIN_COM, LOW);

}

void loop() {

  // Listen for the lcd reader output.
  if (Serial1.available()) {
    byte c = Serial1.read();
    
    // Passthru.
    Serial.print(c);


    switch (rx_state) {
      case 0:
        if (c == '#') {
          rx_state = 1;
          weight = 0;
          
        }
        break;
      case 1:
        weight_byte_high = c;
        weight_byte_low = 0;
        rx_state = 2;
        break;
      case 2:
        weight_byte_low = c;
        weight = (weight_byte_high << 8) | weight_byte_low;
        //
        tx = 1;
        Serial.println(weight);
        //
        transmit(weight);
  
        // Tell the reader the transmitter is finished.
        digitalWrite(PIN_COM, HIGH);
        
        rx_state = 0;
        break;
    }
  }

  if (tx == 1) {
     //Serial1.end();
     tx = 0;
     Serial.println("End");
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= timeout) {
    Serial.println("Timeout");
    
    previousMillis = currentMillis;
    // pretend power down
    digitalWrite(PIN_COM, HIGH);
    tx = 0;
    rx_state = 0;

    //Serial1.begin(57600);
    Serial.println("start");
    delay(1000);
    digitalWrite(PIN_COM, LOW);
  }

}

void transmit(int weight) {

    // Read the battery voltage.
    int battery = battery_mv();
    Serial.print("Batt: ");
    Serial.println(battery);

    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    char url[100];
    snprintf(url, 100, "http://192.168.0.22/bathroom_scales.php?w=%d&b=%d", weight, battery);

   
    Serial.println(url);
    
    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }
    Serial.flush();
    client.stop();
//
//    // Read all the lines of the reply from server and print them to Serial
//    while(client.available()) {
//        String line = client.readStringUntil('\r');
//        Serial.print(line);
//    }

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

