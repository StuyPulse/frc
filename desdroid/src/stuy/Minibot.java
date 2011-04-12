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
    Servo drawbridgeServo;
    Victor trayMotor;
    Servo minibotRelease;
    Servo motorToggle;
    DigitalInput poleContactSwitch;
    DigitalInput trayLimitSwitch;
    DigitalInput drawbridgeSwitch;

    /**
     * Minibot constructor. Deployment of the minibot is controlled by three servos.  Drawbridge deploment is controlled by one servo.
     */
    public Minibot() {
        drawbridgeServo = new Servo(SECOND_SIDECAR_SLOT, DRAWBRIDGE_SERVO);

        trayMotor = new Victor(SECOND_SIDECAR_SLOT, TRAY_RELEASE_MOTOR_PORT);

        minibotRelease = new Servo(SECOND_SIDECAR_SLOT, MINIBOT_RELEASE_SERVO);
        motorToggle = new Servo(SECOND_SIDECAR_SLOT, MOTOR_TOGGLE_SERVO);

        trayLimitSwitch = new DigitalInput(SECOND_SIDECAR_SLOT, TRAY_LIMIT_SWITCH_PORT);
        poleContactSwitch = new DigitalInput(SECOND_SIDECAR_SLOT, POLE_CONTACT_SWITCH_PORT);
        drawbridgeSwitch = new DigitalInput(SECOND_SIDECAR_SLOT, DRAWBRIDGE_LIMIT_SWITCH_PORT);
    }

    /**
     * Deploys drawbridge.
     */
    public void deployDrawbridge() {
        drawbridgeServo.set(0);
    }

    /**
     * Extends the minibot deployer.
     */
    public void runTrayMotor(double speed) {
        trayMotor.set(speed);
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
        if (!poleContactSwitch.get() || !trayLimitSwitch.get()) {
            stopTrayMotor();
        }
    }

    public void deploy() {
        minibotRelease.set(1);
        runTrayMotor(1);
    }

    /**
     * Resets all minibot deployment servos.
     */
    public void reset() {
        drawbridgeServo.set(1);
        minibotRelease.set(0);
        motorToggle.set(0);
        stopTrayMotor();
    }

    public boolean getDrawbridgePoleSwitch() {
        return !drawbridgeSwitch.get();
    }
}