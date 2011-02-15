 /*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stuy;

import edu.wpi.first.wpilibj.*;

/**
 * Controls the DESdroid arm elbow. Note that the Fisher Price motor that powers the arm must be run at full speed or it will stall.
 * @author blake
 */
public class Arm implements Constants {

    DESdroid des;
    Victor armMotor;
    AnalogChannel potentiometer;
    Servo wrist;

    /**
     * Arm constructor.
     */
    public Arm(DESdroid d) {
        des = d;
        armMotor = new Victor(ARM_MOTOR_CHANNEL);
        potentiometer = new AnalogChannel(ARM_POT_CHANNEL);
        wrist = new Servo(WRIST_SERVO);
    }

    /**
     * Rotate the arm manually. Arm motor must be run at full speed.
     * @param stickVal Driver's joystick value to rotate the arm. (-1.0 to 1.0)
     */
    public void rotate(double stickVal) {
        try {
            if (stickVal >= 0.5) {
                armMotor.set(1);
            } else if (stickVal <= -0.5) {
                armMotor.set(-1);
            } else {
                armMotor.set(0);
            }
        } catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }

    /**
     * Move the arm to a specific position.
     * @param potVal The potentiometer value to set the arm to.
     */
    public void setHeight(double potVal) {
        try {
            double currentVal = potentiometer.getVoltage(); // TODO: Find range of getVoltage().
            if (currentVal - potVal > 0.08 && currentVal > 0.395) {
                armMotor.set(-1);
            } else if (currentVal - potVal < -0.08 && currentVal < 0.85) {
                armMotor.set(1);
            } else {
                armMotor.set(0);
            }
        } catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }

    public double getPotVal() {
        return potentiometer.getVoltage();
    }
}
