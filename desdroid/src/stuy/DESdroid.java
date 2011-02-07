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
    Joystick leftStick, rightStick;
    DriverStation ds; // driver station object for getting selections
    OperatorInterface oi;

    // Autonomous class
    Autonomous auton;

    public DESdroid() {
        try {
            driveFrontLeft = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_LEFT, CANJaguar.ControlMode.kSpeed);
            driveFrontRight = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_RIGHT, CANJaguar.ControlMode.kSpeed);
            driveRearLeft = new CANJaguar(DRIVE_CAN_DEVICE_REAR_LEFT, CANJaguar.ControlMode.kSpeed);
            driveRearRight = new CANJaguar(DRIVE_CAN_DEVICE_REAR_RIGHT, CANJaguar.ControlMode.kSpeed);

            driveFrontLeft.setSpeedReference(CANJaguar.SpeedReference.kQuadEncoder);
            driveFrontRight.setSpeedReference(CANJaguar.SpeedReference.kQuadEncoder);
            driveRearLeft.setSpeedReference(CANJaguar.SpeedReference.kQuadEncoder);
            driveRearRight.setSpeedReference(CANJaguar.SpeedReference.kQuadEncoder);

            driveFrontLeft.configEncoderCodesPerRev(ENCODER_CODES_PER_REV);
            driveFrontRight.configEncoderCodesPerRev(ENCODER_CODES_PER_REV);
            driveRearLeft.configEncoderCodesPerRev(ENCODER_CODES_PER_REV);
            driveRearRight.configEncoderCodesPerRev(ENCODER_CODES_PER_REV);

            updatePID();

            drive = new DriveTrain(driveFrontLeft,
                    driveRearLeft,
                    driveFrontRight,
                    driveRearRight);
        } catch (Exception e) {
            e.printStackTrace();
        }

        leftStick = new Joystick(PORT_LEFT_STICK);
        rightStick = new Joystick(PORT_RIGHT_STICK);


        leftSensor   = new DigitalInput(LINE_SENSOR_LEFT_CHANNEL);
        middleSensor = new DigitalInput(LINE_SENSOR_MIDDLE_CHANNEL);
        rightSensor  = new DigitalInput(LINE_SENSOR_RIGHT_CHANNEL);

        // get the driver station instance to read the digital I/O pins
        ds = DriverStation.getInstance();

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
            drive.mecanumDrive_Cartesian(
                    leftStick.getX(), // X translation (horizontal strafe)
                    leftStick.getY(), // Y translation (straight forward)
                    rightStick.getX(), // rotation (clockwise?)
                    0.0);                   // use gyro for field-oriented drive

            binaryValue = auton.binaryValue(true);
            if (binaryValue != previousValue)
                auton.printLineStatus();
            if (binaryValue != 0)
                previousValue = binaryValue;
            if (leftStick.getRawButton(2)) {
                for (int i = 0; i < FileIO.getArray("straightLine.txt").length; i++) {
                    System.out.println(FileIO.getArray("straightLine.txt")[i]);
                }
            }
        }
    }

        // update PID values.  uses a text file drive_PID_values.txt that must be
    // uploaded to the cRIO via ftp://10.6.94.2/ in the root directory.
    public void updatePID() {
        double drivePID[];
//        drivePID = FileIO.getArray("drive_PID_values.txt");
        drivePID = new double[3];
        drivePID[0] = 0.48;
        drivePID[1] = 0.005;
        drivePID[2] = 0.05;

        System.out.println("PID:  " + drivePID[0] + "  " + drivePID[1] + "  " + drivePID[2]);
        try {
            driveFrontLeft.disableControl();
            driveFrontRight.disableControl();
            driveRearLeft.disableControl();
            driveRearRight.disableControl();

            driveFrontLeft.setPID(drivePID[0], drivePID[1], drivePID[2]);
            driveFrontRight.setPID(drivePID[0], drivePID[1], drivePID[2]);
            driveRearLeft.setPID(drivePID[0], drivePID[1], drivePID[2]);
            driveRearRight.setPID(drivePID[0], drivePID[1], drivePID[2]);

            driveFrontLeft.enableControl();
            driveFrontRight.enableControl();
            driveRearLeft.enableControl();
            driveRearRight.enableControl();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
