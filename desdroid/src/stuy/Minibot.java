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
    Victor trayMotor;
    Servo minibotRelease;
    Servo motorToggle;
    DigitalInput minibotSwitch;
    DigitalInput trayLimitSwitch;

    /**
     * Minibot constructor. Deployment of the minibot is controlled by three servos.  Wing deploment is controlled by one servo.
     */
    public Minibot() {
        wingServo = new Servo(WING_SERVO);

        trayMotor = new Victor(TRAY_RELEASE_MOTOR_PORT);
        trayLimitSwitch = new DigitalInput(TRAY_LIMIT_SWITCH_PORT);

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
     * Extends the minibot deployer.
     */
    public void runTrayMotor() {
        trayMotor.set(1);
    }

    /**
     * Stops extending the minibot deployer.
     */
    public void stopTrayMotor() {
        trayMotor.set(0);
    }

    /**
     * Checks the tray limit switch and stops the tray motor if it is pressed.
     */
    public void checkTrayLimitSwitch() {
        if (!trayLimitSwitch.get()) {
            stopTrayMotor();
        }
    }

    /**
     * If minibot is pressed against pole, throw motor switch on.
     */
    public void runMinibotIfReady() {
        if (minibotSwitch.get()) {
            if (DESdroid.DEBUG_MODE)
                System.out.println("Pole switch thrown, motor toggle set.");
            minibotRelease.set(1);
            motorToggle.set(0);
        }
    }

    /**
     * Resets all minibot deployment servos.
     */
    public void reset() {
        wingServo.set(1);
        minibotRelease.set(0);
        motorToggle.set(1);
    }
}