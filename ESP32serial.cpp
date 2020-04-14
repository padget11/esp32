#include "Arduino.h"
#include "ESP32Serial.h"
#include <stdio.h>
#include <HardwareSerial.h>
#include "USONIC.h"
#include <WiFi.h>
#include <HTTPClient.h>
#include "Wifi_client.h"

#define RXD2 16
#define TXD2 17

HardwareSerial MySerial(2);
Usonic sonic = Usonic();
Wifi_client wifi = Wifi_client();

const char* ssid = "ESP32-Access-Point";
const char* password = "123456789";

//Your IP address or domain name with URL path
const char* serverTest = "http://192.168.4.1/result";

char fullStringCharArray[70];         //char arrays for receiving and manipulating the data from serial
char *received_data_array[12];
char received_data[60];
char receivedMsg[20];
char* element;
char hint = 'S';                     //hint from Arduino Uno to send the finalString variable
char hint_received;

//*******************************************************
//external variables which get values from 'USONIC.cpp'
//*******************************************************
extern float FL_Sonic;      //front left ultrasonic
extern float FR_Sonic;      //front right ultrasonic
extern float RR_Sonic;      //rear right ultrasonic
extern float RL_Sonic;      //rear left ultrasonic
extern float UN_Sonic;

String sUS1 = "";
String sUS2 = "";
String sUS3 = "";
String sUS4 = "";
String sUS5 = "";
String sLong  = "";
String sLat = "";
String test;

String myGpsData;                     //my gps coordinates as string
float other_longtitude = 3.4565;      //variables to keep the latitude and longtitude from the myGpsData.     
float other_lattitude = 51.4565;      //Trial values.

extern String otherGpsData;           //gets the value from the BLE_client.cpp

int bufferSize = 0;
String finalString = "";             //string to be send to serial which contains the values from ultrasonics and the other drones gps coordnidates

void ESP32Serial::serial_setup()
{
  Serial.begin(115200);
  Serial.println("setup");
  MySerial.begin(9600, SERIAL_8N1, RXD2, TXD2);
  WiFi.begin(ssid, password);
  wifi.setup_WIFI_client();
}

//********************************************************************************************
// Function which sends the ultrasonic values and the gps coordinates of 
// the other drone through serial to Arduino Uno. 
// It also receives the gps coordinate of its drone through the serial from the Arduino Uno
//********************************************************************************************
String ESP32Serial::send_and_receive_values()
{
  sonic.update_sonic_values();          //get ultrasonic values

  // Check WiFi connection status
  if(WiFi.status()== WL_CONNECTED )
  { 
    //unsigned long start_millis = millis();
    test = wifi.httpGETRequest(serverTest);
    //unsigned long stop_millis = millis();
    //unsigned long time_millis = stop_millis - start_millis;
    //Serial.println(time_millis);
    Serial.println(test);
    // save the last HTTP GET Request
    //previousMillis = currentMillis;
  }
  else 
  {
    Serial.println("WiFi Disconnected");
  }

  char f[20];
  strcpy(f, test.c_str());
  char* element = strtok(f, ", ");
  float theta = atof(element);
  String sTheta = String(theta, 1);
  element = strtok(NULL, ", ");
  String sOffset = element;

  delay(10);
  
  
  sUS1 = String(FL_Sonic,1);            //convert ultrasonic float values to string
  sUS2 = String(FR_Sonic,1);
  sUS3 = String(RR_Sonic,1);
  sUS4 = String(RL_Sonic,1);
  sUS5 = String(UN_Sonic,1);
  sLong =  String(other_longtitude,4); //convert coordinates to string
  sLat =   String(other_lattitude,4);

  //String sTheta = String(theta, 2);
  //String sOffset = String(offset);
  Serial.println(sTheta);
  Serial.println(sOffset);
  
  Serial.println("send and receive");
  if(MySerial.available()>0)
  {           //check if the serial buffer has data
      delay(10);
      Serial.println("data available");
      bufferSize = MySerial.available();
      //Serial.println(bufferSize);
      hint_received = Serial.peek();
      //Serial.println(hint_received);
      MySerial.readBytes(receivedMsg,bufferSize);
      delay(10);
      //Serial.println(receivedMsg);
      delay(10);
      if (receivedMsg[0] == hint){    //check if we received the hint ("S") from arduino UNO    
          //Serial.println("into send");
          put_string_to_array(receivedMsg);
          finalString = String("m a "+sUS1+" b "+sUS2+" c "+sUS3+" d "+sUS4+" e "+sLong+" f "+sLat+" g "+sUS5+" h "+sTheta+" i "+sOffset); //set the full string 
          //convert the full string to char array
          finalString.toCharArray(fullStringCharArray, 65); // 55
          //send the char array to serial
          delay(10);
          Serial.println(fullStringCharArray);
          MySerial.write(fullStringCharArray);
      }

  }
  return receivedMsg;
}

//*************************************
// function to convert float to string
//*************************************
//String ESP32Serial::floatToString(float var){
//  String valueAsString;
//  char value[10];
//  gcvt(var, 6, value);
//  valueAsString = String(value);
//  return valueAsString;
//}

void ESP32Serial::put_string_to_array(char string_array[]){
  
   element = strtok(string_array,",");            //split string into string array with delimiter " "
   received_data_array[0] = element;              //first element
   for(int i=1;i<3;i++){                          //all the othe elements
        element = strtok(NULL,",");
        received_data_array[i]=element;      
    }
    myGpsData = String(received_data_array[1])+","+String(received_data_array[2]); //set the string of my coordinates
    Serial.println(received_data_array[1]);
}
