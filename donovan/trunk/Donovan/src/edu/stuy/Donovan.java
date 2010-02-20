/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.stuy;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.DriverStationEnhancedIO.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Donovan extends SimpleRobot implements Ports, ThreeLaws {

    boolean lastTop;
    Joystick lstick;
    Joystick rstick;
    Joystick shootStick;
    DonovanDriveTrain dt;
    Acquirer roller;
    Kicker kicker;
    Hanger hanger;
   
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
        hanger = new Hanger(WINCH_CHANNEL, A_FRAME_CHANNEL);
       

        gyro = new Gyro(GYRO_CHANNEL);
        gyro.setSensitivity(-0.007); //this is also done in DonCircleTracker
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
            auton.runSettingNum(2);
            // getWatchdog().feed();
        }
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);


        lastTop = false;
        while (isOperatorControl() && isEnabled()) {
            //System.out.println("left encoder: " + dt.getLeftEnc() + " right encoder: " + dt.getRightEnc());

            tracker.doCamera();


            /************ Driver Controls **************/

            dt.tankDrive(lstick, rstick);

            if (lstick.getTrigger()) {
                dt.setLow(); // to low gear
            }
            if (rstick.getTrigger()) {
                dt.setHigh(); //to high gear
            }

            if (!lstick.getRawButton(3) && !rstick.getRawButton(3)) {
                if (lastTop) {
                    tracker.stopAligning();
                }
                lastTop = false;
                dt.tankDrive(lstick, rstick);
            } else {
                if (!lastTop) {
                    tracker.startAligning();
                }
                lastTop = true;
            }

            /*
            if (lstick.getRawButton(6) || rstick.getRawButton(6) || shootStick.getRawButton(6)) {
                oi.testLEDs();
            } else {
                oi.resetLEDs();
            }

            if (lstick.getRawButton(11) || rstick.getRawButton(11) || shootStick.getRawButton(11)) {
                dt.resetEncoders();
           }
            */



            /************ Shooter Controls **************/

            if (shootStick.getRawButton(4)) {
                
                hanger.startWinch();
            }
            else if (shootStick.getRawButton(5)){
               
                hanger.reverseWinch();
            }
            else {
               
                hanger.stopWinch();
            }

            if (shootStick.getTrigger()) {
                kicker.shoot();
            }
            
            if (shootStick.getRawButton(2)){
                hanger.deployAFrame();
            }

            if (shootStick.getRawButton(3)) {
                roller.start();
            } else {
                roller.stop();
            }




          


            if(shootStick.getRawButton(10)){
                kicker.stop();
            }


            /************ Panel Controls **************/

           //System.out.println("Binary switch: " + oi.getAutonSwitch());
          




           if (oi.getA_Frame()) {
               //System.out.println("Get a frame!");
                hanger.deployAFrame();
            }

            if (oi.getWench()) {
                //System.out.println("Get a wench!");
                hanger.startWinch();
            } else {
               
              hanger.stopWinch();
            }

            if (oi.getKick()) {
                //System.out.println("get a kick!");
                kicker.shoot();
            }

            if (oi.getCock()) {
               //System.out.println("get a cock!");
                 kicker.cock();
            }

            if (oi.getAcquirerForward()) {
               //System.out.println("acquirer forward!");
                 roller.start();
            } else {
                roller.stop();
            }
            
            if (oi.getAcquirerReverse()) {
               //System.out.println("acquirer in reverse!");
                 roller.startReverse();
            } else {
                roller.stop();
            }
            updateDashboard();
        }
    }



    public void doNoHarm() {
    }

    public void obeyOrders() {
    }

    public void updateDashboard(){
//        Dashboard lowDashData = DriverStation.getInstance().getDashboardPackerLow();
//        lowDashData.addBoolean(kicker.getCockStatus());
//        lowDashData.addBoolean(dt.getGear());
//        lowDashData.commit();
    }
}
