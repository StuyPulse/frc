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


    //Drawbridge
    static final double DRAWBRIDGE_POT_MIN          = 2.4;

    //Arm potentiometer values 
    static final double POT_SIDE_BOTTOM             = 3.75;
    static final double POT_SIDE_MIDDLE             = 3.12;
    static final double POT_SIDE_TOP                = 2.38;
    static final double POT_MIDDLE_BOTTOM           = 3.67;
    static final double POT_MIDDLE_MIDDLE           = 2.99;
    static final double POT_MIDDLE_TOP              = 2.45;
    static final double POT_FEEDER_LEVEL            = 3.63;
    static final double POT_GROUND_LEVEL            = 4.37;

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
