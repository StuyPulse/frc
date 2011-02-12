 /*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stuy;

import edu.wpi.first.wpilibj.*;

/**
 * Controls the DESdroid arm elbow.
 * @author blake
 */
public class Arm implements Constants {
    CANJaguar armMotor;
    // DigitalInput potentiometer; // wired directly to the jaguar
    DESdroid des;
    Servo wrist;

    /**
     * Arm constructor.
     */
    public Arm(DESdroid d) {
        des = d;

        try {
            armMotor = new CANJaguar(ARM_CAN_DEVICE_NUMBER);
            armMotor.setPositionReference(CANJaguar.PositionReference.kPotentiometer);
            armMotor.configPotentiometerTurns(1);
        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }

        wrist = new Servo(WRIST_SERVO);
    }

    /**
     * Rotate the arm manually. Arm motor must be run at full speed.
     * @param stickVal Driver's joystick value to rotate the arm. (-1.0 to 1.0)
     */
    public void rotate(double stickVal) {
        try {
            if (stickVal >= 0.5) {
                armMotor.setX(1);
            }
            else if (stickVal <= -0.5) {
                armMotor.setX(-1);
            }
            else {
                armMotor.setX(0);
            }
        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }

    /**
     * Move the arm to a specific position.
     * @param potVal The potentiometer value to set the arm to.
     */
    public void setHeight(double potVal) {
        try {
            double currentVal = armMotor.getPosition();
            if (currentVal - potVal > 0.08)
                armMotor.setX(-1);
            else if (currentVal - potVal < -0.08)
                armMotor.setX(1);
            else
                armMotor.setX(0);
        }
        catch(Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }
}
