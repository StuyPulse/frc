/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

package edu.stuy;


import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.Joystick;

import edu.wpi.first.wpilibj.Solenoid;

import edu.wpi.first.wpilibj.Watchdog;
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

    public Donovan(){
        lstick = new Joystick(1); //usb port
        rstick = new Joystick(2); //usb port
        shootStick = new Joystick(3); //usb port
        dt = new DonovanDriveTrain(1,2,3,4); //digital channel
        roller = new Acquirer(5); //digital channel
        kicker = new Kicker(6); //digital channel
    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
        
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(true);
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
            getWatchdog().feed();
        }
    }
}
