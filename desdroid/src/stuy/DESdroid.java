package stuy;
/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

import edu.wpi.first.wpilibj.*;
import java.util.Vector;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the SimpleRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class DESdroid extends SimpleRobot implements Constants {

    // Robot hardware

    Victor driveFrontLeft, driveRearLeft, driveFrontRight, driveRearRight;
    RobotDrive drive;
    Arm arm;
    Grabber grabber;
    DigitalInput leftSensor, middleSensor, rightSensor;
    // Driver controls
    Joystick leftStick;
    Joystick rightStick;
    Joystick armStick;
    OperatorInterface oi;
    // Autonomous class
    Autonomous auton;
    double[] positions;
    DESCircleTracker pegTracker;
    DESTrackerDashboard trackerDashboard;
    boolean isTargeting = false;
    boolean isOn = false;
    boolean wasEnabledOnce = false;
    boolean wasArmControlled = false;
    Vector targetVals;
    ArmController positionController;
    /**
     * DESdroid constructor.
     */
    public DESdroid() {
        // oi = new OperatorInterface(this);

        arm = new Arm(this);
        grabber = new Grabber();

        leftStick = new Joystick(PORT_LEFT_STICK);
        rightStick = new Joystick(PORT_RIGHT_STICK);
        armStick = new Joystick(PORT_ARM_STICK);

        

       

        driveFrontLeft = new Victor(CHANNEL_FRONT_LEFT);
        driveFrontRight = new Victor(CHANNEL_FRONT_RIGHT);
        driveRearLeft = new Victor(CHANNEL_REAR_LEFT);
        driveRearRight = new Victor(CHANNEL_REAR_RIGHT);



            drive = new RobotDrive(driveFrontLeft,
                    driveRearLeft,
                    driveFrontRight,
                    driveRearRight);
        


        targetVals = new Vector();
        trackerDashboard = new DESTrackerDashboard(this);
        pegTracker = new DESCircleTracker(this);

        System.out.println(pegTracker);
        System.out.println(pegTracker.halogen_a);

        auton = new Autonomous(this);

        //positions = FileIO.getArray("positions.txt"); // TODO: where is this file?
        positions = new double[] {.3, 1, 1.7};
    }

    /**
     * This function is called once each time the robot enters autonomous mode.
     */
    public void autonomous() {
        getWatchdog().setEnabled(false);

//        auton.run(oi.getAutonSetting(this));
        auton.run(1);

    }

    /**
     * This function is called once each time the robot enters operator control.
     */
    public void operatorControl() {
        getWatchdog().setEnabled(false);

        double lastTimeSeconds = Timer.getFPGATimestamp();

        while (isEnabled() && isOperatorControl()) {
            /*drive.mecanumDrive_Cartesian(
                    leftStick.getX(), // X translation (horizontal strafe)
                    leftStick.getY(), // Y translation (straight forward)
                    rightStick.getX(), // rotation (clockwise?)
                    0, // use gyro for field-oriented drive
                    true);
             */

            if (leftStick.getRawButton(3))
                drive.mecanumDrive_Cartesian(0, -1, 0, 0);
            else if(leftStick.getRawButton(2))
                drive.mecanumDrive_Cartesian(0, 1, 0, 0);
            else if(leftStick.getRawButton(4))
                drive.mecanumDrive_Cartesian(-1, 0, 0, 0);
            else if(leftStick.getRawButton(5))
                drive.mecanumDrive_Cartesian(1, 0, 0, 0);
            else
                drive.mecanumDrive_Cartesian(0, 0, 0, 0);

            // Arm control

            if (armStick.getRawButton(4))
                arm.wrist.set(0);

            if (armStick.getRawButton(11)){
                if(!wasArmControlled){
                    threadend(positionController);
                    positionController = new ArmController(POT_SIDE_BOTTOM, this);
                    positionController.start();
                    wasArmControlled = true;
                }

//                arm.setHeight(POT_SIDE_BOTTOM); //arm.setHeight(positions[0]);
            } else if (armStick.getRawButton(10)) {
                if (!wasArmControlled) {
                    threadend(positionController);
                    positionController = new ArmController(positions[1], this);
                    positionController.start();
                    wasArmControlled = true;
                }
//                arm.setHeight(positions[1]);
            } else if (armStick.getRawButton(9)) {
                if (!wasArmControlled) {
                    threadend(positionController);
                    positionController = new ArmController(positions[2], this);
                    positionController.start();
                    wasArmControlled = true;
                }

//                arm.setHeight(positions[2]);
            } else if (armStick.getRawButton(8)) {
                threadend(positionController);
                wasArmControlled=false;
                System.out.println("Arm position" + arm.getPosition());
            }else {
                threadend(positionController);
                wasArmControlled=false;
                arm.rotate(armStick.getY());
            }


            if (armStick.getRawButton(8)) {
                positions = FileIO.getArray("positions.txt");
            } 

            // Grabber control
            if (armStick.getTrigger())
                grabber.in();
            else if (armStick.getRawButton(2))
                grabber.out();
            else if (armStick.getRawButton(6))
                grabber.rotateUp();
            else if (armStick.getRawButton(7))
                grabber.rotateDown();
            else
                grabber.stop();
            
            //System.out.println(grabber.getLimitSwitch());



            wasEnabledOnce = true;



            



        }
        

    }


    public void threadend(ArmController elliot){
        if(elliot!=null)
                elliot.end();
    }


    
}
