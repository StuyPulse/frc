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

    public Grabber() {
        try {
            upperRoller = new CANJaguar(GRABBER_UPPER_ROLLER_DEVICE);
            lowerRoller = new CANJaguar(GRABBER_LOWER_ROLLER_DEVICE);
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void in() {

    }

    public void out() {

    }

    public void rotateUp() {
        
    }

    public void rotateDown() {

    }

    public void stop() {
        try {
            upperRoller.setX(0);
            lowerRoller.setX(0);
        }
        catch (Exception e) {
            e.printStackTrace();
        }
    }
}
