/*----------------------------------------------------------------------------
 *
 * Copyright (C) 2022 VEX Team 3583A - All Rights Reserved
 * Any other team can NOT use, distribute, or modify this code 
 * as per the terms of VEX honor code.
 *
 *---------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// *** CHECK ALL PORTS AND GEAR RATIOS AND REVERSE FLAGS ***

motor leftDriveA = motor(PORT12, ratio6_1, true);
motor leftDriveB = motor(PORT19, ratio6_1, true);
motor leftDriveC = motor(PORT13, ratio6_1, false);
motor rightDriveA = motor(PORT11, ratio6_1, false);
motor rightDriveB = motor(PORT20, ratio6_1, false);
motor rightDriveC = motor(PORT14, ratio6_1, true);

motor_group leftDrive = motor_group(leftDriveA, leftDriveB, leftDriveC);
motor_group rightDrive = motor_group(rightDriveA, rightDriveB, rightDriveC);

inertial isensor =  inertial(PORT2);

smartdrive driveTrain = smartdrive(leftDrive, rightDrive, isensor, 3.25*acos(-1), 9.5, 10, distanceUnits::in, 2/3);

encoder encLeft = encoder(Brain.ThreeWirePort.G); // and H
encoder encRight = encoder(Brain.ThreeWirePort.A); // and B

distance dsensor = distance(PORT17);

// disc intaker
motor intake = motor(PORT18, ratio6_1, true);

// four bar motor
motor cata = motor(PORT21, ratio18_1, false);

// pneumatic pistons
pneumatics endgame = pneumatics(Brain.ThreeWirePort.C);


controller Controller1 = controller(primary);


// VEXcode generated functions

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...\n");
  Brain.Screen.setCursor(2, 1);
  
  // calibrate the drivetrain gyro
  wait(200, msec);
  // isensor.calibrate();
  // wait for the gyro calibration process to finish
  while (isensor.isCalibrating())
  {
    Brain.Screen.print("Calibrating Inertial Sensor for Drivetrain\n");
    //Controller1.Screen.print("Calibrating Inertial Sensor for Drivetrain\n");
    wait(200, msec);
  }

  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(3,1);
}


