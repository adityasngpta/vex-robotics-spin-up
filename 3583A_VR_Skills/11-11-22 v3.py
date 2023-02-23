#region VEXcode Generated Robot Configuration
import math
import random
from vexcode_vrc import *
from vexcode_vrc.events import get_Task_func
  
# constructors

drivetrain = Drivetrain()
brain = Brain()
bottom_distance = Distance("BottomDistance", 18)
roller_optical = Optical("RollerOptical", 2)
gps = GPS("GPS", 3)
intake_motor_group = Motor("IntakeMotorGroup", 10)
bottom_line_tracker = LineTracker("BottomLineTracker", 22)
middle_line_tracker = LineTracker("MiddleLineTracker", 23)
top_line_tracker = LineTracker("TopLineTracker", 24)
#endregion VEXcode Generated Robot Configuration


"""
11-1-2022 v3
Change list:
 - finished route
 - made some slight changes to make it more consistent
Working on:
 - getting a heckin good run

current score: 322 pts (3 sec stop)
"""

vexcode_brain_precision = 0
unfixedHeading = 0

def turnToBlueHighGoal():
    global vexcode_brain_precision
    unfixedHeading = math.atan((-1330 - gps.y_position(MM)) / (-1330 - gps.x_position(MM))) / math.pi * 180
    if gps.y_position(MM) > -1330 and gps.x_position(MM) > -1330:
        drivetrain.turn_to_heading((-1 * unfixedHeading), DEGREES, wait=True)
    elif gps.y_position(MM) > -1330 and gps.x_position(MM) < -1330:
        drivetrain.turn_to_heading(-180 - unfixedHeading, DEGREES, wait=True)
    elif gps.y_position(MM) < -1330 and gps.x_position(MM) > -1330:
        drivetrain.turn_to_heading(-unfixedHeading, DEGREES, wait=True)

def turnToRedHighGoal():
    global vexcode_brain_precision
    unfixedHeading = math.atan((1330 - gps.y_position(MM)) / (1330 - gps.x_position(MM))) / math.pi * 180
    if gps.y_position(MM) < 1330 and gps.x_position(MM) < 1330:
        drivetrain.turn_to_heading(180 - unfixedHeading, DEGREES, wait=True)
    elif gps.y_position(MM) < 1330 and gps.x_position(MM) > 1330:
        drivetrain.turn_to_heading(360 - unfixedHeading, DEGREES, wait=True)
    elif gps.y_position(MM) > 1330 and gps.x_position(MM) < 1330:
        drivetrain.turn_to_heading(540 - unfixedHeading, DEGREES, wait=True)

def when_started1():
    global vexcode_brain_precision
    drivetrain.set_drive_velocity(100, PERCENT)
    intake_motor_group.set_velocity(100, PERCENT)
    drivetrain.set_turn_velocity(100, PERCENT)
    """
    drivetrain.drive_for(FORWARD, 45, INCHES, wait=True)
    drivetrain.turn_to_heading(-90, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 75, INCHES, wait=True)
    """
    turnToRedHighGoal()
    intake_motor_group.spin(REVERSE)
    brain.screen.print(drivetrain.heading(DEGREES))
    brain.screen.next_row()

