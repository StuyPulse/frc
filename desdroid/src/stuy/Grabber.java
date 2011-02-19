/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stuy;

import edu.wpi.first.wpilibj.*;

/**
 * Controls the end effector of the DESdroid arm.
 * @author blake
 */
public class Grabber implements Constants {

    Victor upperRoller;
    Victor lowerRoller;
    DigitalInput limitSwitch;

    /**
     * Grabber constructor.
     */
    public Grabber() {
      upperRoller = new Victor(GRABBER_UPPER_ROLLER_PORT);
      lowerRoller = new Victor(GRABBER_LOWER_ROLLER_PORT);
      limitSwitch = new DigitalInput(GRABBER_LIMIT_SWITCH_PORT);
    }

    /**
     * Intake the tube.
     */
    public void in() {
        if (limitSwitch.get()) {
            upperRoller.set(-1);
            lowerRoller.set(1);
        }
        else {
            upperRoller.set(0);
            lowerRoller.set(0);
        }
    }

    /**
     * Eject the tube.
     */
    public void out() {
        upperRoller.set(1);
        lowerRoller.set(-1);
    }

    /**
     * Rotate the tube up.
     */
    public void rotateUp() {
        upperRoller.set(-1);
        lowerRoller.set(-1);
    }

    /**
     * Rotate the tube down.
     */
    public void rotateDown() {
        upperRoller.set(1);
        lowerRoller.set(1);
    }

    /**
     * Stop the grabber rollers.
     */
    public void stop() {
        upperRoller.set(0);
        lowerRoller.set(0);
    }
    
    public boolean getLimitSwitch() {
        return limitSwitch.get();
    }
}
