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

    // Set to true when debugging; it will print out exception stack traces
    // Set to false for competition: log exceptions to a file on the cRIO
    static final boolean DEBUG_MODE = false;

    // Robot hardware
    VictorSpeed driveFrontLeft, driveRearLeft, driveFrontRight, driveRearRight;
    VictorSpeed dummyFLeft, dummyRLeft, dummyFRight, dummyRRight;
    DriveTrain drive;

    Arm arm;
    Grabber grabber;
    Minibot minibot;
    DigitalInput leftSensor, middleSensor, rightSensor;

    Relay acquiredLight;

    // Driver controls
    Joystick leftStick;
    Joystick rightStick;
    Joystick armStick;

    // Operator interface
    OperatorInterface oi;

    // Autonomous class
    Autonomous auton;
    
    boolean wasArmControlled = false;
    ArmController positionController;

    /**
     * DESdroid constructor.
     */
    public DESdroid() {
        try {
            oi = new OperatorInterface();

            arm = new Arm(this);
            grabber = new Grabber();
            minibot = new Minibot();

            acquiredLight = new Relay(TUBE_ACQUIRED_LIGHT);
            acquiredLight.setDirection(Relay.Direction.kForward);

            leftSensor = new DigitalInput(LINE_SENSOR_LEFT_CHANNEL);
            middleSensor = new DigitalInput(LINE_SENSOR_MIDDLE_CHANNEL);
            rightSensor = new DigitalInput(LINE_SENSOR_RIGHT_CHANNEL);

            // Do NOT change the order of these constructors!
            driveFrontLeft = new VictorSpeed(CHANNEL_FRONT_LEFT, CHANNEL_FRONT_LEFT_ENC_A, CHANNEL_FRONT_LEFT_ENC_B, true);
            dummyFLeft = new VictorSpeed(CHANNEL_FRONT_LEFT_ENC_A, CHANNEL_FRONT_LEFT_ENC_B, true);
            driveFrontRight = new VictorSpeed(CHANNEL_FRONT_RIGHT, CHANNEL_FRONT_RIGHT_ENC_A, CHANNEL_FRONT_RIGHT_ENC_B, false);
            dummyFRight = new VictorSpeed(CHANNEL_FRONT_RIGHT_ENC_A, CHANNEL_FRONT_RIGHT_ENC_B, false);
            driveRearLeft = new VictorSpeed(CHANNEL_REAR_LEFT, CHANNEL_REAR_LEFT_ENC_A, CHANNEL_REAR_LEFT_ENC_B, true);
            dummyRLeft = new VictorSpeed(CHANNEL_REAR_LEFT_ENC_A, CHANNEL_REAR_LEFT_ENC_B, true);
            dummyRRight = new VictorSpeed(CHANNEL_REAR_RIGHT_ENC_A, CHANNEL_REAR_RIGHT_ENC_B, true);
            driveRearRight = new VictorSpeed(CHANNEL_REAR_RIGHT, CHANNEL_REAR_RIGHT_ENC_A, CHANNEL_REAR_RIGHT_ENC_B, true);

            leftStick = new Joystick(PORT_LEFT_STICK);
            rightStick = new Joystick(PORT_RIGHT_STICK);
            armStick = new Joystick(PORT_ARM_STICK);

            driveFrontLeft.c.disable();
            driveFrontRight.c.disable();
            driveRearLeft.c.disable();
            driveRearRight.c.disable();

            driveFrontLeft.c.setPID(SPEED_P, SPEED_I, SPEED_D);
            driveFrontRight.c.setPID(SPEED_P, SPEED_I, SPEED_D);
            driveRearLeft.c.setPID(SPEED_P, SPEED_I, SPEED_D);
            driveRearRight.c.setPID(SPEED_P, SPEED_I, SPEED_D);

            driveFrontLeft.c.enable();
            driveFrontRight.c.enable();
            driveRearLeft.c.enable();
            driveRearRight.c.enable();

            drive = new DriveTrain(driveFrontLeft,
                    driveRearLeft,
                    driveFrontRight,
                    driveRearRight);

            auton = new Autonomous(this);
        } catch (Exception e) {
            FileIO.reportError("DESDROID", e, "Uncaught exception in DESdroid constructor.");
        }
    }

    /**
     * Turns off OI lights when the robot is disabled.
     */
    public void disabled() {
        try {
            oi.lightsOff();
            oi.setStuffsBrokenLED(false);
        } catch (Exception e) {
            FileIO.reportError("DESDROID", e, "Uncaught exception in DESdroid disabled() method.");
        }
    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
        try {
            getWatchdog().setEnabled(false);

            auton.run(oi.getAutonSetting());
        } catch (Exception e) {
            FileIO.reportError("DESDROID", e, "Uncaught exception in DESdroid autonomous() method.");
        }
    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        try {
            getWatchdog().setEnabled(false);
            resetEncoders();

            oi.lightsOff();
            oi.setStuffsBrokenLED(false);

            boolean isMinibotDeployed = false;
            minibot.reset();

            while (isEnabled() && isOperatorControl()) {
                drive.mecanumDrive_Cartesian(
                        leftStick.getX(), // X translation (horizontal strafe)
                        leftStick.getY(), // Y translation (straight forward)
                        rightStick.getX(), // rotation (getX() > 0 is clockwise)
                        0, // use gyro for field-oriented drive
                        true);            // deadband the inputs?


                // Arm control by OI
                if (oi.isHeightButtonPressed()) {
                    if (!wasArmControlled) {
                        threadEnd(positionController);
                        positionController = new ArmController(this, oi.getHeightButton(), oi.getTrimAmount(0.5));
                        positionController.start();
                        wasArmControlled = true;
                    }
                } else {
                    arm.rotate(armStick.getY());
                    wasArmControlled = false;
                }

                // Grabber control
                if (armStick.getTrigger()) {
                    grabber.in();
                } else if (armStick.getRawButton(2)) {
                    grabber.out();
                } else if (armStick.getRawButton(4)) {
                    grabber.rotateUp();
                } else if (armStick.getRawButton(5)) {
                    grabber.rotateDown();
                } else {
                    grabber.stop();
                }

                if (oi.getWingSwitch()) {
                    minibot.spreadWings();
                }

                if (oi.getMinibotSwitch()) {
                    minibot.debroy();
                    isMinibotDeployed = true;
                }

                if (isMinibotDeployed) {
                    minibot.runMinibotIfReady();
                }

                updateButtonLights();

                // Turn on light when tube is in the grabber
                if (grabber.getLimitSwitch()) {
                    acquiredLight.set(Relay.Value.kOn);
                } else {
                    acquiredLight.set(Relay.Value.kOff);
                }

            }
            FileIO.writeLog();  //Save the log string
        } catch (Exception e) {
            FileIO.reportError("DESDROID", e, "Uncaught exception in DESdroid operatorControl() method.");
        }
    }


    public void resetEncoders() {
        driveFrontLeft.e.reset();
        driveFrontRight.e.reset();
        driveRearLeft.e.reset();
        driveRearRight.e.reset();
    }

    public static void threadEnd(ArmController elliot) {
        if(elliot != null)
            elliot.end();
    }

    public double getAvgDistance() {
        double avg = 0;
        avg += driveFrontLeft.e.getDistance();
        avg -= driveFrontRight.e.getDistance();
        avg += driveRearLeft.e.getDistance();
        avg -= driveRearRight.e.getDistance();
        avg /= 4.0;                   // Calcuating the average
        avg *= Math.PI;               // Multiply distance by pi, in preparation for calculating
                                      // the circumference

        avg /= 10.0;                  // Multiplies by 6, the wheel diameter, then divides by 60
                                      // seconds a minute

        return avg;
    }

    /**
     * Lights a height button on the OI depending on the proximity of the arm to a height position.
     */
    public void updateButtonLights() {
        double currentPosition = arm.getPosition();
        
        if (Math.abs(currentPosition - Arm.POT_SIDE_BOTTOM) < 0.1)
            oi.setLight(SIDE_LOWER_LIGHT);
        else if(Math.abs(currentPosition - Arm.POT_SIDE_MIDDLE) < 0.1)
            oi.setLight(SIDE_MIDDLE_LIGHT);
        else if(Math.abs(currentPosition - Arm.POT_SIDE_TOP) < 0.1)
            oi.setLight(SIDE_UPPER_LIGHT);
        else if(Math.abs(currentPosition - Arm.POT_MIDDLE_BOTTOM) < 0.1)
            oi.setLight(CENTER_LOWER_LIGHT);
        else if(Math.abs(currentPosition - Arm.POT_MIDDLE_MIDDLE) < 0.1)
            oi.setLight(CENTER_MIDDLE_LIGHT);
        else if(Math.abs(currentPosition - Arm.POT_MIDDLE_TOP) < 0.1)
            oi.setLight(CENTER_UPPER_LIGHT);
        else if(Math.abs(currentPosition - Arm.POT_FEEDER_LEVEL) < 0.1)
            oi.setLight(FEEDER_LEVEL_LIGHT);
        else if(Math.abs(currentPosition - Arm.POT_GROUND_LEVEL) < 0.1)
            oi.setLight(GROUND_LEVEL_LIGHT);
        else
            oi.lightsOff();
    }
}