def code():
    drivetrain.set_drive_velocity(200, PERCENT)
    intake_motor_group.set_velocity(100, PERCENT)
    drivetrain.set_turn_velocity(200, PERCENT)

    turnToBlueHighGoal()
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 13.8, INCHES, wait=True)
    wait(1.2, SECONDS)

    drivetrain.turn_to_heading(0, DEGREES, wait=True)
    drivetrain.drive_for(REVERSE, 1, INCHES, wait=True)
    wait(0.18, SECONDS)
    intake_motor_group.stop()

    drivetrain.turn_to_heading(0, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 3, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 0.4, INCHES, wait=True)
    turnToBlueHighGoal()
    wait(0.75, SECONDS)

    drivetrain.turn_to_heading(-20, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 20, INCHES, wait=True)
    drivetrain.turn_to_heading(90, DEGREES, wait=True)
    drivetrain.drive_for(REVERSE, 2, INCHES, wait=True)
    wait(0.18, SECONDS)

    drivetrain.turn_to_heading(90, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 17, INCHES, wait=True)
    wait(0.6, SECONDS)
    turnToRedHighGoal()
    intake_motor_group.set_velocity(95, PERCENT)
    wait(0.9, SECONDS)
    intake_motor_group.set_velocity(100, PERCENT)

    drivetrain.turn_to_heading(12, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 16, INCHES, wait=True)
    drivetrain.turn_to_heading(35, DEGREES, wait=False)
    wait(0.2, SECONDS)
    intake_motor_group.stop()
    drivetrain.drive_for(FORWARD, 15.6, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 0.9, INCHES, wait=True)
    drivetrain.turn_to_heading(40, DEGREES, wait=False)
    wait(0.2, SECONDS)
    intake_motor_group.stop()
    drivetrain.drive_for(FORWARD, 16, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 1, INCHES, wait=True)
    wait(0.2, SECONDS)
    drivetrain.drive_for(REVERSE, 0.9, INCHES, wait=True)
    intake_motor_group.stop()
    turnToBlueHighGoal()
    intake_motor_group.spin(REVERSE)
    wait(1.2, SECONDS)

    drivetrain.turn_to_heading(-72, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 30, INCHES, wait=True)
    drivetrain.turn_to_heading(77, DEGREES, wait=True)
    intake_motor_group.stop()
    drivetrain.drive_for(FORWARD, 5, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    wait(0.1, SECONDS)
    drivetrain.drive_for(FORWARD, 9.9, INCHES, wait=True)
    turnToRedHighGoal()
    wait(1, SECONDS)

    drivetrain.turn_to_heading(90, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, (gps.y_position(MM) - 460), MM, wait=True)
    drivetrain.turn_to_heading(-5.5, DEGREES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 4, INCHES, wait=True)
    wait(0.1, SECONDS)
    drivetrain.drive_for(FORWARD, 17.9, INCHES, wait=True)
    wait(0.1, SECONDS)
    intake_motor_group.stop()
    drivetrain.turn_to_heading(20, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 21, INCHES, wait=True)
    turnToRedHighGoal()
    drivetrain.turn_for(RIGHT, 1, DEGREES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 5, INCHES, wait=True)
    wait(1.5, SECONDS)
    drivetrain.drive_for(FORWARD, 1, INCHES, wait=True)
    wait(0.5, SECONDS)
    drivetrain.drive_for(REVERSE, 1, INCHES, wait=True)
    wait(1.5, SECONDS)

    drivetrain.turn_to_heading(140, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 20.5, INCHES, wait=True)
    wait(0.7, SECONDS)
    intake_motor_group.stop()
    drivetrain.drive_for(FORWARD, 2, INCHES, wait=True)
    turnToRedHighGoal()
    intake_motor_group.set_velocity(95, PERCENT)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 23.6, INCHES, wait=True)
    wait(1.9, SECONDS)
    intake_motor_group.set_velocity(100, PERCENT)

    drivetrain.turn_to_heading(45, DEGREES, wait=True)
    intake_motor_group.stop()
    drivetrain.drive_for(FORWARD, 20, INCHES)
    drivetrain.turn_to_heading(180, DEGREES, wait=True)
    drivetrain.drive_for(REVERSE, 6, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(REVERSE, 2, INCHES, wait=True)
    wait(0.19, SECONDS)
    intake_motor_group.stop()

    drivetrain.drive_for(FORWARD, 20, INCHES, wait=True)
    drivetrain.turn_to_heading(-90, DEGREES, wait=True)
    drivetrain.drive_for(REVERSE, 13, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(REVERSE, 2, INCHES, wait=True)
    wait(0.17, SECONDS)
    drivetrain.drive_for(FORWARD, 10, INCHES, wait=True)
    
    drivetrain.turn_to_heading(-150, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 27, INCHES, wait=True)
    drivetrain.turn_to_heading(-135, DEGREES, wait=True)
    wait(0.1, SECONDS)
    intake_motor_group.stop()
    drivetrain.drive_for(FORWARD, 12, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 2, INCHES, wait=True)
    drivetrain.turn_to_heading(-138, DEGREES, wait=True)
    intake_motor_group.stop()
    drivetrain.drive_for(FORWARD, 15, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 2.3, INCHES, wait=True)
    wait(0.2, SECONDS)
    intake_motor_group.stop()
    turnToRedHighGoal()
    drivetrain.turn_for(LEFT, 1, DEGREES, wait=False)
    intake_motor_group.spin(REVERSE)
    wait(1.2, SECONDS)
    intake_motor_group.stop()
    
    drivetrain.turn_to_heading(101, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 36, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.turn_to_heading(230, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 1, INCHES, wait=True)
    wait(0.2, SECONDS)
    intake_motor_group.stop()
    drivetrain.turn_to_heading(260, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 6, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 2, INCHES, wait=True)
    wait(0.2, SECONDS)
    intake_motor_group.stop()
    drivetrain.turn_to_heading(265, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 5.5, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 2.3, INCHES, wait=True)
    turnToBlueHighGoal()
    wait(1, SECONDS)

    drivetrain.turn_to_heading(-90, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, -gps.y_position(MM) - 460, MM, wait=True)
    drivetrain.turn_to_heading(180 - 5.5, DEGREES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 4, INCHES, wait=True)
    wait(0.1, SECONDS)
    drivetrain.drive_for(FORWARD, 17.9, INCHES, wait=True)
    wait(0.1, SECONDS)
    intake_motor_group.stop()
    drivetrain.turn_to_heading(200, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 21, INCHES, wait=True)
    turnToBlueHighGoal()
    drivetrain.turn_for(RIGHT, 1, DEGREES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 5, INCHES, wait=True)
    wait(1.5, SECONDS)
    drivetrain.drive_for(FORWARD, 1, INCHES, wait=True)
    wait(0.5, SECONDS)
    drivetrain.drive_for(REVERSE, 1, INCHES, wait=True)
    wait(1.5, SECONDS)

    drivetrain.turn_to_heading(-40, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 22.7, INCHES, wait=True)
    wait(0.7, SECONDS)
    turnToBlueHighGoal()
    wait(1.1, SECONDS)

    drivetrain.turn_to_heading(-45, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 20, INCHES, wait=True)
    wait(0.1, SECONDS)
    intake_motor_group.stop()
    drivetrain.turn_to_heading(35, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 8, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 2, INCHES, wait=True)
    wait(0.1, SECONDS)
    intake_motor_group.stop()
    drivetrain.turn_to_heading(43, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 33, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 2, INCHES, wait=True)
    wait(0.2, SECONDS)
    intake_motor_group.set_velocity(95, PERCENT)
    turnToBlueHighGoal()
    wait(1, SECONDS)
    intake_motor_group.set_velocity(100, PERCENT)

    drivetrain.turn_to_heading(45, DEGREES, wait=True)
    drivetrain.drive_for(FORWARD, 24, INCHES, wait=True)
    intake_motor_group.stop()
    drivetrain.drive_for(FORWARD, 26, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 2, INCHES, wait=True)
    intake_motor_group.stop()
    drivetrain.drive_for(FORWARD, 13, INCHES, wait=True)
    intake_motor_group.spin(REVERSE)
    drivetrain.drive_for(FORWARD, 1, INCHES, wait=True)
    wait(0.3, SECONDS)
    intake_motor_group.stop()
    drivetrain.drive_for(REVERSE, 9, INCHES, wait=True)
    turnToBlueHighGoal()
    intake_motor_group.spin(REVERSE)
vr_thread(code)