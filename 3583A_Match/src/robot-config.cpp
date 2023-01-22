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

// VEXcode device constructors
motor frontMotorA = motor(PORT9, ratio6_1, true);   //FrontLeft
motor frontMotorB = motor(PORT1, ratio6_1, false); //FrontRight 

motor backMotorA = motor(PORT10, ratio6_1, true); //BackLeft
motor backMotorB = motor(PORT2, ratio6_1, false); //BackRight

// motor groups
motor_group leftDrive = motor_group(frontMotorA, backMotorA);
motor_group rightDrive = motor_group(frontMotorB, backMotorB);

inertial isensor =  inertial(PORT4);
smartdrive driveTrain = smartdrive(leftDrive, rightDrive, isensor, 12.566367061, /*trackWidth*/ 14.5, /*wheelBase*/ 13.5, distanceUnits::in, 1);

encoder encLeft = encoder(Brain.ThreeWirePort.G); // and H
encoder encRight = encoder(Brain.ThreeWirePort.A); // and B


// disc intaker
motor intake = motor(PORT3, ratio18_1, false); 

// disk shooter motors
motor flywheel1 = motor(PORT11, ratio6_1, true); 
motor flywheel2 = motor(PORT12, ratio6_1, false); 

// four bar motor
motor indexer = motor(PORT20, ratio36_1, false);

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


