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
    Victor trayMotors;

    /**
     * Minibot constructor. It initializes the tray motors and and the cage latch servo.
     */
    public Minibot() {
        cageLatch = new Servo(CAGE_LATCH_SERVO_CHANNEL);
        cageLatch.set(0);
        trayMotors = new Victor(TRAY_MOTORS_CHANNEL);
    }

    /**
     * Extents the minibot tray out.
     */
    public void trayOut() {
        trayMotors.set(1);
    }

    /**
     * Retracts the minibot tray.
     */
    public void trayIn() {
        trayMotors.set(0);
    }

    /**
     * Release the latch that keeps the minibot in place.
     */
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
