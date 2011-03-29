/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stuy;

import edu.wpi.first.wpilibj.*;

/**
 * Controls the tube acquirer of the DESdroid arm, a.k.a. the end effector.
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
        upperRoller.set(-1);
        lowerRoller.set(1);
    }

    /**
     * Eject the tube.
     */
    public void out() {
        upperRoller.set(.5);
        lowerRoller.set(-.5);
    }

    /**
     * Rotate the tube upwards.
     */
    public void rotateUp(boolean slow) {
        if (slow) {
            upperRoller.set(-.5);
            lowerRoller.set(-.5);
        }
        else {
            upperRoller.set(-1);
            lowerRoller.set(-1);
        }
    }

    /**
     * Rotate the tube downwards.
     */
    public void rotateDown(boolean slow) {
        if (slow) {
            upperRoller.set(.5);
            lowerRoller.set(.5);
        }
        else {
            upperRoller.set(1);
            lowerRoller.set(1);
        }
    }

    /**
     * Stop the grabber rollers.
     */
    public void stop() {
        upperRoller.set(0);
        lowerRoller.set(0);
    }

    /**
     * Checks if the grabber tube contact sensor is pressed.
     * @return True if limit switch is pressed.
     */
    public boolean getLimitSwitch() {
        return !limitSwitch.get();
    }
}
