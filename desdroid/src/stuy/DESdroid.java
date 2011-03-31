package stuy;
/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.camera.AxisCamera;

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
    
    DriveTrain drive;

    Arm arm;
    Grabber grabber;
    Minibot minibot;
    DigitalInput leftSensor, middleSensor, rightSensor;
    VictorSpeed driveFrontLeft, dummyFLeft, driveFrontRight, dummyFRight, driveRearLeft, dummyRLeft, dummyRRight, driveRearRight;

    Relay acquiredLight;

    // Driver controls
    Joystick leftStick;
    Joystick rightStick;
    Joystick armStick;

    // Operator interface
    OperatorInterface oi;

    AxisCamera cam;

    // Autonomous class
    Autonomous auton;
    
    boolean wasArmControlled = false;
    ArmController positionController;

//    DashboardUpdater dashboard;

    /**
     * DESdroid constructor.
     */
    public DESdroid() {
        oi = new OperatorInterface();

        arm = new Arm(this);
        grabber = new Grabber();
        minibot = new Minibot();

        acquiredLight = new Relay(TUBE_ACQUIRED_LIGHT);
        acquiredLight.setDirection(Relay.Direction.kForward);

        leftSensor = new DigitalInput(LINE_SENSOR_LEFT_CHANNEL);
        middleSensor = new DigitalInput(LINE_SENSOR_MIDDLE_CHANNEL);
        rightSensor = new DigitalInput(LINE_SENSOR_RIGHT_CHANNEL);

        leftStick = new Joystick(PORT_LEFT_STICK);
        rightStick = new Joystick(PORT_RIGHT_STICK);
        armStick = new Joystick(PORT_ARM_STICK);


        // Do NOT change the order of these constructors!
        driveFrontLeft = new VictorSpeed(CHANNEL_FRONT_LEFT, CHANNEL_FRONT_LEFT_ENC_A, CHANNEL_FRONT_LEFT_ENC_B, true);
        dummyFLeft = new VictorSpeed(CHANNEL_FRONT_LEFT_ENC_A, CHANNEL_FRONT_LEFT_ENC_B, true);
        driveFrontRight = new VictorSpeed(CHANNEL_FRONT_RIGHT, CHANNEL_FRONT_RIGHT_ENC_A, CHANNEL_FRONT_RIGHT_ENC_B, false);
        dummyFRight = new VictorSpeed(CHANNEL_FRONT_RIGHT_ENC_A, CHANNEL_FRONT_RIGHT_ENC_B, false);
        driveRearLeft = new VictorSpeed(CHANNEL_REAR_LEFT, CHANNEL_REAR_LEFT_ENC_A, CHANNEL_REAR_LEFT_ENC_B, true);
        dummyRLeft = new VictorSpeed(CHANNEL_REAR_LEFT_ENC_A, CHANNEL_REAR_LEFT_ENC_B, true);
        dummyRRight = new VictorSpeed(CHANNEL_REAR_RIGHT_ENC_A, CHANNEL_REAR_RIGHT_ENC_B, true);
        driveRearRight = new VictorSpeed(CHANNEL_REAR_RIGHT, CHANNEL_REAR_RIGHT_ENC_A, CHANNEL_REAR_RIGHT_ENC_B, true);

        drive = new DriveTrain(driveFrontLeft, driveRearLeft, driveFrontRight, driveRearRight);

        drive.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);

        cam = AxisCamera.getInstance();
        cam.writeResolution(AxisCamera.ResolutionT.k320x240);

        auton = new Autonomous(this);

//        dashboard = new DashboardUpdater(this);
    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
        getWatchdog().setEnabled(false);

        minibot.reset();
            auton.run(oi.getAutonSetting());

    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);
        drive.resetEncoders();

        oi.lightsOff();
        oi.setStuffsBrokenLED(false);

        boolean isMinibotDeployed = false;
        minibot.reset();

        boolean wingsSpread = false;
        boolean minibotMode = false;
        boolean isRetracting = false;

        double minibotTimer = 0;

        while (isEnabled() && isOperatorControl()) {
            minibotMode = leftStick.getTrigger() && rightStick.getTrigger();

            if (minibotMode) {
                drive.mecanumDrive_Cartesian(
                        -leftStick.getX() * 0.3125, // X translation (horizontal strafe)
                        -leftStick.getY() * 0.3125, // Y translation (straight forward)
                        rightStick.getX() * 0.3125, // rotation (getX() > 0 is clockwise)
                        0, // use gyro for field-oriented drive
                        true);            // deadband the inputs?
            }
            else {
                drive.mecanumDrive_Cartesian(
                        leftStick.getX(), // X translation (horizontal strafe)
                        leftStick.getY(), // Y translation (straight forward)
                        rightStick.getX(), // rotation (getX() > 0 is clockwise)
                        0, // use gyro for field-oriented drive
                        true);            // deadband the inputs?
            }


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
            if (armStick.getTrigger() && !grabber.getLimitSwitch()) {
                grabber.in();
            } else if (armStick.getRawButton(2)) {
                grabber.out();
            } else if (armStick.getRawButton(4)) {
                grabber.rotateUp(false);
            } else if (armStick.getRawButton(5)) {
                grabber.rotateDown(false);
            } else {
                grabber.stop();
            }

            if (oi.getWingSwitch()) {
                minibot.spreadWings();
                wingsSpread = true;
            }

            if (oi.getMinibotSwitch() && wingsSpread) {
                if (DEBUG_MODE)
                    System.out.println("Got OI minibot switch.");
                minibot.deploy();
                isMinibotDeployed = true;
            }

            //System.out.println("Tray limit switch: " + minibot.trayLimitSwitch.get() + " " + minibot.poleContactSwitch.get());

            //System.out.println(!minibot.trayLimitSwitch.get() + " " + !minibot.poleContactSwitch.get());

            if (isMinibotDeployed) {
                minibot.checkTrayLimitSwitch();
                if (oi.getExtraButton() && !isRetracting) {
                    minibotTimer = Timer.getFPGATimestamp();
                    minibot.runTrayMotor(-1);
                    isRetracting = true;
                }
            }

            if (minibotTimer > 0 && Timer.getFPGATimestamp() - minibotTimer > .5) {
                minibot.stopTrayMotor();
                minibotTimer = 0;
                isRetracting = false;
            }

            updateButtonLights();

            // Turn on light when tube is in the grabber
            if (grabber.getLimitSwitch() || !minibot.drawbridgeSwitch.get()) {
                acquiredLight.set(Relay.Value.kOn);
            }
            else {
                acquiredLight.set(Relay.Value.kOff);
            }

            // Continuously open wrist latch in case of failure during autonomous
            arm.wrist.set(1);


            if (leftStick.getTrigger() && DEBUG_MODE) {
                System.out.println(arm.getPosition());
            }

            if (rightStick.getTrigger() && DEBUG_MODE) {
                System.out.println(drive.getAvgDistance());
            }

            if (rightStick.getRawButton(2) && DEBUG_MODE) {
                drive.resetEncoders();
            }
        }
        oi.lightsOff();
        oi.setStuffsBrokenLED(false);
        FileIO.writeLog();  //Save the log string
    }

    /**
     * Ends the thread.
     * @param elliot Arm controller instance to end.
     */
    public static void threadEnd(ArmController elliot) {
        if(elliot != null)
            elliot.end();
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