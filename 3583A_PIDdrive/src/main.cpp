/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\srees                                            */
/*    Created:      Tue Nov 22 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    9, 10, 1, 2     
// Flywheel             motor_group   11, 12          
// Intake               motor         3               
// indexer              motor         20              
// pneumatic            digital_out   C               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;


#include <math.h>
int Brain_precision = 0, Console_precision = 0, Controller1_precision = 0;

/*
CHANGELOG:
11/16/2022: Made the "stop" button (b) actually work, by setting maintainTrue==False
11/18/2022: Cleaned up the vestiges of block coding, comments, expansion, 
11/27/2022: Put it into github...maybe?
  12:16 -- kp=0.125, ki=0.0001, kd=0.05, power scale factor = 50
  1:17 -- kp=0.11, ki=0.0, kd=0.6, powerscalefactor=50
*/





//Flywheel PID
  bool maintainSpeed = true;
  bool ReadyShoot = false;

  double kp = 0.110;
  double ki = 0.003;
  double kd = 0.65;

  double preverror = 0.0;
  double error = 0.0;
  double totalError = 0.0; // += error
  double derivative = 0.0; // = error-preverror
  //double flyspeed;
  double Power = 0;

int FlyPID(double targetspeed){
  //debugging
  Brain.Screen.clearScreen();
  Brain.Screen.drawLine(0, 120, 479, 120);
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

      if (totalError>=7500||fabs(error) <= 15)  {
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

// "when started" hat block
int whenStarted1() {
  Drivetrain.setStopping(coast);
  Flywheel.setStopping(coast);
  Flywheel.setVelocity(200.0, percent);
  Intake.setVelocity(200.0, percent);
  indexer.setVelocity(200.0, percent);
  indexer.setStopping(hold);
  Flywheel.setPosition(0.0, degrees);
  Drivetrain.setDriveVelocity(200.0, percent);
  pneumatic.set(false);
  return 0;
}

// "when Controller1 ButtonX pressed" hat block
void ButtonX_pressed() {
  if(ReadyShoot) {
    indexer.spinFor(forward, 60.0, degrees, true);
    wait(0.0, seconds);
    indexer.spinFor(forward, -60.0, degrees, true);
  }
}

//Start running flywheel when button A pressed, start PID
void ButtonA_pressed() {
  FlyPID(515);

  Flywheel.stop();
}

//Controller Button B pressed - stops flywheel
void ButtonB_pressed() {
  maintainSpeed = false;
}

//Fires the expansion
void expansion() {
  while (!Controller1.ButtonDown.pressing()) {
    
  }
  pneumatic.set(true);

}

//retracts the expansion
void expansion2() {
  while (!Controller1.ButtonLeft.pressing()) {
    
  }
  pneumatic.set(false);

}

int main() {
  vexcodeInit();
  // register event handlers
  Controller1.ButtonX.pressed(ButtonX_pressed);
  Controller1.ButtonA.pressed(ButtonA_pressed);
  Controller1.ButtonB.pressed(ButtonB_pressed);
  Controller1.ButtonRight.pressed(expansion);
  Controller1.ButtonRight.pressed(expansion2);
  wait(15, msec);
  // post event registration

  // set default print color to black
  printf("\033[30m");

  // wait for rotation sensor to fully initialize
  wait(30, msec);
  //wait for flywheel to come up to speed
  //wait(5, seconds);
  //highly temporary test code
  // for (int i = 0; i<5; i++) {
  //   indexer.spinFor(forward, 60.0, degrees, true);
  //   wait(0.0, seconds);
  //   indexer.spinFor(forward, -60.0, degrees, true);
  //   wait(0.25, seconds);
  // }

  whenStarted1();
}