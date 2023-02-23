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


int Brain_precision = 0, Console_precision = 0, Controller1_precision = 0;


bool skills = true;

const double pi = acos(-1.0);
// 3.141592654

// Robot Start Position
double init_x = 6;
double init_y = -9.5;
double robotAngle;


// Odometry Variables
bool trackingOn = true;

double current_x = 0;
double current_y = 0;
double init_ang = 0;

// Motor Temperature Variables
double FL_t;
double I_t;
double F1_t;
double F2_t;

// Controller Print Coodrinates
int xc;
int yc;

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


// "when started" hat block
int whenStarted1() {
  driveTrain.setStopping(coast);
  Flywheel.setStopping(coast);
  Flywheel.setVelocity(200.0, percent);
  intake.setVelocity(200.0, percent);
  indexer.setVelocity(200.0, percent);
  indexer.setStopping(hold);
  Flywheel.setPosition(0.0, degrees);
  driveTrain.setDriveVelocity(200.0, percent);
  endgame.set(false);
  Flywheel.setVelocity(520, rpm);
  Flywheel.spin(forward);
  return 0;
}

void pushDiscs()
{
  indexer.spinFor(50, rotationUnits::deg, 99, velocityUnits::pct, true);
  wait(5, msec);
  indexer.spinFor(-50, rotationUnits::deg, 99, velocityUnits::pct, true);
  wait(5, msec);
  indexer.spinFor(50, rotationUnits::deg, 99, velocityUnits::pct, true);
  wait(5, msec);
  indexer.spinFor(-50, rotationUnits::deg, 99, velocityUnits::pct, true);
  wait(5, msec);
  indexer.spinFor(50, rotationUnits::deg, 99, velocityUnits::pct, true);
  wait(5, msec);
  indexer.spinFor(-50, rotationUnits::deg, 99, velocityUnits::pct, true);
}

//Start running flywheel when button A pressed, start PID
void Driver_pressed() {
  Flywheel.spin(fwd, 80, percentUnits::pct);
}

void Auton_pressed() {
  Flywheel.spin(fwd, 80, percentUnits::pct);
}

//Controller Button B pressed - stops flywheel
void ButtonB_pressed() {
  Flywheel.stop(brakeType::coast);
}

//Fires the expansion
void expansion() {
  while (!Controller1.ButtonDown.pressing()) {
    
  }
  endgame.set(true);

}

//retracts the expansion
void expansion2() {
  while (!Controller1.ButtonLeft.pressing()) {
    
  }
  endgame.set(false);

}

void indexerForward() {


  indexer.spinFor(10, rotationUnits::deg, 100, velocityUnits::pct);

}

void indexerBackward() {

indexer.spinFor(-10, rotationUnits::deg, 100, velocityUnits::pct);

}



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


/*
void ButtonA_pressed() {
   FlyPID(520);

   Flywheel.stop();
 }
 */



// Basic Drive Functions

void forwardEnc(double dist, double speed=62.5, bool comp = true)
{
  driveTrain.driveFor(directionType::fwd, dist, distanceUnits::in, speed, velocityUnits::pct, false);
}

void backwardEnc(double dist, double speed=62.5, bool comp = true)
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

void turnToHeading(double angle, double speed=10)
{
  driveTrain.turnToHeading(angle, rotationUnits::deg, speed, velocityUnits::pct, true);
}


int robotPosition() 
{
  double d = 2.75;

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


    Controller1.Screen.setCursor(1, 2);
    xc = int(round(current_x));
    yc = int(round(current_y));

    Controller1.Screen.print("%d, %d", xc, yc);


    Brain.Screen.setCursor(1,1);
    Brain.Screen.print("Coordinates: %f, %f", current_x, current_y);
    Brain.Screen.setCursor(2,1);
    Brain.Screen.print("Readings: L = %f,  R = %f", leftDist, rightDist);
    Brain.Screen.setCursor(3,1);
    Brain.Screen.print("Heading: %f", robotAngle);

    FL_t = frontMotorA.temperature(temperatureUnits::fahrenheit);
    I_t = intake.temperature(temperatureUnits::fahrenheit);
    F1_t = flywheel1.temperature(temperatureUnits::fahrenheit);
    F2_t = flywheel2.temperature(temperatureUnits::fahrenheit);

    Brain.Screen.setCursor(5,1);
    Brain.Screen.print("Drive Temperatures (F): FL = %f", FL_t);
    Brain.Screen.setCursor(6,1);
    Brain.Screen.print("Intake Temperature (F): I = %f" , I_t);
    Brain.Screen.setCursor(7,1);
    Brain.Screen.print("Fwhl Tmps (F): F1 = %f, F2 = %f", F1_t, F2_t);

    vex::task::sleep(10); 
  }

  return(0);
}

