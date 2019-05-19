/*
 File/Sketch Name: channel-stepper-testV1-0-part4

 Original Version No.: v1.0 Created 24 March, 2019
 
 Original Author: Clyde A. Lettsome, PhD, PE, MEM
 
 Description:  This code/sketch drives a bipolar stepper motor. The motor is connected to the Arduino board via a A4988 motor driver that is connected 
 to pins 3-5 of the Arduino.

 The Arduino/Genuino will propagate continuously through the channel numbers in the myChannelNum[] array to point your motor to match the angle in the myChannelDegAngle[] array. 
 A list of channels in the United States and corresponding angle relative to your location can be found on a number of sites such as AntennaWeb and the on the FCC website.

 License: This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License (GPL) version 3, or any later
 version of your choice, as published by the Free Software Foundation.

 Notes: Copyright (c) 2019 by C. A. Lettsome Services, LLC
 For more information visit https://clydelettsome.com/blog/2019/05/14/motorized-digital-tv-antenna-mount-aka-digital-tv-antenna-pointer/

 */

const int stepPin = 3;
const int dirPin = 4;
const int enablePin = 5; 

int revolutionStepCount = 0;         // number of steps the motor has taken in the current revolution
int myChannelStepNum[] = {291,0,343,92,270,267,270,374,270,351,350,350,351,272,351,351,351,270,270,291,351,351,351,351,293,379,351,351};  //Place your chennel step numbers in this array
int myChannelDegAngle[] = {262,0,309,83,243,240,243,337,243,316,315,315,316,245,316,316,316,243,243,262,316,316,316,316,264,341,316,316};  //Place your chennel angle numbers in this array
int myChannelNum[] = {2,4,5,8,9,11,12,14,16,17,21,26,28,30,32,34,36,38,40,42,45,46,49,51,53,57,63,69};  //Place your chennel numbers in this array
int numberOfSteps = 0;
int arrayLength = (sizeof(myChannelStepNum)/sizeof(myChannelStepNum[0]));

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
  
  //progress through angles in vector
  for (int channelIndex = 0; channelIndex < arrayLength; channelIndex++)
  {
      if(myChannelStepNum[channelIndex] < revolutionStepCount)
      {
        digitalWrite(dirPin,LOW); //turn counter-clockwise
        
        numberOfSteps = revolutionStepCount - myChannelStepNum[channelIndex]; //find number of step moves required
        
        //turn antenna to new location
        for(int steps = 0; steps < numberOfSteps; steps++)
        {
          //create pulse to turn motor one step at a time
          digitalWrite(stepPin,HIGH);
          delayMicroseconds(10000);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(10000);
          
          revolutionStepCount--; //increment the step counter
        }
      }
      else
      {
        digitalWrite(dirPin,HIGH); //turn clockwise
        
        numberOfSteps = myChannelStepNum[channelIndex] - revolutionStepCount; //find number of step moves required
        
        //turn antenna to new location
        for(int steps = 0; steps < numberOfSteps; steps++)
        {
          //create pulse to turn motor one step at a time
          digitalWrite(stepPin,HIGH);
          delayMicroseconds(10000);
          digitalWrite(stepPin, LOW);
          delayMicroseconds(10000);
          
          revolutionStepCount++; //increment the step counter
        }
      }

    //print chennel, degrees and step number to screen
    Serial.print("channel, degrees, step: ");
    Serial.print(myChannelNum[channelIndex]);
    Serial.print(", ");
    Serial.print(myChannelDegAngle[channelIndex]);
    Serial.print(", ");
    Serial.println(revolutionStepCount);
    
    delay(3000);  //pause for 3 second
  }
}
