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
     * Minibot constructor. Deployment of the minibot is controlled by three servos.  Wing deploment is controlled by one servo.  
     */
    public Minibot() {

        wingServo = new Servo(WING_SERVO);

        trayRelease = new Servo(SECOND_SIDECAR_SLOT, TRAY_RELEASE_SERVO);
        minibotRelease = new Servo(SECOND_SIDECAR_SLOT, MINIBOT_RELEASE_SERVO);
        motorToggle = new Servo(SECOND_SIDECAR_SLOT, MOTOR_TOGGLE_SERVO);
        minibotSwitch = new DigitalInput(SECOND_SIDECAR_SLOT, MINIBOT_SWITCH_PORT);
    }

    /**
     * Deploys wings.  
     */
    public void spreadWings() {
        wingServo.set(0);
    }

    /**
     * Debroys the minibot.
     */
    public void debroy() {
        trayRelease.set(0);
        Timer.delay(0.1);
        minibotRelease.set(1);
    }

    /**
     * If minibot is pressed against pole, throw motor switch on.
     */
    public void runMinibotIfReady() {
        if (minibotSwitch.get()) {
            motorToggle.set(1);
        }
    }

    /**
     * Resets all minibot deployment servos.
     */
    public void reset() {
        wingServo.set(1);
        trayRelease.set(1);
        minibotRelease.set(0);
        motorToggle.set(0);
    }
}
