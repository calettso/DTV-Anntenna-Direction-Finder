/*

 File/Sketch Name: Stepper-test-quarter-turns-part2

 Current Version No.: v1.1 Modified 14 May 2019
 Original Version No.: v1.0 Created 24 February, 2019
 
 Original Author: Clyde A. Lettsome, PhD, PE, MEM
 
 Description: Turn stepper motor clockwise in quarter turns (or 90 degrees).

 License: This program is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License (GPL) version 3, or any later
 version of your choice, as published by the Free Software Foundation.

 Notes: Copyright (c) 2019 by C. A. Lettsome Services, LLC
 For more information visit https://clydelettsome.com/blog/2019/05/14/motorized-digital-tv-antenna-mount-aka-digital-tv-antenna-pointer/

*/

#include <Stepper.h>

const int stepsPerRevolution = 400;  // change this to fit the number of steps per revolution
// for your motor
const int numberOfSteps = stepsPerRevolution/4; //number of steps per turn


// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

void setup() {
  // set the speed at 60 rpm:
  myStepper.setSpeed(60);

}

void loop() {

  myStepper.step(numberOfSteps); //rotate 90 degree.
  delay(500);

  myStepper.step(numberOfSteps); //rotate 90 degree.
  delay(500);

  myStepper.step(numberOfSteps); //rotate 90 degree.
  delay(500);

  myStepper.step(numberOfSteps); //rotate 90 degree.
  delay(500);

}
