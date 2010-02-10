package edu.stuy;

import edu.wpi.first.wpilibj.*;

/**
 * This Kicker Kicks the soccer ball when called.
 * @author Prog
 */
public class Kicker extends Victor implements Ports{
	
    //May need sensors
    DigitalInput limSwitch;
    
	
    public Kicker(int channel){
        super(channel);
        limSwitch = new DigitalInput(LIMSWITCH_CHANNEL);
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
        while(limSwitch.get()){
            set(1.0);
        }
        set(0.0);
    }
    /*
     * This moves the cam so that the kicker is pulled back and ready to fire
     */
    public void cock() {
        while (!limSwitch.get()) {
            set(0.25);
        }
        set(0.0);
    }
}
