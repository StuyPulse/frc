/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stuy;

import edu.wpi.first.wpilibj.*;

/**
 * Arm position control class.  Runs in its own thread.    
 * @author Ginkgo
 */
public class ArmController extends Thread implements Constants {

    boolean active;
    double setpoint;
    DESdroid des;

    /**
     * Create a new ArmController to set the arm's position to a setpoint.  Uses
     * potentiometer feedback to reach the correct position.  Runs in its own
     * thread so that we can drive the robot at the same time as the arm.
     * @param d A reference to the DESdroid object where the robot is running.
     * @param buttonNum The button number corresponding to the desired height
     * (one of Constants.X_Y_BUTTON, with X and Y being SIDE, MIDDLE, etc.
     * @param trimAmount The amount of adjustment to apply to the setpoint,
     * can be provided by driver input from the OI.  0 is no adjustment.
     */
    public ArmController(DESdroid d, int buttonNum, double trimAmount) {
        active = true;
        des = d;
        switch (buttonNum) {
            case SIDE_UPPER_BUTTON:
                setpoint = Arm.POT_SIDE_TOP - trimAmount;
                break;
            case SIDE_MIDDLE_BUTTON:
                setpoint = Arm.POT_SIDE_MIDDLE - trimAmount;
                break;
            case SIDE_LOWER_BUTTON:
                setpoint = Arm.POT_SIDE_BOTTOM - trimAmount;
                break;
            case CENTER_UPPER_BUTTON:
                setpoint = Arm.POT_MIDDLE_TOP - trimAmount;
                break;
            case CENTER_MIDDLE_BUTTON:
                setpoint = Arm.POT_MIDDLE_MIDDLE - trimAmount;
                break;
            case CENTER_LOWER_BUTTON:
                setpoint = Arm.POT_MIDDLE_BOTTOM - trimAmount;
                break;
            case FEEDER_LEVEL_BUTTON:
                setpoint = Arm.POT_FEEDER_LEVEL - trimAmount;
                break;
            case GROUND_LEVEL_BUTTON:
                setpoint = Arm.POT_GROUND_LEVEL - trimAmount;
                break;
        }
    }

    /**
     * Run the position control loop (in its own thread).
     */
    public void run() {
        while (active) {
            double currentVal = des.arm.getPosition();
            // Check if the arm is above/below the setpoint, with a small tolerance.
            if (currentVal - setpoint > 0.005) {       // Intentionally does not depend on a software limit, because there is a physical limit
                // Move up
                des.arm.armMotor.set(1);
            } else if (currentVal - setpoint < -0.005) {
                // Move down
                des.arm.armMotor.set(-1);
            } else {
                // We're done!  Stop the motor and end the thread.
                des.arm.armMotor.set(0);
                this.end();
            }

            // Pulse the motor on and off at different frequencies depending on
            // how far we have to move.  For big amounts of error, run the motor
            // longer than it is off, for small error run it less frequently.
            double delayVal = Arm.ARM_PWM_MULT * Math.abs(des.arm.getPosition() - setpoint);
            Timer.delay(delayVal);
            des.arm.armMotor.set(0);
            try {
                delayVal = Arm.ARM_PWM_MULT / Math.abs(des.arm.getPosition() - setpoint);
            } catch (Exception e) {
                FileIO.reportError("ARMCONTROLLER", e, "Divided by zero in setHeight()");
            }
            Timer.delay(delayVal);
        }

    }

    public void end() {
        active = false;
    }
}
