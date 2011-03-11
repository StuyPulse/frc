 /*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stuy;

import edu.wpi.first.wpilibj.*;

/**
 * Controls the DESdroid arm shoulder. Note that the Fisher Price motor that powers the arm must "not" be run at low speeds or it will burn out.
 * Also note that position control is in ArmController.java
 *
 * @author blaky
 */
public class Arm implements Constants {
    //Upper & lower arm limits
    static final double LOWER_ARM_POT_LIM           = 1.85; //UNUSED
    static final double UPPER_ARM_POT_LIM           = 4.7;

    //Arm potentiometer values 
    static final double POT_SIDE_BOTTOM             = 3.75;
    static final double POT_SIDE_MIDDLE             = 3.12;
    static final double POT_SIDE_TOP                = 3.28;
    static final double POT_MIDDLE_BOTTOM           = 3.67;
    static final double POT_MIDDLE_MIDDLE           = 2.99;
    static final double POT_MIDDLE_TOP              = 2.28;
    static final double POT_FEEDER_LEVEL            = 3.63;
    static final double POT_GROUND_LEVEL            = 4.37;

    //Arm delay multiplier.  Used in ArmController. 
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
        if (stickVal >= 0.5) {
            armMotor.set(1);
        }
        else if (stickVal <= -0.5) {
            armMotor.set(-1);
        }
        else {
            armMotor.set(0);
        }
    }

    /** 
     * Returns position of arm potentiometer. 
     */
     public double getPosition() {
       return potentiometer.getVoltage();
    }
}
