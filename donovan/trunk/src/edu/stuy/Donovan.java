/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package edu.stuy;


import edu.wpi.first.wpilibj.*;

import edu.wpi.first.wpilibj.camera.*;
import edu.wpi.first.wpilibj.image.*;


/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Donovan extends SimpleRobot {

    Joystick lstick;
    Joystick rstick;
    Joystick shootStick;
    DonovanDriveTrain dt;
    Acquirer roller;
    Kicker kicker;
    AxisCamera cam;
    DonTrackerDashboard trackerDashboard = new DonTrackerDashboard();
    double kScoreThreshold = .01;

    Autonomous auton;
    BinarySwitch autonSelect;

    


    public Donovan(){
        lstick = new Joystick(1); //usb port
        rstick = new Joystick(2); //usb port
        shootStick = new Joystick(3); //usb port
        dt = new DonovanDriveTrain(1,2,3,4); //digital channel
        roller = new Acquirer(5); //digital channel
        kicker = new Kicker(6); //digital channel
        
        cam = AxisCamera.getInstance();// getting instance
        cam.writeResolution(AxisCamera.ResolutionT.k640x480);
        cam.writeBrightness(0);

        dt.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        dt.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);

    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
        auton.runSettingNum(autonSelect.getAutonSwitch());

    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);
        while(isOperatorControl() && isEnabled()){
            dt.tankDrive(lstick, rstick);
            if(shootStick.getButton(Joystick.ButtonType.kTrigger)){
                kicker.shoot();
            }
            if(shootStick.getRawButton(1)){  //don't know which button this is
                roller.start();
            }
            else{
                roller.stop();
            }
            doCamera();
            
        }
    }

    public void doCamera(){
        try {
                if (cam.freshImage()) {// && turnController.onTarget()) {
                    ColorImage image = cam.getImage();
                    Thread.yield();
                    DonovanTarget[] targets = DonovanTarget.findCircularTargets(image);
                    Thread.yield();
                    image.free();
                    if (targets.length == 0 || targets[0].m_score < kScoreThreshold) {
                        System.out.println("No target found");
                        DonovanTarget[] newTargets = new DonovanTarget[targets.length + 1];
                        newTargets[0] = new DonovanTarget();
                        newTargets[0].m_majorRadius = 0;
                        newTargets[0].m_minorRadius = 0;
                        newTargets[0].m_score = 0;
                        for (int i = 0; i < targets.length; i++) {
                            newTargets[i + 1] = targets[i];
                        }
                        trackerDashboard.updateVisionDashboard(0.0, 0.0, 0.0, 0.0, newTargets);
                    } else {
                        System.out.println("It's a target! " + targets[0]);
                        System.out.println("Target Angle: " + targets[0].getHorizontalAngle());
                        //turnController.setSetpoint(gyroAngle + targets[0].getHorizontalAngle());
                        trackerDashboard.updateVisionDashboard(0.0, 0.0, 0.0, targets[0].m_xPos / targets[0].m_xMax, targets);
                    }
                }
            } catch (NIVisionException ex) {
                ex.printStackTrace();
            } catch (AxisCameraException ex) {
                ex.printStackTrace();
            }
    }
}
