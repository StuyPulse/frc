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
//    VictorSpeed driveFrontLeft, driveRearLeft, driveFrontRight, driveRearRight;
    Victor driveFrontLeft, driveRearLeft, driveFrontRight, driveRearRight;
    Arm arm;
    Grabber grabber;
    DigitalInput leftSensor, middleSensor, rightSensor;
    // Driver controls
    Joystick leftStick;
    Joystick rightStick;
    Joystick armStick;
    OperatorInterface oi;
    RobotDrive drive;
    // Autonomous class
    Autonomous auton;

    /**
     * DESdroid constructor.
     */
    public DESdroid() {
        //oi = new OperatorInterface(this);

        arm = new Arm(this);
        grabber = new Grabber();

        leftSensor = new DigitalInput(LINE_SENSOR_LEFT_CHANNEL);
        middleSensor = new DigitalInput(LINE_SENSOR_MIDDLE_CHANNEL);
        rightSensor = new DigitalInput(LINE_SENSOR_RIGHT_CHANNEL);

//        driveFrontLeft = new VictorSpeed(CHANNEL_FRONT_LEFT, CHANNEL_FRONT_LEFT_ENC_A, CHANNEL_FRONT_LEFT_ENC_B, true);
//        driveFrontRight = new VictorSpeed(CHANNEL_FRONT_RIGHT, CHANNEL_FRONT_RIGHT_ENC_A, CHANNEL_FRONT_RIGHT_ENC_B, true);
//        driveRearLeft = new VictorSpeed(CHANNEL_REAR_LEFT, CHANNEL_REAR_LEFT_ENC_A, CHANNEL_REAR_LEFT_ENC_B, true);
//        driveRearRight = new VictorSpeed(CHANNEL_REAR_RIGHT, CHANNEL_REAR_RIGHT_ENC_A, CHANNEL_REAR_RIGHT_ENC_B, false);

        leftStick = new Joystick(PORT_LEFT_STICK);
        rightStick = new Joystick(PORT_RIGHT_STICK);
        armStick = new Joystick(PORT_ARM_STICK);

        driveFrontLeft = new Victor(CHANNEL_FRONT_LEFT);
        driveFrontRight = new Victor(CHANNEL_FRONT_RIGHT);
        driveRearLeft = new Victor(CHANNEL_REAR_LEFT);
        driveRearRight = new Victor(CHANNEL_REAR_RIGHT);


        updatePID();

        drive = new RobotDrive(driveFrontLeft,
                driveRearLeft,
                driveFrontRight,
                driveRearRight);

//        drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
//        drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);


        auton = new Autonomous(this);
    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
        auton.lineTrack(false, false);
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

            /*if (leftStick.getRawButton(3))
            drive.mecanumDrive_Cartesian(0, -1, 0, 0);
            else if(leftStick.getRawButton(2))
            drive.mecanumDrive_Cartesian(0, 1, 0, 0);
            else if(leftStick.getRawButton(4))
            drive.mecanumDrive_Cartesian(-1, 0, 0, 0);
            else if(leftStick.getRawButton(5))
            drive.mecanumDrive_Cartesian(1, 0, 0, 0);
            else
            drive.mecanumDrive_Cartesian(0, 0, 0, 0);*/

            if (leftStick.getRawButton(7)) {
                updatePID();
            }
//            if (rightStick.getRawButton(6)) {
//                System.out.println("front left:" +
//                        " get: " + driveFrontLeft.e.get() +
//                        " getRaw: " + driveFrontLeft.e.getRaw() +
//                        " getDis tance: " + driveFrontLeft.e.getDistance() +
//                        " getDirection: " + driveFrontLeft.e.getDirection() +
//                        " getStopped: " + driveFrontLeft.e.getStopped() +
//                        " getPeriod: " + driveFrontLeft.e.getPeriod() +
//                        " getRate: " + driveFrontLeft.e.getRate());
//            }
//
//            if (rightStick.getRawButton(11)) {
//                System.out.println("front right:" +
//                        " get: " + driveFrontRight.e.get() +
//                        " getRaw: " + driveFrontRight.e.getRaw() +
//                        " getDistance: " + driveFrontRight.e.getDistance() +
//                        " getDirection: " + driveFrontRight.e.getDirection() +
//                        " getStopped: " + driveFrontRight.e.getStopped() +
//                        " getPeriod: " + driveFrontRight.e.getPeriod() +
//                        " getRate: " + driveFrontRight.e.getRate());
//            }
//
//            if (rightStick.getRawButton(7)) {
//                System.out.println("rear left:" +
//                        " get: " + driveRearLeft.e.get() +
//                        " getRaw: " + driveRearLeft.e.getRaw() +
//                        " getDistance: " + driveRearLeft.e.getDistance() +
//                        " getDirection: " + driveRearLeft.e.getDirection() +
//                        " getStopped: " + driveRearLeft.e.getStopped() +
//                        " getPeriod: " + driveRearLeft.e.getPeriod() +
//                        " getRate: " + driveRearLeft.e.getRate());
//            }
//
//            if (rightStick.getRawButton(10)) {
//                System.out.println("rear right:" +
//                        " get: " + driveRearRight.e.get() +
//                        " getRaw: " + driveRearRight.e.getRaw() +
//                        " getDistance: " + driveRearRight.e.getDistance() +
//                        " getDirection: " + driveRearRight.e.getDirection() +
//                        " getStopped: " + driveRearRight.e.getStopped() +
//                        " getPeriod: " + driveRearRight.e.getPeriod() +
//                        " getRate: " + driveRearRight.e.getRate());
//            }
//
//            if (rightStick.getTrigger()) {
//                driveFrontLeft.e.reset();
//                driveFrontRight.e.reset();
//                driveRearLeft.e.reset();
//                driveRearRight.e.reset();
//            }
//
//            driveFrontLeft.v.set(0.5);
//            driveFrontRight.v.set(-0.5);
//            driveRearLeft.v.set(0.5);
//            driveRearRight.v.set(-0.5);


            // Arm control
            arm.rotate(armStick.getY());

            // Grabber control
            if (armStick.getTrigger()) {
                grabber.in();
            } else if (armStick.getRawButton(2)) {
                grabber.out();
            } else if (armStick.getRawButton(6)) {
                grabber.rotateUp();
            } else if (armStick.getRawButton(7)) {
                grabber.rotateDown();
            } else {
                grabber.stop();
            }

            Timer.delay(.05);
        }
    }

