/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.stuy;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.camera.AxisCamera;
import edu.wpi.first.wpilibj.camera.AxisCameraException;
import edu.wpi.first.wpilibj.image.ColorImage;
import edu.wpi.first.wpilibj.image.NIVisionException;

/**
 *
 * @author Prog
 */
public class DonCircleTracker implements Ports {

    private Donovan donnie;
    double kScoreThreshold = .01;
    AxisCamera cam;
    PIDController turnController;
    DonTrackerDashboard trackerDashboard;

    //set to good default values
    //double pVal = 0.025;
    //double iVal = 0.00075;
    //double dVal = 0.0;

    public DonCircleTracker(Donovan d) {
        donnie = d;
        
        //kScoreThreshold = .01; //we do this higher up in the declaration
        Timer.delay(10.0);
        cam = AxisCamera.getInstance();
        cam.writeResolution(AxisCamera.ResolutionT.k320x240);
        cam.writeBrightness(0);
        
        
        turnController = new PIDController(PVAL, IVAL, DVAL, donnie.gyro, new PIDOutput() {
            public void pidWrite(double output) {
                donnie.dt.arcadeDrive(0, output);
            }
        }, 0.005);
        trackerDashboard = new DonTrackerDashboard(donnie);
        //donnie.gyro.setSensitivity(-0.007); //this also occurs in Donovan.java
        turnController.setInputRange(-360.0, 360.0);
        turnController.setTolerance(1 / 90. * 100);
        turnController.disable();


    }

    public void doCamera() {
        try {
            if (cam.freshImage()) {// && turnController.onTarget()) {
                
                double gyroAngle = donnie.gyro.pidGet();
                ColorImage image = cam.getImage();
                Thread.yield();
                DonovanTarget[] targets = DonovanTarget.findCircularTargets(image);
                Thread.yield();
                image.free();
                if (targets.length == 0 || targets[0].m_score < kScoreThreshold) {
                   // System.out.println("No target found");

                    DonovanTarget[] newTargets = new DonovanTarget[targets.length + 1];
                    newTargets[0] = new DonovanTarget();
                    newTargets[0].m_majorRadius = 0;
                    newTargets[0].m_minorRadius = 0;
                    newTargets[0].m_score = 0;
                    for (int i = 0; i < targets.length; i++) {
                        newTargets[i + 1] = targets[i];
                    }

                    trackerDashboard.updateVisionDashboard(0.0, donnie.gyro.getAngle(), 0.0, 0.0, newTargets);
                    donnie.oi.resetLEDs();

                } else {
                  //  System.out.println(targets[0]);
                   // System.out.println("Target Angle: " + targets[0].getHorizontalAngle());
                    turnController.setSetpoint(gyroAngle + targets[0].getHorizontalAngle());

                   // System.out.println("calling lightLEDs");
                    donnie.oi.lightLEDs(targets[0]);

                     trackerDashboard.updateVisionDashboard(0.0, donnie.gyro.getAngle(), 0.0, targets[0].m_xPos / targets[0].m_xMax, targets);
                }
            }
        } catch (NIVisionException ex) {
            ex.printStackTrace();
        } catch (AxisCameraException ex) {
            ex.printStackTrace();
        }
        //System.out.println("Time : " + (Timer.getUsClock() - startTime) / 1000000.0);
       // System.out.println("Gyro Angle: " + donnie.gyro.getAngle());
        //counter ++;
    }

    public void startAligning() {
        
        turnController.enable();
        turnController.setSetpoint(donnie.gyro.pidGet());
    }

    public void stopAligning() {
        turnController.disable();
    }

    public void alignAuto(){
        long time = Timer.getUsClock();
        while((Timer.getUsClock() - 3000000 < time) && donnie.isAutonomous() && donnie.isEnabled()) {
            doCamera();
            turnController.enable();
        }
        turnController.disable();

            /*
        long time = Timer.getUsClock();
        while((!turnController.onTarget())&& donnie.isEnabled()) {
            doCamera();
            if((Timer.getUsClock() - 3000000 < time) && donnie.isAutonomous() && donnie.isEnabled())
                turnController.enable();
            else break;
        }
        turnController.disable();
             * */

    }
}
