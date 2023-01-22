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
double turnHeading;
bool timerStarted = false;
double axis4;
double axis2;
int timeElapsed = 0; // ms
int timeLeft;
int minutesLeft;
int secondsLeft;
bool expansionAllowed = false;

// PID Flywheel Variables
bool maintainSpeed = true;
bool ReadyShoot = false;

double kp = 0.125;
double ki = 0.0001;
double kd = 0.05;

double preverror = 0.0;
double error = 0.0;
double totalError = 0.0; // += error
double derivative = 0.0; // = error-preverror
double Power = 0;

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

int FlyPID(double targetspeed){
   //debugging
   int num1 = 0;
   int num2 = 0;
   int diff = 2;
   double prevpreverror = 0.0;

   //actual code
   maintainSpeed = true;
   ReadyShoot = false;
   preverror = 0.0;
   error = 0.0;
   totalError = 0.0; // += error
   derivative = 0.0; // = error-preverror
   double Power = 0;
   while(maintainSpeed){
     for (int i = 0; i<5; i++) {
       error = targetspeed - Flywheel.velocity(rpm);
       if (fabs(error) <= 15){
         ReadyShoot = true;
       }
       else{
         ReadyShoot = false;
         Power += (error*kp + totalError*ki + (error - preverror)*kd)/50;
         prevpreverror = preverror;
         preverror = error;
         totalError += error;
         if (Power>12.0) {
           Power=12.0;
         } else if (Power<0) {
           Power=0;
         }

       }
       Flywheel.spin(forward, Power, volt);
       vex::task::sleep(20);

       if (totalError>=7500) {
         totalError=0;
       }
     }
     //printing graph
     Controller1.Screen.newLine();
     Controller1.Screen.print(error);
     num1 += diff;
     num2 = num1+diff;
     Brain.Screen.drawLine(num1, 120+preverror, num2, 120+error);
     Brain.Screen.drawLine(num1, 120+prevpreverror, num2, 120+preverror);
     if (num1 >= 476) {
       Brain.Screen.clearScreen();
       num1 = 0;
       num2 = 0;
     }

   }
   return 1;
   Controller1.Screen.print(ReadyShoot);
 }


void ButtonA_pressed() {

   FlyPID(500); ////////////////////////////// Change Flywheel Speed Here

   Flywheel.stop();
 }

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

void intakeStart()
{
  intake.spin(directionType::fwd, 100, velocityUnits::pct);
}

void outtakeStart()
{
  intake.spin(directionType::rev, 100, velocityUnits::pct);
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

void stopFlywheel()
{
  maintainSpeed = false;
  flywheel1.stop(brakeType::coast);
  flywheel2.stop(brakeType::coast);
}


// Indexer Functions

void pushDisc()
{
  indexerMoving = true;
  indexer.spinTo(70, rotationUnits::deg, 100, velocityUnits::pct, true);
  wait(60, timeUnits::msec);
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

// Calibration and Starting Functions

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
  maintainSpeed = false;

  prerequisites();

  driveTrain.setStopping(brakeType::coast);

  setup();

  while (true) 
  {
    axis4 = Controller1.Axis4.value();
    axis2 = Controller1.Axis2.value();

    // Turn
    frontMotorA.spin(directionType::fwd, axis4, percentUnits::pct);
    backMotorA.spin(directionType::fwd, axis4, percentUnits::pct);

    frontMotorB.spin(directionType::rev, axis4, percentUnits::pct);
    backMotorB.spin(directionType::rev, axis4, percentUnits::pct);

    // Forward
    frontMotorA.spin(directionType::fwd, axis2, percentUnits::pct);
    backMotorA.spin(directionType::fwd, axis2, percentUnits::pct);

    frontMotorB.spin(directionType::fwd, axis2, percentUnits::pct);
    backMotorB.spin(directionType::fwd, axis2, percentUnits::pct);

    if( ((axis4 != 0) || (axis2 != 0)) && (!timerStarted) )
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
  Controller1.ButtonA.pressed(ButtonA_pressed);
  Controller1.ButtonB.pressed(stopFlywheel);

  Controller1.ButtonY.pressed(expand);

  // Endgame Expansion
  if(expansionAllowed || skills)
  {
  Controller1.ButtonUp.pressed(expand);
  Controller1.ButtonDown.pressed(setup);
  Brain.Screen.setCursor(10,1);
  Brain.Screen.print("EXPANSION ALLOWED");
  }

  vex::task::sleep(10);

  // Expansion Timer Loop
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