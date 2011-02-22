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
    Servo wingServo;
    Servo trayRelease;
    Servo minibotRelease;
    Servo motorToggle;
    DigitalInput minibotSwitch;

    /**
     * Minibot constructor. Deployment of the minibot is controlled by a servo.
     */
    public Minibot() {
        wingServo = new Servo(WING_SERVO);
        trayRelease = new Servo(6, TRAY_RELEASE_SERVO);
        minibotRelease = new Servo(6, MINIBOT_RELEASE_SERVO);
        motorToggle = new Servo(6, MOTOR_TOGGLE_SERVO);
        minibotSwitch = new DigitalInput(6, MINIBOT_SWITCH_PORT);
    }

    public void spreadWings() {
        wingServo.set(0);
    }

    /**
     * Deploys the minibot.
     */
    public void deploy() {
        trayRelease.set(0);
        Timer.delay(0.1);
        minibotRelease.set(1);
    }

    public void checkSwitch() {
        if (minibotSwitch.get()) {
            motorToggle.set(1);
        }
    }

    public void reset() {
        wingServo.set(1);
        trayRelease.set(1);
        minibotRelease.set(0);
        motorToggle.set(0);
    }
}
