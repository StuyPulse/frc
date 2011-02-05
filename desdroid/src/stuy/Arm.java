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
    DESdroid des;

    PIDController posController;

    DESdroid des;



    /**
     * Arm constructor.
     */
    public Arm(DESdroid d) {
        des = d;
        try {
            armMotor = new CANJaguar(ARM_CAN_DEVICE_NUMBER, CANJaguar.ControlMode.kPosition);
            armMotor.setPositionReference(CANJaguar.PositionReference.kPotentiometer);
            armMotor.setPID(ARM_P, ARM_I, ARM_D);

            armMotor.configSoftPositionLimits(LOWER_ARM_POT_LIM, UPPER_ARM_POT_LIM); //TODO:  FIND THESE LOWER, UPPER POT LIMITS

            armMotor.enableControl();


        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }

      /*  posController = new PIDController(ARM_P, ARM_I, ARM_D, this, new PIDOutput() {

            public void pidWrite(double output) {
                try {
                armMotor.setX(output);
                }
                catch (Exception e) {
                    des.oi.setStuffsBrokenLED(true);
                }
            }
        });

        posController.setInputRange(0, 255); // pot return value range
        posController.setTolerance(1 / 90. * 100);
        posController.disable(); */
        
    }

    /**
     * Rotate the arm manually.
     * @param speed Speed to rotate the arm. (-1.0 to 1.0)
     */
    public void rotate(double speed) {
        try {
            armMotor.set(speed);
        }
        catch (Exception e) {
            des.oi.setStuffsBrokenLED(true);
        }
        return toReturn;
    }

    /**
     * Move the arm to a specific position.
     * @param height The height to set the arm to.
     */
    public void setHeight(double height) {

        try {
            armMotor.setX(height);
        }
        catch(Exception e) {
            System.out.println(e);
        }




        }


    }
