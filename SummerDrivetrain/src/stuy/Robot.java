/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package stuy;

import edu.wpi.first.wpilibj.SimpleRobot;
import edu.wpi.first.wpilibj.CANJaguar;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.Joystick;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class Robot extends SimpleRobot implements Constants {

    CANJaguar frontLeftMotor, rearLeftMotor, frontRightMotor, rearRightMotor;
    RobotDrive drivetrain;
    Joystick gamepad;

    public Robot() {
        try {
            frontLeftMotor = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_LEFT);
            rearLeftMotor = new CANJaguar(DRIVE_CAN_DEVICE_REAR_LEFT);
            frontRightMotor = new CANJaguar(DRIVE_CAN_DEVICE_FRONT_RIGHT);
            rearRightMotor = new CANJaguar(DRIVE_CAN_DEVICE_REAR_RIGHT);
        }
        catch (Exception e) {
        }

        drivetrain = new RobotDrive(frontLeftMotor, rearLeftMotor, frontRightMotor, rearRightMotor);

        // TODO: Check for inverted motors.
        drivetrain.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, false);
        drivetrain.setInvertedMotor(RobotDrive.MotorType.kRearLeft, false);
        drivetrain.setInvertedMotor(RobotDrive.MotorType.kFrontRight, false);
        drivetrain.setInvertedMotor(RobotDrive.MotorType.kRearRight, false);

        gamepad = new Joystick(PORT_GAMEPAD);
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
            drivetrain.tankDrive(gamepad, 2, gamepad, 4);
        }
    }
}