///////////////////////////////////////////////////////////////////////////

void driveToCoordinate(double x, double y, double dSpeed = 50, double tSpeed = 25)
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


  turnToHeading(dAng, tSpeed);

  // Distance To Drive

  double c = sqrt(rise * rise + run * run);

  forwardEnc(c, dSpeed);
}




void driveToCoordinate2(double x, double y, double dSpeed = 75, double tSpeed = 25)
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

  
  dAng = dAng - 180;

  turnToHeading(dAng, tSpeed);

  // Distance To Drive

  double c = sqrt(rise * rise + run * run);

  backwardEnc(c, dSpeed);
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

void autonomous()
{
  prerequisites();
  vex::thread t(robotPosition);

  // Right Side Auton
  ///*
  isensor.setHeading(180, deg);
  forwardEnc(24);
  turnToHeading(270, 50);
  outtakeStart();
  forwardEnc(10);
  wait(0.3, sec);
  backwardEnc(7);
  intakeStop(); 
  turnToHeading(44, 50);
  intakeStart();
  spinFlywheel(50);
  forwardEnc(28);
  turnToHeading(330);
  pushDisc();
  stopFlywheel();
  intakeStop();
  //*/


  // Left Side Auton
  /*
  isensor.setHeading(90, deg);
  vex::thread f(Auton_pressed);
  forwardEnc(7.5);
  turnToHeading(0);
  outtakeStart();
  forwardDist(43.5, 50);
  wait(0.05, sec);
  backwardEnc(5);
  turnToHeading(270);
  forwardEnc(40);
  pushDisc();
  pushDisc();

  */






  // vex::thread f(ButtonA_pressed3);
  // turnToHeading(195, 50);
  // outtakeStart();
  // forwardEnc(5);
  // wait(0.15, sec);
  // backwardEnc(5, 100);
  // intakeStart();
  // turnToHeading(90);
  // forwardEnc(40);
  // pushDisc();
  // pushDisc();
  // backwardEnc(10);
  // turnToHeading(345);
  

  /*
  driveToCoordinate2(50, -8, 50);
  driveToCoordinate(12, 48);
  turnToHeading(44, 50);
  pushDisc();
  pushDisc();
  wait(0.1, sec);
  */



  // Roller + 2 Low Discs
  /*
  turnToHeading(195, 50);
  outtakeStart();
  forwardEnc(5.5);
  wait(0.15, sec);
  backwardEnc(5);
  intakeStart();
  driveToCoordinate(57, -8, 100);
  pushDisc();
  wait(0.25, sec);
  pushDisc();
  wait(0.25, sec);
  pushDisc();
  stopFlywheel();
  //driveToCoordinate2(50, -8, 50);
  //driveToCoordinate(50, 50);
  */

  

  // spinFlywheel(50);
  // turnToHeading(0, 50);
  // pushDisc();

  // turnToHeading(44, 50);
  // forwardEnc(12);

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
  maintainSpeed = false;

  prerequisites();

  vex::thread t(robotPosition);
  vex::thread f(Driver_pressed);

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

  Controller1.ButtonX.pressed(pushDiscs);
  Controller1.ButtonB.pressed(ButtonB_pressed);
  Controller1.ButtonRight.pressed(expansion);
  Controller1.ButtonRight.pressed(expansion2);

  Controller1.ButtonR1.pressed(indexerForward);
  Controller1.ButtonR2.pressed(indexerBackward);
  }

  /*

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
  Controller1.ButtonA.pressed(ButtonA_pressed); // Controller1.ButtonA.pressed(spinFlywheelDriver);
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
  */
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