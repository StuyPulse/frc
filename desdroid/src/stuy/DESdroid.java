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

    //CANJaguar driveFrontLeft, driveRearLeft, driveFrontRight, driveRearRight;
    Victor driveFrontLeft, driveRearLeft, driveFrontRight, driveRearRight;
    Arm arm;
    Grabber grabber;
    DigitalInput leftSensor, middleSensor, rightSensor;
    // Driver controls
    Joystick leftStick;
    Joystick rightStick;
    Joystick armStick;

    OperatorInterface oi;
    DriveTrain drive;
    // Autonomous class
    Autonomous auton;

    /**
     * DESdroid constructor.
     */
    public DESdroid() {
       // oi = new OperatorInterface(this);

       // arm = new Arm(this);
       // grabber = new Grabber(this);

        leftStick = new Joystick(PORT_LEFT_STICK);
        rightStick = new Joystick(PORT_RIGHT_STICK);


        leftSensor = new DigitalInput(LINE_SENSOR_LEFT_CHANNEL);
        middleSensor = new DigitalInput(LINE_SENSOR_MIDDLE_CHANNEL);
        rightSensor = new DigitalInput(LINE_SENSOR_RIGHT_CHANNEL);
/*
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
        } */

        driveFrontLeft = new Victor(DRIVE_CAN_DEVICE_FRONT_LEFT);
        driveFrontRight = new Victor(DRIVE_CAN_DEVICE_FRONT_RIGHT);
        driveRearLeft = new Victor(DRIVE_CAN_DEVICE_REAR_LEFT);
        driveRearRight = new Victor(DRIVE_CAN_DEVICE_REAR_RIGHT);

        drive = new DriveTrain(driveFrontLeft,
                driveRearLeft,
                driveFrontRight,
                driveRearRight);

        auton = new Autonomous(this);
    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
        getWatchdog().setEnabled(false);

//        auton.run(oi.getAutonSetting(this));
        auton.lineTrack(false, false);
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);
        
        while (isEnabled() && isOperatorControl()) {
            drive.mecanumDrive_Cartesian(
                    leftStick.getX(),   // X translation (horizontal strafe)
                    leftStick.getY(), // Y translation (straight forward)
                    rightStick.getX(), // rotation (clockwise?)
                    0,             // use gyro for field-oriented drive
                    true);
        }
    }

    /**
     * update PID values.  uses a text file drive_PID_values.txt that must be
     * uploaded to the cRIO via ftp://10.6.94.2/ in the root directory.
     */ /*
    public void updatePID() {
        double drivePID[];
//        drivePID = FileIO.getArray("drive_PID_values.txt");
        drivePID = new double[3];
        drivePID[0] = SPEED_P;
        drivePID[1] = SPEED_I;
        drivePID[2] = SPEED_D;

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
    } */
}
