/*
 File/Sketch Name: precision-step-test-A4988-driver-part4

 Original Version No.: v1.0 Created 24 March, 2019
 
 Original Author: Clyde A. Lettsome, PhD, PE, MEM
 
 Description:  This code/sketch drives a bipolar stepper motor. The motor is connected to the Arduino board via a A4988 motor driver that is connected 
 to pins 3-5 of the Arduino.

 The motor will pause a given number of times per one revolution. The number of steps between pauses will be evenly distributed. The motor will then 
 turn the opposite direction and make the same number of pauses per one revolution . You can use this to
 test that you are capable of making a precise number of steps using your Arduino.

 License: This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License (GPL) version 3, or any later
 version of your choice, as published by the Free Software Foundation.

 Notes: Copyright (c) 2019 by C. A. Lettsome Services, LLC
 For more information visit https://clydelettsome.com/blog/2019/05/14/motorized-digital-tv-antenna-mount-aka-digital-tv-antenna-pointer/

 */

const int stepsPerRevolution = 400;  // change this to fit the number of steps per revolution for your motor
const int pausesPerRevolution = 4;
const int stepsBetweenPauses = stepsPerRevolution/pausesPerRevolution; //number of steps between pauses
const int stepPin = 3;
const int dirPin = 4;
const int enablePin = 5; 

int revolutionStepCount = 0;         // number of steps the motor has taken in the current revolution

void setup() 
{
  // Set pin modes
  pinMode (stepPin, OUTPUT); 
  pinMode (dirPin, OUTPUT);
  pinMode (enablePin, OUTPUT);

  digitalWrite(enablePin, LOW); //Enable is active low
  Serial.begin(9600); // initialize the serial port:
}

void loop() 
{ 
  digitalWrite(dirPin,HIGH); //turn clockwise
  //make pauses per revolution
  for (int pauseNumber = 0; pauseNumber < pausesPerRevolution; pauseNumber++)
  {
    //steps between pauses
    for(int steps = 0; steps < stepsBetweenPauses; steps++)
    {
      //create pulse to turn motor on step at a time
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(10000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(10000);
  
      //print step number to screen
      Serial.print("steps:");
      Serial.println(revolutionStepCount);
      
      revolutionStepCount++; //increment the step counter
    }
    delay(1000);  //pause for 1 second
  }
  
  digitalWrite(dirPin,LOW); //turn counter-clockwise
  //make pauses per revolution
  for (int pauseNumber = 0; pauseNumber < pausesPerRevolution; pauseNumber++)
  {
    //steps between pauses
    for(int steps = 0; steps < stepsBetweenPauses; steps++)
    {
      //create pulse to turn motor on step at a time
      digitalWrite(stepPin,HIGH);
      delayMicroseconds(10000);
      digitalWrite(stepPin, LOW);
      delayMicroseconds(10000);
    
      //print step number to screen
      Serial.print("steps:");
      Serial.println(revolutionStepCount);
      revolutionStepCount--; //decrement the step counter
    }
    delay(1000); //pause for 1 second
  }
}
