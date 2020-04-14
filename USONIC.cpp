//****************************************************************
// This class is used to get data from the ultrasonic sensors.
//****************************************************************
#include "Arduino.h"
#include "USONIC.h"
#include <stdio.h>

//**********************************
// set the pins for the ultrasonics
//**********************************
////front left UltraSonic
//const int FL_trig = 14;
//const int FL_echo = 12;
////front right UltraSonic
//const int FR_trig = 15;
//const int FR_echo = 2;
////rear right UltraSonic
//const int RR_trig = 32;
//const int RR_echo = 35;
////rear left UltraSonic
//const int RL_trig = 18;
//const int RL_echo = 19;
// underneath
const int UN_trig = 25;
const int UN_echo = 27;


extern float FL_Sonic = 0;    //front left
extern float FR_Sonic = 0;    //front right
extern float RR_Sonic = 0;    //rear right
extern float RL_Sonic = 0;    //rear left
extern float UN_Sonic = 0;    //under

long FR_duration=0;
long FL_duration=0;
long RR_duration=0;
long RL_duration=0;
long UN_duration = 0;

//**************************************
// setup and initilise the ultrasonics
//**************************************
void Usonic::set_sonics()
{
//  //FRONT RIGHT
//  pinMode(FR_trig,OUTPUT);
//  pinMode(FR_echo,INPUT);
//  //FRONT LEFT
//  pinMode(FL_trig,OUTPUT);
//  pinMode(FL_echo,INPUT);
//  //REAR LEFT
//  pinMode(RL_trig,OUTPUT);
//  pinMode(RL_echo,INPUT);
//  //REAR RIGHT
//  pinMode(RR_trig,OUTPUT);
//  pinMode(RR_echo,INPUT);
  //UNDER
  pinMode(UN_trig, OUTPUT);
  pinMode(UN_echo, INPUT);
}

//***************************************
// get values from ultrasonics
//***************************************
void Usonic::update_sonic_values(){

  
//  // Clears the trigPin
//  digitalWrite(FR_trig, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(FR_trig, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(FR_trig, LOW);
//  FR_duration = pulseIn(FR_echo, HIGH);
//  FR_Sonic = FR_duration*0.034/2;
//
//  delay(50);
//  // Clears the trigPin
//  digitalWrite(FL_trig, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(FL_trig, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(FL_trig, LOW);
//  FL_duration = pulseIn(FL_echo, HIGH);
//  FL_Sonic = FL_duration*0.034/2;
//
//  delay(50);
//  // Clears the trigPin
//  digitalWrite(RL_trig, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(RL_trig, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(RL_trig, LOW);
//  RL_duration = pulseIn(RL_echo, HIGH);
//  RL_Sonic = RL_duration*0.034/2;
//
//  delay(50);
//  // Clears the trigPin
//  digitalWrite(RR_trig, LOW);
//  delayMicroseconds(2);
//  // Sets the trigPin on HIGH state for 10 micro seconds
//  digitalWrite(RR_trig, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(RR_trig, LOW);
//  RR_duration = pulseIn(RR_echo, HIGH);
//  RR_Sonic = RR_duration*0.034/2;
  
  delay(50);
  // Clears the trigPin
  digitalWrite(UN_trig, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(UN_trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(UN_trig, LOW);
  UN_duration = pulseIn(UN_echo, HIGH);
  UN_Sonic = UN_duration*0.034/2;
  UN_Sonic = 1.2345;
}

  
