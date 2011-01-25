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
    
    public DESCircleTracker() {

        cam = AxisCamera.getInstance();
        cam.writeResolution(AxisCamera.ResolutionT.k320x240);
        cam.writeBrightness(0);
    }
}
