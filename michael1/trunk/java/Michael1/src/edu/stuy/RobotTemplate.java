/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.stuy;

import edu.wpi.first.wpilibj.*;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class RobotTemplate extends SimpleRobot {

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    //CONSTANTS
    //Driver Station
    final int LEFT_DRIVE_JOYSTICK = 1;
    final int RIGHT_DRIVE_JOYSTICK = 2;
    final int SHOOTER_JOYSTICK = 3;
//Digital Sidecar PWM (slot 4)
    final int LEFT_DRIVE_MOTOR = 1;
    final int RIGHT_DRIVE_MOTOR = 2;
    final int INTAKE_ROLLER = 4;
    final int SHOOTER_ROLLER = 3;
    final int SERVO1 = 9;
    final int SERVO2 = 10;
    final int CAM_HORIZONTAL = 11;
    final int CAM_VERTICAL = 10;
//Digital Sidecar DigIO (slot 4)
    final int ARIELS_LIGHT = 1;
    final int AUTON_SELECTOR_1 = 14;
    final int AUTON_SELECTOR_2 = 7;
    final int AUTON_SELECTOR_3 = 8;
    final int AUTON_SELECTOR_4 = 9;
    final int ALLIANCE_SELECTOR = 14;
//Analog Sensors
    final int ACCELEROMETER = 1;
    final int GYRO = 2;
    Joystick left_stick;
    Joystick right_stick;
    Joystick shooter_stick;
    DigitalInput alliance_selector;
    Victor intake;
    Victor shooter;
    Servo servo_1;
    Servo servo_2;
    DriverStation ds;
    RobotDrive robotDrive;
    DigitalOutput coast;
    Gyro gyro;
    // Michael1Camera cam;
    Timer time;

    public RobotTemplate() {
        // We're Alive!
        System.out.print("Hello!\n\n\n");

        // Driver's Station Inputs
        left_stick = new Joystick(LEFT_DRIVE_JOYSTICK);
        right_stick = new Joystick(RIGHT_DRIVE_JOYSTICK);
        shooter_stick = new Joystick(SHOOTER_JOYSTICK);

        // Robot Inputs
        //TODO just used in autonomous
        alliance_selector = new DigitalInput(4, ALLIANCE_SELECTOR);
        // Robot Outputs
        //ariels_light = new DigitalOutput(ARIELS_LIGHT);
        intake = new Victor(INTAKE_ROLLER);
        shooter = new Victor(SHOOTER_ROLLER);
        servo_1 = new Servo(SERVO1);
        servo_2 = new Servo(SERVO2);
        coast = new DigitalOutput(4, 6);
        coast.set(true);
        gyro = new Gyro(GYRO);
        gyro.setSensitivity(0.007);

        // Helper Objects
        robotDrive = new RobotDrive(LEFT_DRIVE_MOTOR, RIGHT_DRIVE_MOTOR);

        // cam = new Michael1Camera(false);

        ds = DriverStation.getInstance();

        // System-Wide timer. Never to be reset.
        time = new Timer();
        time.start();

        // WPILib crap
        getWatchdog().setExpiration(100);

    }

    public void autonomous() {
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {

        System.out.print("\n\n\tStart Teleop:\n\n");
        double oldTime = 0;
        ds.setDigitalOut(3, false);
        gyro.reset();

        while (isOperatorControl()) {
            double newTime = time.get();
            if (newTime - oldTime >= 0.1) {
                oldTime = newTime;
                System.out.println(gyro.getAngle());
            }

            //joystick motor control
            if (left_stick.getTrigger() || right_stick.getTrigger()) {
                robotDrive.tankDrive(left_stick, right_stick);
            } 
            /*
            else {
                double halfOfLeftStickY = (left_stick.getY() / 2);
                double halfOfRightStickY = (right_stick.getY() / 2);
                // dt.setMotors(-(float) halfOfLeftStickY, -(float) halfOfRightStickY);
                // not needed because we think FRC RobotDrive does this

            }
             */


            //brakes
            if (left_stick.getRawButton(2) || right_stick.getRawButton(2)) {
                coast.set(false);
            } else {
                coast.set(true);
            }

            //shooter
            if (shooter_stick.getTrigger() || shooter_stick.getRawButton(3)) {
                shooter.set(-0.75);
            } else {
                shooter.set(shooter_stick.getY() * 0.5);
            }

            /* OI switch box
             * Left 1u, 2d
             * mid  5u, 3d
             * rig	6u, 4d*/

            //intake
            if (ds.getDigitalIn(6) || (shooter.get()) > 0) {
                intake.set(1);
            } else if (ds.getDigitalIn(4)) {
                intake.set(-1);
            } else {
                intake.set(0);
            }

            //Servos
            if (ds.getDigitalIn(5)) {
                servo_1.set(0);
                servo_2.set(1);
            } else if (ds.getDigitalIn(3)) {
                servo_1.set(1);
                servo_2.set(0);
            } else {
                servo_1.set(1);
                servo_2.set(0);
            }
        }
    }
}

