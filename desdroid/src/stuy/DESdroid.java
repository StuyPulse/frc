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
    DriveTrain drive;
    // Driver controls
    Joystick leftStick, rightStick;
    // Autonomous class
    Autonomous auton;

    DESCircleTracker pegTracker;
    DESTrackerDashboard trackerDashboard;

    boolean isOn = false;

    public DESdroid() {
        try {
            driveFrontLeft = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_LEFT, CANJaguar.ControlMode.kSpeed);
            driveFrontRight = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_RIGHT, CANJaguar.ControlMode.kSpeed);
            driveRearLeft = new CANJaguar(DRIVE_CAN_DEVICE_REAR_LEFT, CANJaguar.ControlMode.kSpeed);
            driveRearRight = new CANJaguar(DRIVE_CAN_DEVICE_REAR_RIGHT, CANJaguar.ControlMode.kSpeed);

            driveFrontLeft.setSpeedReference(CANJaguar.SpeedReference.kQuadEncoder);
            driveFrontRight.setSpeedReference(CANJaguar.SpeedReference.kQuadEncoder);
            driveRearLeft.setSpeedReference(CANJaguar.SpeedReference.kQuadEncoder);
            driveRearRight.setSpeedReference(CANJaguar.SpeedReference.kQuadEncoder);

            driveFrontLeft.configEncoderCodesPerRev(ENCODER_CODES_PER_REV);
            driveFrontRight.configEncoderCodesPerRev(ENCODER_CODES_PER_REV);
            driveRearLeft.configEncoderCodesPerRev(ENCODER_CODES_PER_REV);
            driveRearRight.configEncoderCodesPerRev(ENCODER_CODES_PER_REV);

            updatePID();

            drive = new DriveTrain(driveFrontLeft,
                    driveRearLeft,
                    driveFrontRight,
                    driveRearRight);


            leftStick = new Joystick(PORT_ARM_STICK);
            rightStick = new Joystick(PORT_JOYSTICK);

            trackerDashboard = new DESTrackerDashboard(this);
            pegTracker = new DESCircleTracker(this);
        } catch (Exception e) {
            System.out.println(e);

        }

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
        getWatchdog().setEnabled(false);

        while (isEnabled() && isOperatorControl()) {
   
            // drive.tankDrive(gamepad, 2, gamepad, 4);
            //drive.mecanumDrive_Cartesian(leftStick.getX(), leftStick.getY(), rightStick.getX(), 0.0);


            // Place the robot centered in front of a target and record the xPos
            // value (press button 7 to find the target).  Since the camera is
            // off-center, this value must be determined experimentally.  Put it
            // into Constants.java as PID_SETPOINT.

            // Move the robot or the target, then press and hold button 10 to
            // align using PID feedback control (tune the PID gains as well).

            drive.mecanumDrive_Cartesian(leftStick.getX(), leftStick.getY(), rightStick.getX(), 0);
            
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
                pegTracker.halogen_a.set(Relay.Value.kOn);
            }
            else {
                pegTracker.halogen_a.set(Relay.Value.kOff);
            }
        }
    }

    // update PID values.  uses a text file drive_PID_values.txt that must be
    // uploaded to the cRIO via ftp://10.6.94.2/ in the root directory.
     public void updatePID() {
        double drivePID[];
        /*
         try {
              //  drivePID = FileIO.getArray("drive_PID_values.txt");
         }
        catch (Exception e) { 
         e.printStackTrace();
          * */

         drivePID = new double[3];
         drivePID[0] = 0.48;
         drivePID[1] = 0.005;
         drivePID[2] = 0.05;

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
