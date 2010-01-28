package edu.stuy;

import edu.wpi.first.wpilibj.*;


/**
 * This acquires the ball so that the robot may kick it.
 * It will keep the ball near the robot and prevent the ball from drifting.
 * @author Prog
 */
public class Acquirer extends Victor{

    public Acquirer(int channel){
        super(channel);
    }

    /**
     * This will run the acquirer so it can keep the ball
     */
    public void start() {
        set(1); //double pwm value between -1 and 1
    }

    /**
     * This stops the acquirer so it may shoot or something else
     */
    public void stop() {
        set(0);
    }
}
