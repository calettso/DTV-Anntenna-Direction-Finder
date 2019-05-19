/*
 File/Sketch Name: DTV-Antenna-Direction-Finder

 Version No.: v1.0 Created 14 April, 2019
 
 Original Author: Clyde A. Lettsome, PhD, PE, MEM
 
 Description:  This code/sketch makes DTV transmitter antenna finding easy. This code drives a bipolar stepper motor to point a DTV antenna towards a DTV transmitter antenna
 locations based on a premade channel list.  A list of channels in the United States and corresponding angles relative to your location can be found on a number of sites 
 such as AntennaWeb and the on the FCC website.
 
 The stepper motor that turns the antenna is connected to the Arduino/Genuino board via a A4988 motor driver that is connected to pins 3-5 of the Arduino/Genuin. Communication 
 with the Arduino can be done via an HM-10 Bluetooth board. A Bluetooth Termainal application will be needed to communicate with the HM-10 Bluetooth board. When a 0 is entered at 
 the Bluetooth Terminal app's prompt, the Arduino/Genuino decrement through the list of channels in the myChannelNum[] array. When a 1 is entered in the Bluetooth Terminal  
 app's prompt, the Arduino/Genuino increment through channels listed in the same array via. Based on the channel selected from the list, the motor will turn your antenna to 
 the corresponding angle in the myChannelDegAngle[] array.


 License: This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License (GPL) version 3, or any later
 version of your choice, as published by the Free Software Foundation.

 Notes: Copyright (c) 2019 by C. A. Lettsome Services, LLC
 For more information visit https://clydelettsome.com/blog/2019/05/14/motorized-digital-tv-antenna-mount-aka-digital-tv-antenna-pointer/

 */

const int stepPin = 3;
const int dirPin = 4;
const int enablePin = 5; 

int revolutionStepCount = 0;         // number of steps the motor has taken in the current revolution
int myChannelNum[] = {0};  // Enter channel numbers here. This is the channel number array. Note: 0 indicates the home beginning position and added channels should be done as shown. Ex. {0,2,4,5, ....}
int myChannelDegAngle[] = {0};  //Enter channel's angle degrees here. This is the channel degree angle array. Note: 0 degree is due North and added angles should be done as shown. Ex. {0,52,144,59, ....}
int myChannelStepNum[] = {0}; //Array should contain a list of the number of steps necessary for the stepper motor to get to the angle corresponding to the angle in the myChannelDegAngle[] array.
int numberOfSteps = 0;
int arrayLength = (sizeof(myChannelStepNum) / sizeof(myChannelStepNum[0])); //Find the number of channels in myChannelNum[] array.
char Incoming_value=0;
int channelIndex = 0;  //Start at beginning angle position (0 degrees or North)and home channel (channel 0)

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
  if(Serial.available() > 0)  
  {
    Incoming_value = Serial.read();      //Read the incoming data and store it into variable Incoming_value

    if(Incoming_value == '1')            //Checks whether value of Incoming_value is equal to 1 
      channelIndex++;  //increment in the selection
    else if(Incoming_value == '0')       //Checks whether value of Incoming_value is equal to 0
      channelIndex--;   //decrease in channel selection

    //wrap around the channel numbers if at the beginning or end of the array
    if(channelIndex>arrayLength-1)
      channelIndex=0;
    else if(channelIndex<0)
      channelIndex=(arrayLength-1);  
  
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

    //print channel, degrees and step number to screen
    Serial.print("channel, degrees, step: ");
    Serial.print(myChannelNum[channelIndex]);
    Serial.print(", ");
    Serial.print(myChannelDegAngle[channelIndex]);
    Serial.print(", ");
    Serial.println(revolutionStepCount);
  }
}
