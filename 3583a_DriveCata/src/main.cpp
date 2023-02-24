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

  // if(abs(Controller.Axis3.position()) > driveVel){
  //   if(Controller.Axis3.position() < 0-driveVel) {
  //     leftDrive.setVelocity(0 - driveVel, percent);
  //   } else {
  //     leftDrive.setVelocity(driveVel, percent);
  //   }
  // }
  leftDrive.setVelocity(Controller.Axis3.position()*driveVel, percent);
  leftDrive.spin(forward);
}

void axis2changed() {


  /*
  if(abs(Contcataroller.Axis2.position()) > driveVel){
    if(Controller.Axis2.position() < 0-driveVel) {
      rightDrive.setVelocity(0 - driveVel, percent);
    } else {
      rightDrive.setVelocity(driveVel, percent);
    }
  } else  {
    rightDrive.setVelocity(Controller.Axis2.position(), percent);
  }d
  */
  rightDrive.setVelocity(Controller.Axis2.position()*driveVel, percent);
  rightDrive.spin(forward);
};



int main() {
  Controller.ButtonX.pressed(buttonX);
  Controller.ButtonRight.pressed(buttonRight);
  Controller.Axis3.changed(axis3changed);
  Controller.Axis2.changed(axis2changed);
  Controller.ButtonA.pressed(buttonA);
  vexcodeInit();
  whenStarted();

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
 