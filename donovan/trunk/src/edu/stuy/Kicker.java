package edu.stuy;

import edu.wpi.first.wpilibj.*;

/**
 * This Kicker Kicks the soccer ball when called.
 * @author Prog
 */
public class Kicker extends Victor{

    //May need sensors

    public Kicker(int channel){
        super(channel);
    }

    /**
     * This method shoots the ball the same way no matter
     * where in the field the robot is
     */
    public void shoot() {
    }
}
