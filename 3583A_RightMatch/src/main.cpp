/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\The_BigPotato                                    */
/*    Created:      Wed Feb 15 2023                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LimitSwitchH         limit         H               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;

float driveVel = 1.00;
bool cataLoad= false;
competition Competition;

int whenStarted() {
  leftDrive.setStopping(coast);
  rightDrive.setStopping(coast);
  intake.setStopping(coast);
  intake.setVelocity(300, percent);
  cata.setStopping(coast);
  cata.setVelocity(60, percent);
  cata.setPosition(0, degrees);
  cata.spin(reverse);
  wait(0.5, sec);
  while(!limitSwitch.pressing()) {
    wait(20, msec);
  }
  cata.stop();
  expansion.set(false);
  return 0;
}

void driver_control () {
  leftDrive.setStopping(coast);
  rightDrive.setStopping(coast);
  intake.setStopping(coast);
  intake.setVelocity(300, percent);
  cata.setStopping(coast);
  cata.setVelocity(60, percent);
  cata.setPosition(0, degrees);
  expansion.set(false);
}

void buttonX() {
  cata.setStopping(coast);
  cata.spinFor(reverse, 1080, deg, true);
  // cata.setStopping(hold);
  
  Controller.Screen.clearLine(3);
  Controller.Screen.setCursor(3, 1);
  Controller.Screen.print(cata.temperature(fahrenheit));
}
void buttonA() {
  cata.spin(reverse);
  if (cataLoad) {
    wait(0.5, sec);
  }
  while(!limitSwitch.pressing()) {
    wait(20, msec);
  }
  cata.stop();
  cataLoad = true;
}

void buttonRight() {
  while(Controller.ButtonDown.pressing() != true){
  }
  expansion.set(true);
}

void axis3changed() {
  float x = Controller.Axis3.position();

  leftDrive.setVelocity(0.000086*x*x*x+0.1537*x, percent);
  leftDrive.spin(forward);
}

void axis2changed() {
  float x = Controller.Axis2.position();

  rightDrive.setVelocity(0.000086*x*x*x+0.1537*x, percent);
  rightDrive.spin(forward);
}

void Drive(float dist, int vel, bool wait) {
    double dist2 = (dist/(3.25*3.1415926535) * 360) * 1.5;
    leftDrive.setVelocity(vel, percent);
    rightDrive.setVelocity(vel, percent);

    if (wait == false) {
        leftDrive.spinFor(forward, dist2, degrees, false);
        rightDrive.spinFor(forward, dist2, degrees, false);
    } else {
        leftDrive.spinFor(forward, dist2, degrees, false);
        rightDrive.spinFor(forward, dist2, degrees, true);
    }
}

void Turn(float deg, float vel) {
    //global myVariable, driveVel
    float deg2 = (deg/(3.25*3.1415926535) * 360) * 0.15;
    leftDrive.setVelocity(vel, percent);
    rightDrive.setVelocity(vel, percent);

    leftDrive.spinFor(forward, deg2, degrees, false);
    rightDrive.spinFor(reverse, deg2, degrees, false);
}

void rightAuton () {
  //right
  
}

int main() {
  Controller.ButtonX.pressed(buttonX);
  Controller.ButtonRight.pressed(buttonRight);
  Controller.Axis3.changed(axis3changed);
  Controller.Axis2.changed(axis2changed);
  Controller.ButtonA.pressed(buttonA);
  vexcodeInit();
  whenStarted();

  Competition.autonomous(rightAuton);
  Competition.drivercontrol(driver_control);
  
  while (true) {
    if (limitSwitch.pressing()) {
      Brain.Screen.setPenColor(green);
      Brain.Screen.setFillColor(green);
      Brain.Screen.drawCircle(240, 120, 60); 
    } else {
      Brain.Screen.setPenColor(red);
      Brain.Screen.setFillColor(red);
      Brain.Screen.drawCircle(240, 120, 60); 
    }
    wait(100, msec);
  }
}
 