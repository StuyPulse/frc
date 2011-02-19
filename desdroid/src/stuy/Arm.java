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
    static final double LOWER_ARM_POT_LIM           = 1.85;
    static final double UPPER_ARM_POT_LIM           = 4.7;
    static final double POT_SIDE_BOTTOM             = 3.54;
    static final double POT_SIDE_MIDDLE             = 3.01;
    static final double POT_SIDE_TOP                = 2.38;
    static final double POT_MIDDLE_BOTTOM           = 3.47;
    static final double POT_MIDDLE_MIDDLE           = 2.67;
    static final double POT_MIDDLE_TOP              = 2.0;
    static final double POT_FEEDER_LEVEL            = 3.52;
    static final double POT_GROUND_LEVEL            = 4.44;
    static final double MAX_ARM_DELAY               = .4;

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
        double currentVal = getPosition();
        if (stickVal >= 0.5 && currentVal < UPPER_ARM_POT_LIM) {
            armMotor.set(1);
        }
        else if (stickVal <= -0.5 && currentVal > LOWER_ARM_POT_LIM) {
            armMotor.set(-1);
        }
        else {
            armMotor.set(0);
        }
    }

    /**
     * Move the arm to a specific position.
     * @param potVal The potentiometer value to set the arm to.
     */
    public boolean setHeight(double potVal) {
        double currentVal = getPosition(); // TODO: Find range of getVoltage().
        if (currentVal - potVal > 0.005 && currentVal > LOWER_ARM_POT_LIM) {
            armMotor.set(1);
        }
        else if (currentVal - potVal < -0.01 && currentVal < UPPER_ARM_POT_LIM) {
            armMotor.set(-1);
        }
        else {
            armMotor.set(0);
            return true;
        }
        double delayVal = MAX_ARM_DELAY * Math.abs(getPosition() - potVal);
        Timer.delay(delayVal); //TODO:  Protect from /0 !
        armMotor.set(0);
        delayVal = MAX_ARM_DELAY / Math.abs(getPosition() - potVal);
        Timer.delay(delayVal); //TODO:  Protect from /0 !
        return false;
    }

    /**
     * Move the arm to a specific position based on an OI height button.
     * @param butonNum The OI height button number pressed.
     */
    public void setHeight(int buttonNum, double trimAmount) {
        switch (buttonNum) {
            case SIDE_UPPER_BUTTON:
                setHeight(POT_SIDE_TOP + trimAmount);
                break;
            case SIDE_MIDDLE_BUTTON:
                setHeight(POT_SIDE_MIDDLE + trimAmount);
                break;
            case SIDE_LOWER_BUTTON:
                setHeight(POT_SIDE_BOTTOM + trimAmount);
                break;
            case CENTER_UPPER_BUTTON:
                setHeight(POT_MIDDLE_TOP + trimAmount);
                break;
            case CENTER_MIDDLE_BUTTON:
                setHeight(POT_MIDDLE_MIDDLE + trimAmount);
                break;
            case CENTER_LOWER_BUTTON:
                setHeight(POT_MIDDLE_BOTTOM + trimAmount);
                break;
            case FEEDER_LEVEL_BUTTON:
                setHeight(POT_FEEDER_LEVEL + trimAmount);
                break;
            case GROUND_LEVEL_BUTTON:
                setHeight(POT_GROUND_LEVEL + trimAmount);
                break;
        }
    }

    public double getPosition() {
        return potentiometer.getVoltage();
    }
}
