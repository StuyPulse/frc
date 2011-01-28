/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stuy;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.camera.*;
import edu.wpi.first.wpilibj.image.*;


/**
 *
 * @author Ginkgo
 */
public class DESCircleTracker implements Constants{
    double kScoreThreshold = .01;
    AxisCamera cam;
    DESTrackerDashboard trackerDashboard;
    
    public DESCircleTracker() {

        cam = AxisCamera.getInstance();
        cam.writeResolution(AxisCamera.ResolutionT.k320x240);
        cam.writeBrightness(0);


    }

        public void doCamera() {
        try {
            if (cam.freshImage()) {// && turnController.onTarget()) {

                ColorImage image = cam.getImage();
                Thread.yield();
                DESTarget[] targets = DESTarget.findCircularTargets(image);
                Thread.yield();
                image.free();
                if (targets.length == 0 || targets[0].m_score < kScoreThreshold) {
                   // System.out.println("No target found");

                    DESTarget[] newTargets = new DESTarget[targets.length + 1];
                    newTargets[0] = new DESTarget();
                    newTargets[0].m_majorRadius = 0;
                    newTargets[0].m_minorRadius = 0;
                    newTargets[0].m_score = 0;
                    for (int i = 0; i < targets.length; i++) {
                        newTargets[i + 1] = targets[i];
                    }

                    trackerDashboard.updateVisionDashboard(0.0, 0.0, 0.0, 0.0, newTargets);

                } else {
                  //  System.out.println(targets[0]);
                   // System.out.println("Target Angle: " + targets[0].getHorizontalAngle());

                   // System.out.println("calling lightLEDs");

                     trackerDashboard.updateVisionDashboard(0.0, 0.0, 0.0, targets[0].m_xPos / targets[0].m_xMax, targets);
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
}
