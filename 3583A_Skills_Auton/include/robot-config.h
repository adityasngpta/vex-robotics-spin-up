/*----------------------------------------------------------------------------
 *
 * Copyright (C) 2022 VEX Team 3583A - All Rights Reserved
 * Any other team can NOT use, distribute, or modify this code 
 * as per the terms of VEX honor code.
 *
 *---------------------------------------------------------------------------*/
 

using namespace vex;

extern brain Brain;

extern motor leftDriveA;
extern motor leftDriveB; 
extern motor leftDriveC;
extern motor rightDriveA;
extern motor rightDriveB;
extern motor rightDriveC;

extern motor intake;
extern motor cata;

extern smartdrive driveTrain;
extern inertial isensor;

extern encoder encLeft;
extern encoder encRight;

extern distance dsensor;

extern pneumatics endgame;

extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );