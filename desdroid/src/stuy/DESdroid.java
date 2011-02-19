package stuy;
/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

import edu.wpi.first.wpilibj.*;
import java.util.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class DESdroid extends SimpleRobot implements Constants {

    // Robot hardware
    VictorSpeed driveFrontLeft, driveRearLeft, driveFrontRight, driveRearRight;
    VictorSpeed dummyFLeft, dummyRLeft, dummyFRight, dummyRRight;
    DriveTrain drive;

    Arm arm;
    Grabber grabber;
    DigitalInput leftSensor, middleSensor, rightSensor;

    // Driver controls
    Joystick leftStick;
    Joystick rightStick;
    Joystick armStick;

    // Operator interface
    OperatorInterface oi;

    // Autonomous class
    Autonomous auton;
    
    double[] positions;
    DESTrackerDashboard trackerDashboard;
    boolean isTargeting = false;
    boolean isOn = false;
    boolean wasEnabledOnce = false;
    boolean wasArmControlled = false;
    ArmController positionController;
    /**
     * DESdroid constructor.
     */
    public DESdroid() {
        oi = new OperatorInterface(this);

        arm = new Arm(this);
        grabber = new Grabber();
        leftSensor = new DigitalInput(LINE_SENSOR_LEFT_CHANNEL);
        middleSensor = new DigitalInput(LINE_SENSOR_MIDDLE_CHANNEL);
        rightSensor = new DigitalInput(LINE_SENSOR_RIGHT_CHANNEL);

        driveFrontLeft = new VictorSpeed(CHANNEL_FRONT_LEFT, CHANNEL_FRONT_LEFT_ENC_A, CHANNEL_FRONT_LEFT_ENC_B, true);
        dummyFLeft = new VictorSpeed(CHANNEL_FRONT_LEFT_ENC_A, CHANNEL_FRONT_LEFT_ENC_B, true);
        driveFrontRight = new VictorSpeed(CHANNEL_FRONT_RIGHT, CHANNEL_FRONT_RIGHT_ENC_A, CHANNEL_FRONT_RIGHT_ENC_B, false);
        dummyFRight = new VictorSpeed(CHANNEL_FRONT_RIGHT_ENC_A, CHANNEL_FRONT_RIGHT_ENC_B, false);
        driveRearLeft = new VictorSpeed(CHANNEL_REAR_LEFT, CHANNEL_REAR_LEFT_ENC_A, CHANNEL_REAR_LEFT_ENC_B, true);
        dummyRLeft = new VictorSpeed(CHANNEL_REAR_LEFT_ENC_A, CHANNEL_REAR_LEFT_ENC_B, true);
        driveRearRight = new VictorSpeed(CHANNEL_REAR_RIGHT, CHANNEL_REAR_RIGHT_ENC_A, CHANNEL_REAR_RIGHT_ENC_B, true);
        dummyRRight = new VictorSpeed(CHANNEL_REAR_RIGHT_ENC_A, CHANNEL_REAR_RIGHT_ENC_B, true);

        leftStick = new Joystick(PORT_LEFT_STICK);
        rightStick = new Joystick(PORT_RIGHT_STICK);
        armStick = new Joystick(PORT_ARM_STICK);

        updatePID();

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

//        auton.run(oi.getAutonSetting());
        auton.run(1);
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);
            
        updatePID();

        drive.updateWeightGains();

        driveFrontLeft.e.reset();
        driveFrontRight.e.reset();
        driveRearLeft.e.reset();
        driveRearRight.e.reset();

        while (isEnabled() && isOperatorControl()) {
            drive.mecanumDrive_Cartesian(
                    leftStick.getX(), // X translation (horizontal strafe)
                    leftStick.getY(), // Y translation (straight forward)
                    rightStick.getX(), // rotation (clockwise?)
                    0,                 // use gyro for field-oriented drive
                    true);


            // Wrist servo
            if (armStick.getRawButton(6))
                arm.wrist.set(0);
            else if (armStick.getRawButton(7))
                arm.wrist.set(1);

            // Arm control by OI
            if (oi.isHeightButtonPressed()) {
                threadend(positionController);
                positionController = new ArmController(this, oi.getHeightButton(), oi.getTrimAmount(0.5));
                positionController.start();
                wasArmControlled = true;
            } else {
                arm.rotate(armStick.getY());
            }

/*
            if (armStick.getRawButton(11)){
                if(!wasArmControlled){
                    threadend(positionController);
                    positionController = new ArmController(Arm.POT_MIDDLE_TOP, this);
                    positionController.start();
                    wasArmControlled = true;
                }

            } else if (armStick.getRawButton(10)) {
                if (!wasArmControlled) {
                    threadend(positionController);
                    positionController = new ArmController(Arm.POT_MIDDLE_MIDDLE, this);
                    positionController.start();
                    wasArmControlled = true;
                }
            } else if (armStick.getRawButton(9)) {
                if (!wasArmControlled) {
                    threadend(positionController);
                    positionController = new ArmController(Arm.POT_MIDDLE_BOTTOM, this);
                    positionController.start();
                    wasArmControlled = true;
                }

            } else if (armStick.getRawButton(8)) {
                threadend(positionController);
                wasArmControlled=false;
                System.out.println("Arm position" + arm.getPosition());
            }else {
                threadend(positionController);
                wasArmControlled=false;
                arm.rotate(armStick.getY());
            } */
            
            // Grabber control
            if (armStick.getTrigger())
                grabber.in();
            else if (armStick.getRawButton(2))
                grabber.out();
            else if (armStick.getRawButton(4))
                grabber.rotateUp();
            else if (armStick.getRawButton(5))
                grabber.rotateDown();
            else
                grabber.stop();
        }
    }

    /**
     * update PID values.  uses a text file drive_PID_values.txt that must be
     * uploaded to the cRIO via ftp://10.6.94.2/ in the root directory.
     */
    public void updatePID() {
        double drivePID[];

        try {
            drivePID = FileIO.getArray("drive_PID_values.txt");
        }
        catch (Exception e) {
            e.printStackTrace();
            drivePID = new double[3];
            drivePID[0] = SPEED_P;
            drivePID[1] = SPEED_I;
            drivePID[2] = SPEED_D;
        }

        try {
            driveFrontLeft.c.disable();
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
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void threadend(ArmController elliot){
        if(elliot!=null)
                elliot.end();
    }


    
}
