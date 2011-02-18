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

    VictorSpeed driveFrontLeft, driveRearLeft, driveFrontRight, driveRearRight;
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

        

       

        
            driveFrontLeft = new VictorSpeed(CHANNEL_FRONT_LEFT, 1, 2);
            rightSensor = new DigitalInput(LINE_SENSOR_RIGHT_CHANNEL);
            driveFrontRight = new VictorSpeed(CHANNEL_FRONT_RIGHT, 3, 4);
            middleSensor = new DigitalInput(LINE_SENSOR_MIDDLE_CHANNEL);
            driveRearLeft = new VictorSpeed(CHANNEL_REAR_LEFT, 5, 6);
            leftSensor = new DigitalInput(LINE_SENSOR_LEFT_CHANNEL);
            driveRearRight = new VictorSpeed(CHANNEL_REAR_RIGHT, 7, 8);

            updatePID();

            drive = new DriveTrain(driveFrontLeft,
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

    /**
     * update PID values.  uses a text file drive_PID_values.txt that must be
     * uploaded to the cRIO via ftp://10.6.94.2/ in the root directory.
     */
    public void updatePID() {
        double drivePID[];

         try {
                drivePID = FileIO.getArray("drive_PID_values.txt");
         }
        catch (Exception e) {
            e.printStackTrace();
            drivePID = new double[3];
                drivePID[0] = SPEED_P;
                drivePID[1] = SPEED_I;
                drivePID[2] = SPEED_D;
        }
        System.out.println("PID:  " + drivePID[0] + "  " + drivePID[1] + "  " + drivePID[2]);

        try {
            driveFrontLeft.c.disable();
            driveFrontRight.c.disable();
            driveRearLeft.disable();
            driveRearRight.disable();

            driveFrontLeft.c.setPID(drivePID[0], drivePID[1], drivePID[2]);
            driveFrontRight.c.setPID(drivePID[0], drivePID[1], drivePID[2]);
            driveRearLeft.c.setPID(drivePID[0], drivePID[1], drivePID[2]);
            driveRearRight.c.setPID(drivePID[0], drivePID[1], drivePID[2]);

            driveFrontLeft.c.enable();
            driveFrontRight.c.enable();
            driveRearLeft.c.enable();
            driveRearRight.c.enable();

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
