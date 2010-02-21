package edu.stuy;

import edu.wpi.first.wpilibj.*;

/**
 * This acquires the ball so that the robot may kick it.
 * It will keep the ball near the robot and prevent the ball from drifting.
 * @author Prog
 */
public class Acquirer extends Victor {

    Donovan donnie;

    public Acquirer(int channel, Donovan d) {
        super(channel);
        donnie = d;
    }

    /**
     * This will run the acquirer so it can keep the ball
     */
    public void start() {
        if (donnie.isAutonomous()) {
            System.out.println("in acq class running fwd and stuff");
        }
        set(-1.0); //double pwm value between -1 and 1
    }

    public void startReverse() {
        if (donnie.isAutonomous()) {
            System.out.println("in acq class running rev and stuff");
        }
        set(1.0);
    }

    /**
     * This stops the acquirer so it may shoot or something else
     */
    public void stop() {
        if (donnie.isAutonomous()) {
            System.out.println("in acq class stopping and stuff");
        }
        set(0);
    }
}
