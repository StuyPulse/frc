/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stuy;

import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Ginkgo
 */
public class ArmController extends Thread implements Constants {

    boolean active;
    double setpoint;
    DESdroid des;

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

    public ArmController(double setpoint, DESdroid that) {
        active = true;
        this.setpoint = setpoint;
        this.des = that;
    }

    public void run() {
        while (active) {
            double currentVal = des.arm.getPosition();
            if (currentVal - setpoint > 0.005 && currentVal > Arm.LOWER_ARM_POT_LIM) {
                des.arm.armMotor.set(1);
            } else if (currentVal - setpoint < -0.005 && currentVal < Arm.UPPER_ARM_POT_LIM) {
                des.arm.armMotor.set(-1);
            } else {
                des.arm.armMotor.set(0);
                this.end();
            }
            double delayVal = Arm.MAX_ARM_DELAY * Math.abs(des.arm.getPosition() - setpoint);
            Timer.delay(delayVal);
            des.arm.armMotor.set(0);
            try {
                delayVal = Arm.MAX_ARM_DELAY / Math.abs(des.arm.getPosition() - setpoint);
            } catch (Exception e) {
                //Do nothing 
            }
            Timer.delay(delayVal); //TODO:  Protect from /0 !

        }

    }

    public void end() {
        active = false;
    }
}
