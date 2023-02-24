#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
motor intake = motor(PORT18, ratio36_1, true);
motor cata = motor(PORT6, ratio18_1, false);
digital_out expansion = digital_out(Brain.ThreeWirePort.A);
motor leftDriveA = motor(PORT12, ratio36_1, true);
motor leftDriveB = motor(PORT19, ratio36_1, true);
motor leftDriveC = motor(PORT13, ratio36_1, false);
motor rightDriveA = motor(PORT11, ratio36_1, false);
motor rightDriveB = motor(PORT20, ratio36_1, false);
motor rightDriveC = motor(PORT14, ratio36_1, true);
motor_group leftDrive = motor_group(leftDriveA, leftDriveB, leftDriveC);
motor_group rightDrive = motor_group(rightDriveA, rightDriveB, rightDriveC);
controller Controller = controller(primary);
limit limitSwitch = limit(Brain.ThreeWirePort.H);

// VEXcode generated functions
bool RCEnabled = true;
bool intakeStop = true;
bool cataStop = true;
int ControllerLoop() {
  while(true) {
    if(RCEnabled) {
      //INTAKE
      if(Controller.ButtonL1.pressing()){
        intake.spin(forward);
        intakeStop = false;
      } else if(Controller.ButtonL2.pressing()) {
        intake.spin(reverse);
        intakeStop = false;
      } else if(!intakeStop){
        intake.stop();
        intakeStop = true;
      }
      //----------------------
      //CATAPULT
      if(Controller.ButtonR1.pressing()){
        cata.spin(forward);
        cataStop = false;
      } else if(Controller.ButtonR2.pressing()) {
        cata.spin(reverse);
        cataStop = false;
      } else if(!cataStop){
        cata.stop();
        cataStop = true;
      }
    
    }
    wait(20, msec);
  }
  return 0;
}

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task ControllerLoopTask(ControllerLoop);
}