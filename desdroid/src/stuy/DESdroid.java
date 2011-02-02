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

    DESTrackerDashboard trackerDashboard;
    DESCircleTracker pegTracker;

    // Driver controls
    Joystick gamepad;
    Joystick leftStick;
    Joystick rightStick;

    // Digital I/O


    // Autonomous class
    Autonomous auton;

    boolean isOn = false;


    public DESdroid() {
        
        try {
            driveFrontLeft  = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_LEFT);
            driveFrontRight = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_RIGHT);
            driveRearLeft   = new CANJaguar(DRIVE_CAN_DEVICE_REAR_LEFT);
            driveRearRight  = new CANJaguar(DRIVE_CAN_DEVICE_REAR_RIGHT);
        }
        catch (Exception e) {
            System.out.println(e);

        }

        drive = new RobotDrive(driveFrontLeft,
                               driveRearLeft,
                               driveFrontRight,
                               driveRearRight);

       



        leftStick = new Joystick(PORT_ARM_STICK);
        rightStick = new Joystick(PORT_JOYSTICK);
        
        trackerDashboard = new DESTrackerDashboard(this);
        pegTracker = new DESCircleTracker(this);




    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
	System.out.println("Autonomous");
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);

        while (isEnabled() && isOperatorControl()) {
   
            // drive.tankDrive(gamepad, 2, gamepad, 4);
            drive.mecanumDrive_Cartesian(leftStick.getX(), leftStick.getY(), rightStick.getX(), 0.0);


            // Place the robot centered in front of a target and record the xPos
            // value (press button 7 to find the target).  Since the camera is
            // off-center, this value must be determined experimentally.  Put it
            // into Constants.java as PID_SETPOINT.

            // Move the robot or the target, then press and hold button 10 to
            // align using PID feedback control (tune the PID gains as well).
            
            if (leftStick.getRawButton(7) && !isOn) {
                System.out.println("track called");
                pegTracker.doCamera();
                isOn = true;
            }
            
            if(leftStick.getRawButton(9)) {
                isOn = false;
            }
            
            if (leftStick.getRawButton(10)) { //button choice?
                if (!isOn) {
                    pegTracker.startAligning();
                    isOn = true;
                }
                pegTracker.doCamera();
            }
            else {
                pegTracker.stopAligning();
                isOn = false;
            }

            if (leftStick.getTrigger()) {
                pegTracker.halogen_a.set(true);
                pegTracker.halogen_b.set(true);
            }
            else {
                pegTracker.halogen_a.set(false);
                pegTracker.halogen_b.set(false);
            }
        }
    }
}
