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
    Victor armMotor;
    DigitalInput potentiometer;

    public Arm() {
        armMotor = new Victor(ARM_MOTOR_CHANNEL_NUMBER);
    }

    public void drive(double speed) {
        armMotor.set(speed);
    }

    public void setHeight(double height) {
        
    }
}
