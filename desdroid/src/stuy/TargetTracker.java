/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stuy;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.camera.AxisCamera;

/**
 *
 * @author blake
 */
public class TargetTracker implements Constants {
    AxisCamera camera;
    PIDController turnController;
    DESdroid des;

    public TargetTracker(DESdroid d) {
        des = d;
    }

    public void doCamera() {

    }

    public void startAligning() {

    }

    public void stopAligning() {
        
    }

    public void alignAuto() {
        
    }
}
