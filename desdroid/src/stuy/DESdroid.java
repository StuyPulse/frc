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
    DigitalInput leftSensor, middleSensor, rightSensor;

    // Driver controls
    Joystick gamepad;
    DriverStation ds; // driver station object for getting selections
    OperatorInterface oi;

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

        leftSensor   = new DigitalInput(LINE_SENSOR_LEFT_CHANNEL);
        middleSensor = new DigitalInput(LINE_SENSOR_MIDDLE_CHANNEL);
        rightSensor  = new DigitalInput(LINE_SENSOR_RIGHT_CHANNEL);

        // get the driver station instance to read the digital I/O pins
        ds = DriverStation.getInstance();

        gamepad  = new Joystick(PORT_GAMEPAD);

        auton = new Autonomous(this);
    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
        boolean straightLine, goLeft;

        straightLine = true;
        goLeft = false;

        auton.lineTrack(straightLine, goLeft);
        
        //    switch (oi.getAutonSwitch()) {
        //        case 1: // Go straight
        //            straightLine = true;
        //            goLeft = false;
        //        case 2: // Go left
        //            straightLine = false;
        //            goLeft = true;
        //        case 3: // Go right
        //            straightLine = false;
        //            goLeft = false;
        //        default:
        //            straightLine = true;
        //            goLeft = false;
        //    }

        // Use digital inputs for straight/left input?
        // straightLine = des.ds.getDigitalIn(des.DIGITAL_IN_STRAIGHT_LINE);
        // goLeft = !des.ds.getDigitalIn(des.DIGITAL_IN_GO_LEFT) && !straightLine;
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);

        int binaryValue, previousValue = 0;
        while (isEnabled() && isOperatorControl()) {
            drive.tankDrive(gamepad.getRawAxis(AXIS_GAMEPAD_LEFT),
                            gamepad.getRawAxis(AXIS_GAMEPAD_RIGHT));

            binaryValue = auton.binaryValue(true);
            if (binaryValue != previousValue)
                auton.printLineStatus();
            if (binaryValue != 0)
                previousValue = binaryValue;
        }
    }
}
