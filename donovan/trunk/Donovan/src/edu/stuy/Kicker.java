package edu.stuy;

import edu.wpi.first.wpilibj.*;

/**
 * This Kicker Kicks the soccer ball when called.
 * @author Prog
 */
public class Kicker extends Victor implements Ports {

    //May need sensors
    DigitalInput limSwitch;
    Donovan donnie;

    public Kicker(int channel, Donovan d) {
        super(channel);
        limSwitch = new DigitalInput(LIMSWITCH_CHANNEL);
        donnie = d;

    }

    /**
     *
     *
     * This method shoots the ball the same way no matter
     * where in the field the robot is.  It will cock if 
     * it hasn't been cocked already.
     *  
     *
     */
    public void shoot() {
        cock();
      /*  while (limSwitch.get()) {
            set(1.0);

        }
       */
       set(0.0);
    }

    public void stop() {
        set(0.0);
    }

    public void runKicker() {
        set(0.5);
    }
    /*
     * This moves the cam so that the kicker is pulled back and ready to fire
     */
    public void cock() {
        while (/*!limSwitch.get()*/ true) {
            set(0.25);
            if (!donnie.shootStick.getTrigger()) {
                break;
            }
        }
        set(0.0);
    }
}
