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
    Servo minibotRelease;

    /**
     * Minibot constructor. Deployment of the minibot is controlled by a servo.
     */
    public Minibot() {
        minibotRelease = new Servo(MINIBOT_RELEASE_SERVO);
        minibotRelease.set(0);
    }

    /**
     * Deploys the minibot.
     */
    public void deploy() {
        minibotRelease.set(1);
    }
}
