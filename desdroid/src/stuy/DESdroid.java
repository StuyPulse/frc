package stuy;
/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

import edu.wpi.first.wpilibj.*;
import java.util.Vector;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class DESdroid extends SimpleRobot implements Constants {

    // Robot hardware
    CANJaguar driveFrontLeft, driveRearLeft, driveFrontRight, driveRearRight;
    DriveTrain drive;
    Arm arm;
    Grabber grabber;
    DigitalInput leftSensor, middleSensor, rightSensor;
    // Driver controls
    Joystick leftStick;
    Joystick rightStick;
    Joystick armStick;
    OperatorInterface oi;
    // Autonomous class
    Autonomous auton;
    double[] positions;
    DESCircleTracker pegTracker;
    DESTrackerDashboard trackerDashboard;
    boolean isTargeting = false;
    boolean isOn = false;
    boolean wasEnabledOnce = false;
    Vector targetVals;

    /**
     * DESdroid constructor.
     */
    public DESdroid() {
        oi = new OperatorInterface(this);

//        arm = new Arm(this);
//        grabber = new Grabber();
//
        leftStick = new Joystick(PORT_LEFT_STICK);
//        rightStick = new Joystick(PORT_RIGHT_STICK);
//        armStick = new Joystick(PORT_ARM_STICK);
//
//        leftSensor = new DigitalInput(LINE_SENSOR_LEFT_CHANNEL);
//        middleSensor = new DigitalInput(LINE_SENSOR_MIDDLE_CHANNEL);
//        rightSensor = new DigitalInput(LINE_SENSOR_RIGHT_CHANNEL);
//
//        try {
//            driveFrontLeft = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_LEFT, CANJaguar.ControlMode.kSpeed);
//            driveFrontRight = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_RIGHT, CANJaguar.ControlMode.kSpeed);
//            driveRearLeft = new CANJaguar(DRIVE_CAN_DEVICE_REAR_LEFT, CANJaguar.ControlMode.kSpeed);
//            driveRearRight = new CANJaguar(DRIVE_CAN_DEVICE_REAR_RIGHT, CANJaguar.ControlMode.kSpeed);
//
//            driveFrontLeft.setSpeedReference(CANJaguar.SpeedReference.kQuadEncoder);
//            driveFrontRight.setSpeedReference(CANJaguar.SpeedReference.kQuadEncoder);
//            driveRearLeft.setSpeedReference(CANJaguar.SpeedReference.kQuadEncoder);
//            driveRearRight.setSpeedReference(CANJaguar.SpeedReference.kQuadEncoder);
//
//            driveFrontLeft.configEncoderCodesPerRev(ENCODER_CODES_PER_REV);
//            driveFrontRight.configEncoderCodesPerRev(ENCODER_CODES_PER_REV);
//            driveRearLeft.configEncoderCodesPerRev(ENCODER_CODES_PER_REV);
//            driveRearRight.configEncoderCodesPerRev(ENCODER_CODES_PER_REV);
//
//            updatePID();
//
//            drive = new DriveTrain(driveFrontLeft,
//                    driveRearLeft,
//                    driveFrontRight,
//                    driveRearRight);
//        } catch (Exception e) {
//            e.printStackTrace();
//        }
//
//
//        targetVals = new Vector();
//        trackerDashboard = new DESTrackerDashboard(this);
//        pegTracker = new DESCircleTracker(this);
//
//        System.out.println(pegTracker);
//        System.out.println(pegTracker.halogen_a);
//
//        auton = new Autonomous(this);
//
//        positions = FileIO.getArray("positions.txt"); // TODO: where is this file?
    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
//        getWatchdog().setEnabled(false);
//
////        auton.run(oi.getAutonSetting(this));
//        auton.run(1);

    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {


        getWatchdog().setEnabled(false);
        //pegTracker.halogen_a.set(Relay.Value.kOn);

//        double lastTimeSeconds = Timer.getFPGATimestamp();

        int i = 0;
        while (isEnabled() && isOperatorControl()) {
//            System.out.println(oi.getHeightButton());
            try {
                oi.enhancedIO.setDigitalOutput(LIGHT_BIT_D_CHANNEL, leftStick.getRawButton(6));
                oi.enhancedIO.setDigitalOutput(LIGHT_BIT_C_CHANNEL, leftStick.getRawButton(7));
                oi.enhancedIO.setDigitalOutput(LIGHT_BIT_B_CHANNEL, leftStick.getRawButton(10));
                oi.enhancedIO.setDigitalOutput(LIGHT_BIT_A_CHANNEL, leftStick.getRawButton(11));
            }
            catch (Exception e) {
                System.out.println("shit");
            }

            if (oi.getMinibotSwitch()) {
                System.out.println("Minibot switch");
            }

            if (oi.getWingSwitch()) {
                System.out.println("Wing switch");
            }

            if (oi.getExtraButton()) {
                System.out.println("Extra button");
            }

            /**drive.mecanumDrive_Cartesian(
                    leftStick.getX(), // X translation (horizontal strafe)
                    leftStick.getY(), // Y translation (straight forward)
                    rightStick.getX(), // rotation (clockwise?)
                    0, // use gyro for field-oriented drive
                    true);
             */

//            if (leftStick.getRawButton(3))
//                drive.mecanumDrive_Cartesian(0, -1, 0, 0, false);
//            else if(leftStick.getRawButton(2))
//                drive.mecanumDrive_Cartesian(0, 1, 0, 0, false);
//            else if(leftStick.getRawButton(4))
//                drive.mecanumDrive_Cartesian(-1, 0, 0, 0, false);
//            else if(leftStick.getRawButton(5))
//                drive.mecanumDrive_Cartesian(1, 0, 0, 0, false);
//            else
//                drive.mecanumDrive_Cartesian(0, 0, 0, 0, false);
//
//            // Arm control
//            if (armStick.getRawButton(4))
//                arm.wrist.set(0);
//
//            if (armStick.getRawButton(11)) {
//                arm.setHeight(positions[0]);
//            } else if (armStick.getRawButton(10)) {
//                arm.setHeight(positions[1]);
//            } else if (armStick.getRawButton(9)) {
//                arm.setHeight(positions[2]);
//            } else {
//                arm.rotate(armStick.getY());
//            }
//
//            if (armStick.getRawButton(8)) {
//                positions = FileIO.getArray("positions.txt");
//            }
//
//            // Grabber control
//            if (armStick.getTrigger()) {
//                grabber.in();
//            } else if (armStick.getRawButton(2)) {
//                grabber.out();
//            } else if (armStick.getRawButton(6)) {
//                grabber.rotateUp();
//            } else if (armStick.getRawButton(7)) {
//                grabber.rotateDown();
//            } else {
//                grabber.stop();
//            }
//
//            if (Timer.getFPGATimestamp() - lastTimeSeconds > 0.25) {
//                try {
//                    //System.out.println("Requested position: " + setPos + " current position: " + arm.armMotor.getPosition());
//                } catch (Exception e) {
//                    e.printStackTrace();
//                }
//                lastTimeSeconds = Timer.getFPGATimestamp();
//            }
//
//            wasEnabledOnce = true;
//
//            // Place the robot centered in front of a target and record the xPos
//            // value (press button 7 to find the target).  Since the camera is
//            // off-center, this value must be determined experimentally.  Put it
//            // into Constants.java as PID_SETPOINT.
//
//            // Move the robot or the target, then press and hold button 10 to
//            // align using PID feedback control (tune the PID gains as well).
//
//            if (!leftStick.getRawButton(7)) {
//                if (isTargeting) {
//                    pegTracker.halogen_a.set(Relay.Value.kOff);
//                    pegTracker.stopAligning();
//                    System.out.println("Stopped");
//                }
//                isTargeting = false;
//            } else {
//                pegTracker.halogen_a.set(Relay.Value.kOn);
//                if (!isTargeting) {
//                    Timer.delay(.5);
//                }
//                pegTracker.doCamera();
//                targetVals.addElement("" + pegTracker.mainTarget.m_xPos);
//
//
//                if (!isTargeting) {
//                    pegTracker.startAligning();
//                    System.out.println("Started");
//                    isTargeting = true;
//                }
//
//            }
//
//            if (leftStick.getRawButton(11)) {
//                pegTracker.updatePID();
//            }
//
//            /*
//            if (rightStick.getTrigger() && !isOn) {
//            pegTracker.halogen_a.set(Relay.Value.kOn);
//            Timer.delay(.5);
//            isOn = true;
//            pegTracker.doCamera();
//            //   Timer.delay(1);
//            } else {
//            //pegTracker.halogen_a.set(Relay.Value.kOff);
//            }
//
//            if (rightStick.getTop()) {
//            isOn = false;
//            }
//
//             */
//
//
//
//
//            /*
//            if (leftStick.getTrigger()) {
//            pegTracker.halogen_a.set(Relay.Value.kOn);
//            }
//            else {
//            pegTracker.halogen_a.set(Relay.Value.kOff);
//            } */
//        }
//        /*
//        pegTracker.halogen_a.set(Relay.Value.kOff);
//        System.out.println(targetVals); */
//
//        if (wasEnabledOnce) {
//            for (int i = 0; i < targetVals.size(); i++) {
//                System.out.println(targetVals.elementAt(i) + "\t" + pegTracker.outputVals.elementAt(i));
//
//            }
        }
    }

    /**
     * update PID values.  uses a text file drive_PID_values.txt that must be
     * uploaded to the cRIO via ftp://10.6.94.2/ in the root directory.
     */
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
    }
}
