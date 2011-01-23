package stuy;
/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.can.CANTimeoutException;

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

    // Driver controls
    Joystick leftStick, rightStick;
    DriverStation ds; // driver station object for getting selections

    // Autonomous class
    Autonomous auton;

    public DESdroid() {
        try {
            driveFrontLeft  = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_LEFT);
            driveFrontRight = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_RIGHT);
            driveRearLeft   = new CANJaguar(DRIVE_CAN_DEVICE_REAR_LEFT);
            driveRearRight  = new CANJaguar(DRIVE_CAN_DEVICE_REAR_RIGHT);
        }
        catch (CANTimeoutException e) {
            e.printStackTrace();
        }

        drive = new RobotDrive(driveFrontLeft,
                               driveRearLeft,
                               driveFrontRight,
                               driveRearRight);

        drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, false);
        drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, false);
        drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, false);
        drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, false);

        // get the driver station instance to read the digital I/O pins
        ds = DriverStation.getInstance();

        leftStick  = new Joystick(PORT_LEFT_STICK);
        rightStick = new Joystick(PORT_RIGHT_STICK);
    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
        auton = new Autonomous(this);
        auton.lineTrackStraight();
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);
        while (isEnabled() && isOperatorControl()) {
            drive.tankDrive(leftStick, rightStick);
        }
    }
}
