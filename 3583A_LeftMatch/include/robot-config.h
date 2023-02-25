using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor intake;
extern motor cata;
extern digital_out expansion;
extern motor leftDriveA; 
extern motor leftDriveB; 
extern motor leftDriveC; 
extern motor rightDriveA; 
extern motor rightDriveB; 
extern motor rightDriveC; 
extern motor_group leftDrive;
extern motor_group rightDrive;
extern controller Controller;
extern limit limitSwitch;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );