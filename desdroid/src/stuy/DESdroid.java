package stuy;
/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

import edu.wpi.first.wpilibj.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class DESdroid extends SimpleRobot implements Constants {

    // Robot hardware
    CANJaguar driveFrontLeft, driveFrontRight, driveRearLeft, driveRearRight;
    RobotDrive drive;
    Arm arm;
    Grabber grabber;

    DESTrackerDashboard trackerDashboard;
    DESCircleTracker pegTracker;

    // Driver controls
    Joystick gamepad;
    Joystick armStick;

    // Autonomous class
    Autonomous auton;


    public DESdroid() {
        
        try {
            driveFrontLeft  = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_LEFT);
            driveFrontRight = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_RIGHT);
            driveRearLeft   = new CANJaguar(DRIVE_CAN_DEVICE_REAR_LEFT);
            driveRearRight  = new CANJaguar(DRIVE_CAN_DEVICE_REAR_RIGHT);
        }
        catch (Exception e) {
            System.out.println(e);

        } 

        drive = new RobotDrive(driveFrontLeft,
                               driveRearLeft,
                               driveFrontRight,
                               driveRearRight);

        grabber = new Grabber();


        gamepad  = new Joystick(PORT_GAMEPAD);
        armStick = new Joystick(PORT_ARM_STICK);
        trackerDashboard = new DESTrackerDashboard(this);
        pegTracker = new DESCircleTracker(this);
    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
	System.out.println("Autonomous");
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);

        while (isEnabled() && isOperatorControl()) {
         
            drive.tankDrive(gamepad, 2, gamepad, 4);

            if (gamepad.getRawButton(4)) {
                pegTracker.doCamera();
            }

        }


    }


}