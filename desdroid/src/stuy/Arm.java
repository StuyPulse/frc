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
    DigitalInput potentiometer;

    /**
     * Arm constructor.
     */
    public Arm() {
        try {
            armMotor = new CANJaguar(ARM_CAN_DEVICE_NUMBER, CANJaguar.ControlMode.kPosition);
            armMotor.setPositionReference(CANJaguar.PositionReference.kPotentiometer);
            armMotor.setPID(ARM_P, ARM_I, ARM_D);

            armMotor.configSoftPositionLimits(LOWER_ARM_POT_LIM, UPPER_ARM_POT_LIM); //TODO:  FIND THESE LOWER, UPPER POT LIMITS
        } catch (Exception e) {
        }
    }

    /**
     * Rotate the arm manually.
     * @param speed Speed to rotate the arm at. (-1.0 to 1.0)
     */
    public void rotate(double speed) {
        try {
            armMotor.setX(speed);
        }
        catch (Exception e) {
            // turn on exception LED
            //System.out.println(e);
        }
    }

    /**
     * Move the arm to a specific position.
     * @param height The height to set the arm to.
     */
    public void setHeight(double height) {

        try {
            armMotor.enableControl();

        }
        catch(Exception e) {
            System.out.println(e);
        }




        }
    }
