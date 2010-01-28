/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.                             */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/
package edu.wpi.first.wpilibj.samples;

//TODO: switch to using alternate blocking function call with specific task
//TODO: fix PCVideo server failure killing crio
//TODO: Tune loop better
//TODO: add more joystick functionality
import edu.wpi.first.wpilibj.GenericHID.Hand;
import edu.wpi.first.wpilibj.Gyro;
import edu.wpi.first.wpilibj.IterativeRobot;
import edu.wpi.first.wpilibj.Jaguar;
import edu.wpi.first.wpilibj.Joystick;
import edu.wpi.first.wpilibj.PIDController;
import edu.wpi.first.wpilibj.PIDOutput;
import edu.wpi.first.wpilibj.RobotDrive;
import edu.wpi.first.wpilibj.SpeedController;
import edu.wpi.first.wpilibj.Timer;
import edu.wpi.first.wpilibj.camera.AxisCamera;
import edu.wpi.first.wpilibj.camera.AxisCameraException;
import edu.wpi.first.wpilibj.image.ColorImage;
import edu.wpi.first.wpilibj.image.NIVisionException;

/**
 * The VM is configured to automatically run this class, and to call the
 * functions corresponding to each mode, as described in the IterativeRobot
 * documentation. If you change the name of this class or the package after
 * creating this project, you must also update the manifest file in the resource
 * directory.
 */
public class CircleTrackerDemo extends IterativeRobot {

    double kScoreThreshold = .01;
    AxisCamera cam;
    Gyro gyro = new Gyro(1);
    RobotDrive drive = new RobotDrive(1, 2);

    {
        drive.setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);
        drive.setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
    }
    Joystick js = new Joystick(1);
    Joystick js2 = new Joystick(2);
    PIDController turnController = new PIDController(.08, 0.0, 0.5, gyro, new PIDOutput() {

        public void pidWrite(double output) {
            drive.arcadeDrive(0, output);
        }
    }, .005);
    TrackerDashboard trackerDashboard = new TrackerDashboard();

    /**
     * This function is run when the robot is first started up and should be
     * used for any initialization code.
     */
    public void robotInit() {
        Timer.delay(10.0);
        cam = AxisCamera.getInstance();
        cam.writeResolution(AxisCamera.ResolutionT.k320x240);
        cam.writeBrightness(0);
        gyro.setSensitivity(.007);
        turnController.setInputRange(-360.0, 360.0);
        turnController.setTolerance(1 / 90. * 100);
        turnController.disable();
    }

    /**
     * This function is called periodically during autonomous
     */
    public void autonomousPeriodic() {
    }

    /**
     * This function is called while the robot is disabled.
     */
    public void disabledPeriodic() {
    }

    /**
     * This function is called at the beginning of teleop
     */
    public void teleopInit() {
    }
    boolean lastTrigger = false;

    /**
     * This function is called periodically during operator control
     */
    public void teleopPeriodic() {
        long startTime = Timer.getUsClock();
        if (!js.getTrigger()) {
            if (lastTrigger)
                turnController.disable();
            lastTrigger = false;
            drive.tankDrive(js,js2);
        } else {
            if (!lastTrigger) {
                turnController.enable();
                turnController.setSetpoint(gyro.pidGet());
            }
            lastTrigger = true;
            try {
                if (cam.freshImage()) {// && turnController.onTarget()) {
                    double gyroAngle = gyro.pidGet();
                    ColorImage image = cam.getImage();
                    Thread.yield();
                    Target[] targets = Target.findCircularTargets(image);
                    Thread.yield();
                    image.free();
                    if (targets.length == 0 || targets[0].m_score < kScoreThreshold) {
                        System.out.println("No target found");
                        Target[] newTargets = new Target[targets.length + 1];
                        newTargets[0] = new Target();
                        newTargets[0].m_majorRadius = 0;
                        newTargets[0].m_minorRadius = 0;
                        newTargets[0].m_score = 0;
                        for (int i = 0; i < targets.length; i++) {
                            newTargets[i + 1] = targets[i];
                        }
                        trackerDashboard.updateVisionDashboard(0.0, gyro.getAngle(), 0.0, 0.0, newTargets);
                    } else {
                        System.out.println(targets[0]);
                        System.out.println("Target Angle: " + targets[0].getHorizontalAngle());
                        turnController.setSetpoint(gyroAngle + targets[0].getHorizontalAngle());
                        trackerDashboard.updateVisionDashboard(0.0, gyro.getAngle(), 0.0, targets[0].m_xPos / targets[0].m_xMax, targets);
                    }
                }
            } catch (NIVisionException ex) {
                ex.printStackTrace();
            } catch (AxisCameraException ex) {
                ex.printStackTrace();
            }
            System.out.println("Time : " + (Timer.getUsClock() - startTime) / 1000000.0);
            System.out.println("Gyro Angle: " + gyro.getAngle());
        }
    }
}
