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

const double pi = acos(-1.0);
// 3.141592654

const double d = 2.75; // in
// Tracking Wheel Diameter

// Robot Start Position
double init_x = -17.5; //-21;
double init_y = -22; //-20;
double robotAngle;

// Odometry Variables
bool trackingOn = true;

double current_x = 0;
double current_y = 0;
double init_ang = 0;


bool maintainSpeed = true;
   bool ReadyShoot = false;

   double kp = 0.125;
   double ki = 0.0001;
   double kd = 0.05;

   double preverror = 0.0;
   double error = 0.0;
   double totalError = 0.0; // += error
   double derivative = 0.0; // = error-preverror
   //double flyspeed;
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


// Basic Drive Functions

void forwardEnc(double dist, double speed=62.5)
{
  driveTrain.driveFor(directionType::fwd, dist, distanceUnits::in, speed, velocityUnits::pct);
}

void backwardEnc(double dist, double speed=62.5)
{
  driveTrain.driveFor(directionType::rev, dist, distanceUnits::in, speed, velocityUnits::pct);
}


// Intake Functions

void intakeStart(double speed = 200)
{
  intake.spin(directionType::fwd, speed, velocityUnits::pct);
}

void outtakeStart(double speed = 100)
{
  intake.spin(directionType::rev, speed, velocityUnits::pct);
}

void intakeStop()
{
  intake.stop(brakeType::brake);
}


// Cata Functions

void cataDiscs()
{
  // Add Things Here
}


bool encLeftReverse = false; // reverse = true
bool encRightReverse = false; // reverse = true 
bool encBackReverse = false; // reverse = true 

double getRotation(encoder e, rotationUnits units, bool reverse)
{
  double r = e.rotation(units);
  if(reverse)
    r = -r;
  return r;
}


void turnToHeading(double angle, double speed = 75)
{
  driveTrain.turnToHeading(angle, rotationUnits::deg, speed, velocityUnits::pct, true);
}

///////////////////////////////////////////////////////////////////////////

int robotPosition() 
{
  robotAngle = isensor.heading();

  double init_left_dist = getRotation(encLeft, rotationUnits::rev, encLeftReverse)*pi*d;;
  double init_right_dist = getRotation(encRight, rotationUnits::rev, encRightReverse)*pi*d;

  double leftDist, rightDist;
  double deltaLeft, deltaRight, deltaFwd; 


  while(trackingOn)
  {
    robotAngle = isensor.heading();

    leftDist = getRotation(encLeft, rotationUnits::rev, encLeftReverse)*pi*d;
    rightDist = getRotation(encRight, rotationUnits::rev, encLeftReverse)*pi*d;

    deltaLeft = leftDist - init_left_dist;
    deltaRight = rightDist - init_right_dist;

    deltaFwd = (deltaLeft + deltaRight)/2;

    bool caseDone = false;

    ////////// Case 1 - Robot Headed NE

    if(robotAngle >= 0 && robotAngle <= 90)
    {
      double lineAng = robotAngle;

      double delta_x = deltaFwd * sin(lineAng * pi / 180);
      double delta_y = deltaFwd * cos(lineAng * pi / 180);

      current_x = init_x + delta_x;
      current_y = init_y + delta_y;

      caseDone = true;
    }

    ////////// Case 2 - Robot Headed SE

    if(robotAngle >= 180 && robotAngle <= 270 && !caseDone)
    {
      double lineAng = robotAngle - 180;

      double delta_x = deltaFwd * sin(lineAng * pi / 180);
      double delta_y = deltaFwd * cos(lineAng * pi / 180);

      current_x = init_x - delta_x;
      current_y = init_y - delta_y;

      caseDone = true;
    }

    ////////// Case 3 - Robot Headed NW

    if(robotAngle >= 270 && robotAngle <= 360 && !caseDone)
    {
      double lineAng = robotAngle - 270;

      double delta_x = deltaFwd * cos(lineAng * pi / 180);
      double delta_y = deltaFwd * sin(lineAng * pi / 180);

      current_x = init_x - delta_x;
      current_y = init_y + delta_y;
      
      caseDone = true;
    }

     ////////// Case 4 - Robot Headed SW

    if(robotAngle >= 90 && robotAngle <= 180 && !caseDone)
    {
      double lineAng = robotAngle - 90;

      double delta_x = deltaFwd * cos(lineAng * pi / 180);
      double delta_y = deltaFwd * sin(lineAng * pi / 180);

      current_x = init_x + delta_x;
      current_y = init_y - delta_y;

      caseDone = true;
    }

    init_left_dist = leftDist;
    init_right_dist = rightDist;

    init_x = current_x;
    init_y = current_y;

    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("Coordinates: %f, %f", current_x, current_y);
    Brain.Screen.setCursor(2,1);
    Brain.Screen.print("Readings: L = %f,  R = %f", leftDist, rightDist);
    Brain.Screen.setCursor(3,1);
    Brain.Screen.print("Heading: %f", robotAngle);

    vex::task::sleep(10); 
  }

  return(0);
}

