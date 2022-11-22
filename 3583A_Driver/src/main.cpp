/*----------------------------------------------------------------------------
 *
 * Copyright (C) 2022 VEX Team 3583A - All Rights Reserved
 * Any other team can NOT use, distribute, or modify this code 
 * as per the terms of VEX honor code.
 *
 *---------------------------------------------------------------------------*/

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

bool skills = true;

const double pi = acos(-1.0);
// 3.141592654

// Motor Temperature Variables
double FL_t;
double I_t;
double F1_t;
double F2_t;

// Driver Variables 
bool indexerMoving = false;
bool notTurning = true;
double turnHeading;
bool timerStarted = false;
double axis3;
double axis2;
int timeElapsed = 0; // ms
int timeLeft;
int minutesLeft;
int secondsLeft;
bool expansionAllowed = false;

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/


// Basic Drive Functions

void forward1(double dist, double speed=62.5, bool comp = true)
{
  driveTrain.driveFor(directionType::fwd, dist, distanceUnits::in, speed, velocityUnits::pct, false);
}

void backward1(double dist, double speed=62.5, bool comp = true)
{
  driveTrain.driveFor(directionType::rev, dist, distanceUnits::in, speed, velocityUnits::pct, comp);
}


// Intake Functions

void intakeStart(double speed = 200)
{
  intake.spin(directionType::fwd, speed, velocityUnits::pct);
}

void outtakeStart(double speed = 200)
{
  intake.spin(directionType::rev, speed, velocityUnits::pct);
}

void intakeStop()
{
  intake.stop(brakeType::brake);
}


// Flywheel Functions

void spinFlywheel(double speed = 100)
{
  flywheel1.spin(directionType::fwd, speed, velocityUnits::pct);
  flywheel2.spin(directionType::fwd, speed, velocityUnits::pct);
}

void spinFlywheelDriver()
{
  flywheel1.spin(directionType::fwd, 72.5, velocityUnits::pct);
  flywheel2.spin(directionType::fwd, 72.5, velocityUnits::pct);
}

void stopFlywheel()
{
  flywheel1.stop(brakeType::coast);
  flywheel2.stop(brakeType::coast);
}


// Indexer Functions

void pushDisc()
{
  indexerMoving = true;
  indexer.spinTo(60, rotationUnits::deg, 100, velocityUnits::pct, true);
  wait(0, timeUnits::msec);
  indexer.spinTo(-5, rotationUnits::deg, 100, velocityUnits::pct, true);
  indexerMoving = false;
}

// Endgame

void expand()
{
  endgame.open();
}

void setup()
{
  endgame.close();
}


void turnToHeading(double angle, double speed=10)
{
  driveTrain.turnToHeading(angle, rotationUnits::deg, speed, velocityUnits::pct, true);
}

///////////////////////////////////////////////////////////////////////////

void prerequisites()
{
frontMotorA.resetRotation();
frontMotorB.resetRotation();
backMotorA.resetRotation();
backMotorB.resetRotation();

intake.resetRotation();
flywheel1.resetRotation();
flywheel2.resetRotation();
indexer.resetRotation();

encLeft.resetRotation();
encRight.resetRotation();

driveTrain.setStopping(brakeType::brake);

intake.setStopping(brakeType::coast);
indexer.setStopping(brakeType::hold);
flywheel1.setStopping(brakeType::coast);
flywheel2.setStopping(brakeType::coast);
}

void autonomous()
{
  prerequisites();
  isensor.setHeading(180, deg);

  // Roller + 2 Low Discs
  /*
  spinFlywheel(50);
  turnToHeading(195, 50);
  outtakeStart();
  forward1(5.5);
  wait(0.15, sec);
  backward1(5);
  pushDisc();
  wait(0.25, sec);
  pushDisc();
  wait(0.25, sec);
  pushDisc();
  stopFlywheel();
  */

  forward1(24);
  turnToHeading(270, 50);
  outtakeStart();
  forward1(10);
  wait(0.3, sec);
  backward1(7);
  intakeStop(); 
  turnToHeading(44, 50);
  intakeStart();
  forward1(28);

  // spinFlywheel(50);
  // turnToHeading(0, 50);
  // pushDisc();

  // turnToHeading(44, 50);
  // forward1(12);

  // intakeStop();
  // stopFlywheel();
}

void reset(motor &m)
{
  m.resetPosition();
  m.resetRotation();
}  

void initMotors(void)
{
  reset(frontMotorA);
  reset(frontMotorB);
  reset(backMotorA);
  reset(backMotorB);

  reset(intake);
  reset(flywheel1);
  reset(flywheel2);
  reset(indexer);
}

void usercontrol(void) 
{ 
  prerequisites();

  driveTrain.setStopping(brakeType::coast);

  setup();

  while (true) 
  {
    if(notTurning)
    {
    
    axis3 = Controller1.Axis3.value();
    axis2 = Controller1.Axis2.value();

    // Left Drive
    frontMotorA.spin(directionType::fwd, axis3, percentUnits::pct);
    backMotorA.spin(directionType::fwd, axis3, percentUnits::pct);

    // Right Drive
    frontMotorB.spin(directionType::fwd, axis2, percentUnits::pct);
    backMotorB.spin(directionType::fwd, axis2, percentUnits::pct);
    }

    if( ((axis3 != 0) || (axis2 != 0)) && (!timerStarted) )
    {
      timerStarted = true;
    }

    // Intakes
    if (Controller1.ButtonL1.pressing())
    {
      intakeStart();
    }
    else if (Controller1.ButtonL2.pressing()) 
    {
      outtakeStart();
    }
    else 
    {
      intakeStop();
    }


    // Indexer
    Controller1.ButtonX.pressed(pushDisc);

    if (Controller1.ButtonR1.pressing()) 
    {
        indexer.spin(forward);
    } 
    else if (Controller1.ButtonR2.pressing()) 
    {
        indexer.spin(reverse);
    } 
    else if (!indexerMoving) 
    {
        indexer.stop();
    }

  // Flywheel
  Controller1.ButtonA.pressed(spinFlywheelDriver);
  Controller1.ButtonB.pressed(stopFlywheel);

  // Endgame Expansion
  if(expansionAllowed || skills)
  {
  Controller1.ButtonUp.pressed(expand);
  Controller1.ButtonDown.pressed(setup);
  Brain.Screen.setCursor(10,1);
  Brain.Screen.print("EXPANSION ALLOWED");
  }

  vex::task::sleep(10);

  if(timerStarted && !skills)
  {
    timeElapsed += 10;
    timeLeft = 105 - (timeElapsed/1000);
    minutesLeft = (timeLeft/60 - (timeLeft % 60)/60);
    secondsLeft = (timeLeft % 60);

    if(minutesLeft == 0 && secondsLeft <= 12)
    {
      expansionAllowed = true; 
    }

    Brain.Screen.setCursor(9,1);
    Brain.Screen.print("Time Left = %d : %d", minutesLeft, secondsLeft);
  }
  
  }
}

void pre_auton()
{
  isensor.resetHeading();
  initMotors();
  endgame.close();
}



// Main will set up the competition functions and callbacks.

int main() {
  // init
  vexcodeInit(); 
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}