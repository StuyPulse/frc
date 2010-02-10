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


//TODO: Keep putting gyro, pid and timer(?) stuff back in!


/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Donovan extends SimpleRobot implements Ports {
    boolean lastTrig;
    Joystick lstick;
    Joystick rstick;
    Joystick shootStick;
    DonovanDriveTrain dt;
    Acquirer roller;
    Kicker kicker;
    Gyro gyro;
    //Move move;  //Move class has been deprecated, now in DonovanDriveTrain.java
    AxisCamera cam;
    DonTrackerDashboard trackerDashboard = new DonTrackerDashboard();
    double kScoreThreshold = .01;
	
    PIDController turnController;
	
    Autonomous auton;
    BinarySwitch autonSwitch;
	
    DriverStationLCD lcd;
	
    
	
    public Donovan(){
        lstick = new Joystick(LSTICK_PORT); //usb port
        rstick = new Joystick(RSTICK_PORT); //usb port
        shootStick = new Joystick(SHOOTSTICK_PORT); //usb port
        dt = new DonovanDriveTrain(DRIVE_1_CHANNEL,DRIVE_2_CHANNEL/*,DRIVE_3_CHANNEL,DRIVE_4_CHANNEL*/); //digital channel
        roller = new Acquirer(ACQUIRER_CHANNEL); //digital channel
        kicker = new Kicker(KICKMOTOR_CHANNEL); //digital channel
        gyro = new Gyro(GYRO_CHANNEL);
        gyro.setSensitivity(.007);
        //move = new Move(this);
		
        cam = AxisCamera.getInstance();// getting instance
        cam.writeResolution(AxisCamera.ResolutionT.k640x480);
        cam.writeBrightness(0);
		
        auton = new Autonomous(this);
        autonSwitch = new BinarySwitch();
		
        lcd = DriverStationLCD.getInstance();
		
        
		
        turnController = new PIDController(.08, 0.0, 0.5, gyro, new PIDOutput() {
			public void pidWrite(double output) {
				dt.arcadeDrive(0, output); //CHANGE TO TANK DRIVE
			}
		}, .005);
		
        turnController.setInputRange(-360.0, 360.0);
        turnController.setTolerance(1 / 90. * 100);
        //turnController.disable();
        
        dt.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        dt.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
    }
	
    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
        getWatchdog().setEnabled(false);
		
        lcd.println(DriverStationLCD.Line.kUser3, 1, "Auton Mode: " + autonSwitch.getAutonSwitch());
        lcd.updateLCD();
        auton.runSettingNum(autonSwitch.getAutonSwitch());
        
    }
	
    /**
     * This function is called once each time the robot enters operator control.
     */
	
	
    public void operatorControl() {
        getWatchdog().setEnabled(false);
		//        getWatchdog().feed();
        lastTrig=false;
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
            if (!lstick.getTrigger()) {
				if (lastTrig)
					turnController.disable();
				lastTrig = false;
				dt.tankDrive(lstick,rstick);
			} else {
				if (!lastTrig) {
					turnController.enable();
					turnController.setSetpoint(gyro.pidGet());
				}
				lastTrig= true;
				doCamera();
				
			}
		}
    }
	
	
    public void doCamera(){
        try {
			if (cam.freshImage()&& turnController.onTarget()) {
				double gyroAngle = gyro.pidGet();
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
					trackerDashboard.updateVisionDashboard(0.0, gyro.getAngle(), 0.0, 0.0, newTargets);
				} else {
					//             System.out.println("It's a target! " + targets[0]);
					System.out.println("Target Angle: " + targets[0].getHorizontalAngle());
					turnController.setSetpoint(gyroAngle + targets[0].getHorizontalAngle());
					trackerDashboard.updateVisionDashboard(0.0, gyro.getAngle(), 0.0, targets[0].m_xPos / targets[0].m_xMax, targets);
				}
			}
		} catch (NIVisionException ex) {
			ex.printStackTrace();
		} catch (AxisCameraException ex) {
			ex.printStackTrace();
		}
		//         System.out.println("Time : " + (Timer.getUsClock() - startTime) / 1000000.0);
		System.out.println("Gyro Angle: " + gyro.getAngle());
    }
}
