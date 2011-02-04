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

    CANJaguar upperRoller;
    CANJaguar lowerRoller;

    DESdroid des;

    byte syncGroup = (byte)0x81;

    /**
     * Grabber constructor.
     */
    public Grabber(DESdroid d) {
      des = d;
        try {
            upperRoller = new CANJaguar(GRABBER_UPPER_ROLLER_DEVICE);
            lowerRoller = new CANJaguar(GRABBER_LOWER_ROLLER_DEVICE);
        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }

    /**
     * Intake the tube.
     */
    public void in() {
        try {
            upperRoller.setX(1, syncGroup);
            lowerRoller.setX(-1, syncGroDup);
            CANJaguar.updateSyncGroup(syncGroup);
        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }

    /**
     * Eject the tube.
     */
    public void out() {
        try {
            upperRoller.setX(-1, syncGroup);
            lowerRoller.setX(1, syncGroup);
            CANJaguar.updateSyncGroup(syncGroup);
        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }

    /**
     * Rotate the tube up.
     */
    public void rotateUp() {
        try {
            upperRoller.setX(1, syncGroup);
            lowerRoller.setX(1, syncGroup);
            CANJaguar.updateSyncGroup(syncGroup);
        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }

    /**
     * Rotate the tube down.
     */
    public void rotateDown() {
        try {
            upperRoller.setX(-1, syncGroup);
            lowerRoller.setX(-1, syncGroup);
            CANJaguar.updateSyncGroup(syncGroup);
        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }

    /**
     * Stop the grabber rollers.
     */
    public void stop() {
        try {
            upperRoller.setX(0, syncGroup);
            lowerRoller.setX(0, syncGroup);
            CANJaguar.updateSyncGroup(syncGroup);
        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }
}
