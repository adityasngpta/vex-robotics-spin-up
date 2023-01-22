/*----------------------------------------------------------------------------
 *
 * Copyright (C) 2022 VEX Team 3583A - All Rights Reserved
 * Any other team can NOT use, distribute, or modify this code 
 * as per the terms of VEX honor code.
 *
 *---------------------------------------------------------------------------*/
 

using namespace vex;

extern brain Brain;

extern distance dsensor;

extern motor frontMotorA;
extern motor frontMotorB;
extern motor backMotorA;
extern motor backMotorB;

extern motor intake;
extern motor flywheel1;
extern motor flywheel2;
extern motor_group Flywheel;

extern motor indexer;

extern smartdrive driveTrain;
extern inertial isensor;

extern encoder encLeft;
extern encoder encRight;

extern pneumatics endgame;

extern controller Controller1;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );