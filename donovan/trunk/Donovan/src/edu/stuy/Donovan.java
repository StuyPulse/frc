/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.stuy;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.DriverStationEnhancedIO.EnhancedIOException;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Donovan extends SimpleRobot implements Ports, ThreeLaws {

    boolean lastTrig;
    Joystick lstick;
    Joystick rstick;
    Joystick shootStick;
    DonovanDriveTrain dt;
    Acquirer roller;
    Kicker kicker;
    Gyro gyro;
    DonTrackerDashboard trackerDashboard;
    DonCircleTracker tracker;
    DonovanOI oi;
    Autonomous auton;
    DriverStationLCD lcd;

    public Donovan() {
        lstick = new Joystick(LSTICK_PORT); //usb port
        rstick = new Joystick(RSTICK_PORT); //usb port
        shootStick = new Joystick(SHOOTSTICK_PORT); //usb port
        dt = new DonovanDriveTrain(DRIVE_1_CHANNEL, DRIVE_2_CHANNEL, DRIVE_3_CHANNEL, DRIVE_4_CHANNEL); //digital channelss
        roller = new Acquirer(ACQUIRER_CHANNEL); //digital channel
        kicker = new Kicker(KICKMOTOR_CHANNEL, this); //digital channel
        gyro = new Gyro(GYRO_CHANNEL);
        gyro.setSensitivity(.007);
        auton = new Autonomous(this);

        lcd = DriverStationLCD.getInstance();
        oi = new DonovanOI(this);
        trackerDashboard = new DonTrackerDashboard();
        tracker = new DonCircleTracker(this);

//        dt.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
//        dt.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
//        dt.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
//        dt.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);

        /*
         * Default to low, so that we're in a consistent state
         */

        if (dt.shifterLeft.get() == 1) {
            dt.shifterLeft.set(0);
            dt.shifterRight.set(0);
        }


    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
        getWatchdog().setEnabled(false);
        //getWatchdog().setExpiration(15);
        if (isAutonomous() && isEnabled()) {
            auton.runSettingNum(oi.getAutonSwitch());
            // getWatchdog().feed();
        }
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);


        lastTrig = false;
        while (isOperatorControl() && isEnabled()) {
            System.out.println("left encoder: " + dt.getLeftEnc() + " right encoder: " + dt.getRightEnc());


            //controls subject to change
            roller.set(shootStick.getY());
            dt.tankDrive(lstick, rstick);
        /*    if (lstick.getRawButton(6) || rstick.getRawButton(6) || shootStick.getRawButton(6)){
                oi.testLEDs();
            }
            else {
                oi.resetLEDs();
            } */
            if (lstick.getRawButton(11) || rstick.getRawButton(11) || shootStick.getRawButton(11)) {
                dt.resetEncoders();
            }
            if (shootStick.getButton(Joystick.ButtonType.kTrigger)) {
                kicker.runKicker();
            } else {
                kicker.stop();
            }

            if (lstick.getTrigger()) {
                dt.setLow();
            }
            if (rstick.getTrigger()) {
                dt.setHigh();
            }
            if (shootStick.getRawButton(2)) {
                kicker.stop();
            }


            //                roller.stop();
            //            }
            if (oi.getA_Frame()) {
                oi.deployA_Frame();
            }

            if (oi.getAWench()) {
                oi.deployAWench();
            }

            if (oi.getAKick()) {
                oi.deployAKick();
            }
            if (oi.getACock()){
                oi.deployACock();
            }
            if (oi.getAcquirerForward()){
                oi.deployAcquirerForward();
            }
            else {
                roller.stop();
            }
            if (oi.getAcquirerReverse()) {
                oi.deployAcquirerReverse();
            }
            else {
                roller.stop();
            }






            if (!lstick.getTrigger() && !rstick.getTrigger()) {
                if (lastTrig) {
                    tracker.stopAligning();
                }
                lastTrig = false;
                dt.tankDrive(lstick, rstick);
            } else {
                if (!lastTrig) {
                    tracker.startAligning();
                }
                lastTrig = true;
            }
            tracker.doCamera();

        }

    }
    public void doNoHarm() {
        
    }
    public void obeyOrders() {
        
    }
}