// update PID values.  uses a text file drive_PID_values.txt that must be
// uploaded to the cRIO via ftp://10.6.94.2/ in the root directory.
    public void updatePID() {
        double drivePID[];


        try {
            drivePID = FileIO.getArray("drive_PID_values.txt");


        } catch (Exception e) {
            e.printStackTrace();
            drivePID = new double[3];
            drivePID[0] = PDRIVE;
            drivePID[1] = IDRIVE;
            drivePID[2] = DDRIVE;


        }
        System.out.println("PID:  " + drivePID[0] + "  " + drivePID[1] + "  " + drivePID[2]);


        try {
            /*            driveFrontLeft.c.disable();
            driveFrontRight.c.disable();
            driveRearLeft.disable();
            driveRearRight.disable();

            driveFrontLeft.c.setPID(drivePID[0], drivePID[1], drivePID[2]);
            driveFrontRight.c.setPID(drivePID[0], drivePID[1], drivePID[2]);
            driveRearLeft.c.setPID(drivePID[0], drivePID[1], drivePID[2]);
            driveRearRight.c.setPID(drivePID[0], drivePID[1], drivePID[2]);

            driveFrontLeft.c.enable();
            driveFrontRight.c.enable();
            driveRearLeft.c.enable();
            driveRearRight.c.enable();
             */
        } catch (Exception e) {
            e.printStackTrace();

        }
    }
}
