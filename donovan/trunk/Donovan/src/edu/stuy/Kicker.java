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
    boolean limSwitchBroken;

    public Kicker(int channel, Donovan d) {
        super(channel);
        limSwitch = new DigitalInput(LIMSWITCH_CHANNEL);
        donnie = d;
        limSwitchBroken = false;
    }

    /**
     * This method shoots the ball the same way no matter
     * where in the field the robot is.  It will cock if 
     * it hasn't been cocked already.
     */
    public void shoot() {
        if (limSwitchBroken) {
            System.out.println("manual control - running kicker");
            runKicker();
            return ;
        }

            cock();
            long time = Timer.getUsClock();
            System.out.println("kicking");
            set(1.0);
            Timer.delay(0.5);
//            while (limSwitch.get() == NOT_COCKED && (Timer.getUsClock() - time < 2000000)) {
//                set(1.0);
//            }
//            set(0.0);
            cock();
    }
    /*
     * This moves the cam so that the kicker is pulled back and ready to fire
     */

    public void cock() {
        if (limSwitchBroken) {
            System.out.println("manaual control - cock button disabled");
            return ;
        }
        System.out.println("cocking");
        long time = Timer.getUsClock();
        while (limSwitch.get() == NOT_COCKED && (Timer.getUsClock() - time < 2000000)) { //COCKED defined in Ports
            set(0.75);
            //may need a short delay?
            
        }
        set(0.0);
    }

    public void stop() {
        set(0.0);
    }

    /**
     * Used for testing when the limit switch is not properly installed
     */
    public void runKicker() {
        set(1.0);
    }

    public boolean getCockStatus() {
        return limSwitch.get();
    }
}
 