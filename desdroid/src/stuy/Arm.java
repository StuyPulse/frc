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

    Victor armMotor;
    AnalogChannel potentiometer;
    Servo wrist;
    DESdroid des;

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

    public double getPosition() {
        return potentiometer.getVoltage();
    }
}
