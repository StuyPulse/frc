/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.wpi.first.wpilibj.templates;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.camera.AxisCamera;



/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class RobotTest extends SimpleRobot {

    RobotDrive drivetrain;
    Joystick leftStick;
    Joystick rightStick;
    Joystick shooterStick;

    Victor intake;
    Victor shooter;

    

    //initialize for tankdrive
    public RobotTest() {
        System.out.println("we are alive");
        drivetrain  = new RobotDrive(1, 2);
        leftStick  = new Joystick(1);
        rightStick  = new Joystick(2);

        shooterStick = new Joystick(3);
        intake = new Victor(4);
        shooter = new Victor(3);
        AxisCamera.getInstance();


        drivetrain.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        drivetrain.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);


    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     * Drives in a square 4 times
     */
    public void autonomous() {
       System.out.println("autonomous");
     
       /*
        for (int i = 0; i < 4; i++) {
            drivetrain.drive(0.5, 0.0);   // drive 50% fwd 0% turn 
            Timer.delay(2.0);             // wait 2 seconds 
            drivetrain.drive(0.0, 0.75);  // drive 0% fwd, 75% turn 
        } 
        drivetrain.drive(0.0, 0.0);  // drive 0% forward, 0% turn
    */
    }

   void updateDashboard() {
        Dashboard lowDashData = DriverStation.getInstance().getDashboardPackerLow();
        lowDashData.addCluster();
        {
            lowDashData.addCluster();
            {     //analog modules
                lowDashData.addCluster();
                {
                    for (int i = 1; i <= 8; i++) {
                        lowDashData.addFloat((float) AnalogModule.getInstance(1).getAverageVoltage(i));
                    }
                }
                lowDashData.finalizeCluster();
                lowDashData.addCluster();
                {
                    for (int i = 1; i <= 8; i++) {
                        lowDashData.addFloat((float) AnalogModule.getInstance(2).getAverageVoltage(i));
                    }
                }
                lowDashData.finalizeCluster();
            }
            lowDashData.finalizeCluster();

            lowDashData.addCluster();
            { //digital modules
                lowDashData.addCluster();
                {
                    lowDashData.addCluster();
                    {
                        int module = 4;
                        lowDashData.addByte(DigitalModule.getInstance(module).getRelayForward());
                        lowDashData.addByte(DigitalModule.getInstance(module).getRelayForward());
                        lowDashData.addShort(DigitalModule.getInstance(module).getAllDIO());
                        lowDashData.addShort(DigitalModule.getInstance(module).getDIODirection());
                        lowDashData.addCluster();
                        {
                            for (int i = 1; i <= 10; i++) {
                                lowDashData.addByte((byte) DigitalModule.getInstance(module).getPWM(i));
                            }
                        }
                        lowDashData.finalizeCluster();
                    }
                    lowDashData.finalizeCluster();
                }
                lowDashData.finalizeCluster();

                lowDashData.addCluster();
                {
                    lowDashData.addCluster();
                    {
                        int module = 6;
                        lowDashData.addByte(DigitalModule.getInstance(module).getRelayForward());
                        lowDashData.addByte(DigitalModule.getInstance(module).getRelayReverse());
                        lowDashData.addShort(DigitalModule.getInstance(module).getAllDIO());
                        lowDashData.addShort(DigitalModule.getInstance(module).getDIODirection());
                        lowDashData.addCluster();
                        {
                            for (int i = 1; i <= 10; i++) {
                                lowDashData.addByte((byte) DigitalModule.getInstance(module).getPWM(i));
                            }
                        }
                        lowDashData.finalizeCluster();
                    }
                    lowDashData.finalizeCluster();
                }
                lowDashData.finalizeCluster();

            }
            lowDashData.finalizeCluster();

            lowDashData.addByte(Solenoid.getAll());
        }
        lowDashData.finalizeCluster();
        lowDashData.commit();

    }


    /**
     * This function is called once each time the robot enters operator control.
         */
    public void operatorControl() {

        getWatchdog().setEnabled(false);

        
        //updateDashboard();

        System.out.println("Teleop");

        AxisCamera cam = AxisCamera.getInstance();
        //cam.writeCompression(0);
        cam.writeBrightness(0);
        cam.writeResolution(AxisCamera.ResolutionT.k160x120);
        Timer.delay(3.0);

        while(true && isOperatorControl() && isEnabled()){
            drivetrain.tankDrive(leftStick, rightStick);
            if(shooterStick.getTrigger()){
                intake.set(1);
            }
            else {
                intake.set(0);
            }
            if(shooterStick.getRawButton(3)){
                shooter.set(-1);
            }
            else {
                shooter.set(0);
            }
            
            Timer.delay(0.010); //in sample code - for update speed of jaguar?
        }
        }
    }

