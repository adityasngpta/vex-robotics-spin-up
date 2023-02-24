#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;



// VEXcode device constructors
motor intake = motor(PORT18, ratio6_1, true);
motor cata = motor(PORT6, ratio18_1, false);
pneumatics expansion = pneumatics(Brain.ThreeWirePort.A);
motor leftDriveA = motor(PORT12, ratio6_1, true);
motor leftDriveB = motor(PORT19, ratio6_1, true);
motor leftDriveC = motor(PORT13, ratio6_1, false);
motor rightDriveA = motor(PORT11, ratio6_1, false);
motor rightDriveB = motor(PORT20, ratio6_1, false);
motor rightDriveC = motor(PORT14, ratio6_1, true);
motor_group leftDrive = motor_group(leftDriveA, leftDriveB, leftDriveC);
motor_group rightDrive = motor_group(rightDriveA, rightDriveB, rightDriveC);
limit limitSwitch = limit(Brain.ThreeWirePort.H);
inertial isensor = inertial(PORT2);
smartdrive driveTrain = smartdrive(leftDrive, rightDrive, isensor, 3.25*acos(-1), 9.5, 10, distanceUnits::in, 2/3);
encoder encLeft = encoder(Brain.ThreeWirePort.D); // and E
encoder encRight = encoder(Brain.ThreeWirePort.B); // and C
distance dsensor = distance(PORT17);

// VEXcode generated functions
bool RCEnabled = true;
bool intakeStop = true;
bool cataStop = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  task ControllerLoopTask;
}