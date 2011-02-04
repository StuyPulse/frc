/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stuy;

import edu.wpi.first.wpilibj.*;

/**
 * This class controls minibot deployment mechanisms.
 * @author Kevin Wang
 */
public class Minibot implements Constants {
    Servo cageLatch;

    public Minibot() {
        cageLatch = new Servo(CAGE_LATCH_SERVO_CHANNEL);
        cageLatch.set(0);
    }

    public void trayOut() {

    }

    public void trayIn() {

    }

    public void openCage() {
        cageLatch.set(1);
    }

    /**
     * Extends the tray out
     * Opens the cage to release the minibot
     */
    public void deploy() {
        trayOut();
        openCage();
    }
}
