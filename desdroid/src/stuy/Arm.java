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
    public void setHeight(double potVal) {
        double currentVal = getPosition(); // TODO: Find range of getVoltage().
        System.out.println("Input: " + currentVal);
        System.out.println("Setpoint: " + potVal);
        if (currentVal - potVal > 0.005 && currentVal > LOWER_ARM_POT_LIM) {
            armMotor.set(1);
        }
        else if (currentVal - potVal < -0.01 && currentVal < UPPER_ARM_POT_LIM) {
            armMotor.set(-1);
        }
        else {
            armMotor.set(0);
        }
        double delayVal = MAX_ARM_DELAY * Math.abs(getPosition() - potVal);
        System.out.println("Rising: " + delayVal);
        Timer.delay(delayVal); //TODO:  Protect from /0 !
        armMotor.set(0);
        delayVal = MAX_ARM_DELAY / Math.abs(getPosition() - potVal);
        System.out.println("Falling: " + delayVal);
        Timer.delay(delayVal); //TODO:  Protect from /0 !
    }

    public double getPosition() {
        return potentiometer.getVoltage();
    }

    public double getPotVal() {
        return potentiometer.getVoltage();
    }
    public void toPositionControl() {
        try {
            armMotor.changeControlMode(CANJaguar.ControlMode.kPosition);
            armMotor.setPositionReference(CANJaguar.PositionReference.kPotentiometer);
            //armMotor.setPID(ARM_P, ARM_I, ARM_D);
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
