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
    Autonomous auton;
    RobotDrive dt;
    Arm arm;

    public DESdroid() {
        dt = new RobotDrive(1, 2);
        dt.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        dt.setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        dt.setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        dt.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
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
            
        }
    }
}
