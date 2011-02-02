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
    DigitalInput leftSensor, middleSensor, rightSensor;

    // Driver controls
    Joystick leftStick;
    Joystick rightStick;
    Joystick armStick;
    DriverStation ds; // driver station object for getting selections
    OperatorInterface oi;

    // Autonomous class
    Autonomous auton;

    public DESdroid() {
        try {
            driveFrontLeft = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_LEFT);
            driveRearLeft = new CANJaguar(DRIVE_CAN_DEVICE_REAR_LEFT);
            driveFrontRight = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_RIGHT);
            driveRearRight = new CANJaguar(DRIVE_CAN_DEVICE_REAR_RIGHT);
        }
        catch (Exception e) {

        }

        drive = new RobotDrive(driveFrontLeft,
                driveRearLeft,
                driveFrontRight,
                driveRearRight);

        drive.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, false);
        drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, false);
        drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);

        leftStick = new Joystick(PORT_LEFT_STICK);
        rightStick = new Joystick(PORT_RIGHT_STICK);
        armStick = new Joystick(PORT_ARM_STICK);

        arm = new Arm();
        grabber = new Grabber();

        leftSensor = new DigitalInput(LINE_SENSOR_LEFT_CHANNEL);
        middleSensor = new DigitalInput(LINE_SENSOR_MIDDLE_CHANNEL);
        rightSensor = new DigitalInput(LINE_SENSOR_RIGHT_CHANNEL);

        // get the driver station instance to read the digital I/O pins
        ds = DriverStation.getInstance();

        oi = new OperatorInterface();

        auton = new Autonomous(this);
    }

     /**
      * This function is called once each time the robot enters autonomous mode.
      */
    public void autonomous() {
        getWatchdog().setEnabled(false);

        auton.run(oi.getAutonSetting());
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);

        while (isEnabled() && isOperatorControl()) {
            drive.mecanumDrive_Cartesian(
                    leftStick.getX(), // X translation (horizontal strafe)
                    leftStick.getY(), // Y translation (straight forward)
                    rightStick.getX(), // rotation (clockwise?)
                    0.0);                   // use gyro for field-oriented drive

            arm.rotate(armStick.getY());

            // Control grabber: wat do?

        }
    }
}
