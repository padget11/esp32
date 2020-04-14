#include <WiFi.h>
#include <HTTPClient.h>
#include "Wifi_client.h"
#include "Arduino.h"
#include <stdio.h>
#include "ESP32serial.h"
#include "USONIC.h"


Usonic sonic_ = Usonic();
ESP32Serial espSerial = ESP32Serial();

unsigned long previousMillis = 0;
const long interval = 1000; 

void setup()
{
  Serial.begin(115200);
  espSerial.serial_setup();
  sonic_.set_sonics();
}

void loop()
{
  espSerial.send_and_receive_values();
  delay(1000);
  
}
