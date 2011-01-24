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

    CANJaguar[] rollers;

    public Grabber() {
        rollers = new CANJaguar[2];
        try {
            rollers[0] = new CANJaguar(GRABBER_CAN_DEVICE_NUMBER[0]);
            rollers[1] = new CANJaguar(GRABBER_CAN_DEVICE_NUMBER[1]);
        }
        catch (Exception e) {

        }
    }

    public void rollInwards(double speed) {

    }

    public void rollOutwards() {

    }
}