///////////////////////////////////////////////////////////////////////////

void driveToCoordinate(double x, double y, double dSpeed = 100, double tSpeed = 75)
{
  double rise = y - current_y;
  double run = x - current_x;

  // Angle of Attack

  double dAng = 0; // Default Case - Robot Headed N
  double lAng = ( atan ( std::abs(rise) / std::abs(run) ) ) * 180 / pi;
  Brain.Screen.clearLine(4,color::black);
  Brain.Screen.setCursor(4,1);

  ////////// Case 1 - Robot Headed NE

    if(rise > 0 && run > 0)
    {
      dAng = 90 - lAng;
     
      Brain.Screen.print("Case 1");
    }

    ////////// Case 2 - Robot Headed SE

    if(rise < 0 && run > 0)
    {
      dAng = 90 + lAng;

      Brain.Screen.print("Case 2");
    }

    ////////// Case 3 - Robot Headed NW

    if(rise > 0 && run < 0)
    {
      dAng = 270 + lAng;

      Brain.Screen.print("Case 3");
    }

    ////////// Case 4 - Robot Headed SW

    if(rise < 0 && run < 0)
    {
      dAng = 270 - lAng;
  
      Brain.Screen.print("Case 4");
    }

  ///////// Case 5 - Robot Headed N or S

    if(run == 0)
    {
      dAng = 0;

      if(rise < 0)
      {
        dAng = 180;
      }

      Brain.Screen.print("Case 5");
    }

   ///////// Case 6 - Robot Headed E or W

    if(rise == 0)
    {
      dAng = 90;

      if(run < 0)
      {
        dAng = 270;
      }

      Brain.Screen.print("Case 6");
    }

  if(dSpeed < 0)
  {
    dAng = dAng - 180;
  }

  turnToHeading(dAng, tSpeed);

  // Distance To Drive

  double c = sqrt(rise * rise + run * run);

  if(dSpeed > 0)
  {
    forwardEnc(c, dSpeed);
  }
  else
  {
  backwardEnc(c, -dSpeed);
  }
}


void forwardDist(double stoppingDist, double speed)
{
  double dist = dsensor.objectDistance(distanceUnits::mm);

  driveTrain.drive(fwd, speed, velocityUnits::pct);

  while(dist > stoppingDist)
  {
    dist = dsensor.objectDistance(distanceUnits::mm);
    
  }

  driveTrain.stop(brakeType::brake);
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

trackingOn = true;
}

void autonomous()
{
  prerequisites();
  isensor.setHeading(270, deg);
  vex::thread t(robotPosition);

// Roller 1

  intakeStart();
  forwardDist(43.5, 50);
  backwardEnc(6, 50);


  // Roller 2
  turnToHeading(70);
  forwardEnc(30, 100);
  turnToHeading(0);
  forwardDist(43.5, 50);
  backwardEnc(6, 50);
  intakeStop();

  // Shoot 3 Discs
  driveToCoordinate(60, 0);
  turnToHeading(88, 100);
  cataDiscs();

  // Intake 3 Discs
  intakeStart();
  driveToCoordinate(25, -22.5);
  driveToCoordinate(52.5, -57.5);

  // Shoot 3 Discs
  driveToCoordinate(105, -55);
  turnToHeading(350);
  intakeStop();
  cataDiscs();

  // Roller 3
  driveToCoordinate(95, -112.5, -100);
  turnToHeading(90, 75);
  intakeStart();
  forwardDist(43.5, 50);
  backwardEnc(5, 50);
  turnToHeading(100);
  backwardEnc(25, 50);
  intakeStop();

  // Roller 4
  turnToHeading(180, 100);
  intakeStart();
  forwardDist(43.5, 50);
  backwardEnc(10, 20);

  // Intake 2 Discs
  driveToCoordinate(37.5, -72.5, 100); // driveToCoordinate(20, -57.5, 100, 100);

  // Shoot 3 Discs
  turnToHeading(237.5, 100);
  cataDiscs();
  //stopFlywheel();

  driveToCoordinate(80, -115, -100);

  // Expansion
  endgame.open();
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
