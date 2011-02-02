/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stuy;

import edu.wpi.first.wpilibj.*;

/**
 *
 * @author blake
 */
public class Arm implements Constants {
    CANJaguar armMotor;
    DigitalInput potentiometer;

    public Arm() {
        try {
            armMotor = new CANJaguar(ARM_CAN_DEVICE_NUMBER, CANJaguar.ControlMode.kPosition);
            armMotor.setPositionReference(CANJaguar.PositionReference.kPotentiometer);
        }
        catch (Exception e) {
            
        }
    }

    public void rotate(double speed) {
        try {
            armMotor.setX(speed);
        }
        catch (Exception e) {
            
        }
    }

    public void setHeight(double height) {
        
    }
}
