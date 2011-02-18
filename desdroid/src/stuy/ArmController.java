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
    DESdroid robot;

    public ArmController(double setpoint, DESdroid that) {
        active = true;
        this.setpoint = setpoint;
        this.robot = that;
    }

    public void run() {
        while (active) {
            double currentVal = robot.arm.getPosition(); // TODO: Find range of getVoltage().
            System.out.println("Input: " + currentVal);
            System.out.println("Setpoint: " + setpoint);
            if (currentVal - setpoint > 0.005 && currentVal > LOWER_ARM_POT_LIM) {
                robot.arm.armMotor.set(1);
            } else if (currentVal - setpoint < -0.01 && currentVal < UPPER_ARM_POT_LIM) {
                robot.arm.armMotor.set(-1);
            } else {
                robot.arm.armMotor.set(0);
                this.end();
            }
            double delayVal = MAX_ARM_DELAY * Math.abs(robot.arm.getPosition() - setpoint);
            System.out.println("Rising: " + delayVal);
            Timer.delay(delayVal); //TODO:  Protect from /0 !
            robot.arm.armMotor.set(0);
            delayVal = MAX_ARM_DELAY / Math.abs(robot.arm.getPosition() - setpoint);
            System.out.println("Falling: " + delayVal);
            Timer.delay(delayVal); //TODO:  Protect from /0 !

        }

    }

    public void end() {
        active = false;
    }
}
