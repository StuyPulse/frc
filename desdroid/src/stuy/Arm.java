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

    /**
     * Arm constructor.
     */
    public Arm(DESdroid d) {
        des = d;

        try {
            armMotor = new CANJaguar(ARM_CAN_DEVICE_NUMBER);
            toPositionControl();
        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }

    /**
     * Rotate the arm manually. Arm motor must be run at full speed.
     * @param speed Speed to rotate the arm. (-1.0 to 1.0)
     */
    public void rotate(double speed) {
        try {
            toPercentVbusControl();
            if (speed >= 0.5) {
                armMotor.setX(1);
            }
            else if (speed <= -0.5) {
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
     * @param height The height to set the arm to.
     */
    public void setHeight(double height) {
        double init = Timer.getFPGATimestamp();
        try {
            toPositionControl();
            
            armMotor.enableControl();
            armMotor.setX(height);

            armMotor.disableControl();

            toPercentVbusControl();
        }
        catch(Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }

    public void toPositionControl() {
        try {
            armMotor.changeControlMode(CANJaguar.ControlMode.kPosition);
            armMotor.setPositionReference(CANJaguar.PositionReference.kPotentiometer);
            armMotor.setPID(ARM_P, ARM_I, ARM_D);
            armMotor.configSoftPositionLimits(LOWER_ARM_POT_LIM, UPPER_ARM_POT_LIM);
        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }

    public void toPercentVbusControl() {
        try {
            armMotor.changeControlMode(CANJaguar.ControlMode.kPercentVbus);
        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
    }
}