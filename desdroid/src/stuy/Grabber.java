/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stuy;

import edu.wpi.first.wpilibj.*;

/**
 *
 * @author blake
 */
public class Grabber implements Constants {

    CANJaguar upperRoller;
    CANJaguar lowerRoller;

    byte syncGroup = (byte)0x80;

    public Grabber() {
        try {
            upperRoller = new CANJaguar(GRABBER_UPPER_ROLLER_DEVICE);
            lowerRoller = new CANJaguar(GRABBER_LOWER_ROLLER_DEVICE);
        }
        catch (Exception e) {

        }
    }

    public void in() {
        try {
            upperRoller.setX(1, syncGroup);
            lowerRoller.setX(-1, syncGroup);
            CANJaguar.updateSyncGroup(syncGroup);
        }
        catch (Exception e) {

        }
    }

    public void out() {
        try {
            upperRoller.setX(-1, syncGroup);
            lowerRoller.setX(1, syncGroup);
            CANJaguar.updateSyncGroup(syncGroup);
        }
        catch (Exception e) {

        }
    }

    public void rotateUp() {
        try {
            upperRoller.setX(1, syncGroup);
            lowerRoller.setX(1, syncGroup);
            CANJaguar.updateSyncGroup(syncGroup);
        }
        catch (Exception e) {

        }
    }

    public void rotateDown() {
        try {
            upperRoller.setX(-1, syncGroup);
            lowerRoller.setX(-1, syncGroup);
            CANJaguar.updateSyncGroup(syncGroup);
        }
        catch (Exception e) {

        }
    }

    public void stop() {
        try {
            upperRoller.setX(0, syncGroup);
            lowerRoller.setX(0, syncGroup);
            CANJaguar.updateSyncGroup(syncGroup);
        }
        catch (Exception e) {
            
        }
    }
}
