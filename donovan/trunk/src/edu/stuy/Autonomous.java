package edu.stuy;

import edu.wpi.first.wpilibj.*;

/**
 * These are the different methods for autonomus mode.
 * @author Prog
 */
public class Autonomous {
	
    Donovan donnie;
    
	
    public Autonomous(Donovan d){
        donnie = d;
        // set distance per pulse of encoder
        //  move = new Move();
    }
	
    public void runSettingNum(int settingNum) {
        switch(settingNum) {
            case 1: setting1(); break;
            case 2: setting2(); break;
            case 3: setting3(); break;
            case 4: setting4(); break;
            case 5: setting5(); break;
            case 6: setting6(); break;
            case 7: setting7(); break;
            case 8: setting8(); break;
                
        }
    }
    /**
     * This will move robot forward 30 inches while running acquirer
     */
    public void setting1() {
        donnie.roller.start();
        donnie.dt.forwardInches(30);
		
    }
	
    /**
     * This will perform setting1 and then stop the acquirer and shoot
     */
    public void setting2() {
        setting1();
        kick();
    }
	
    /**
     * This will perform setting2 and then move 6 feet forward while running acquirer
     */
    public void setting3() {
        setting2();
        donnie.roller.start();
        donnie.dt.forwardInches(72); //6 feet
    }
	
    /**
     * This will move robot back 16 feet
     * CHECK IF THIS INSTRUCTION IS CORRECT
     */
    public void setting4() {
        donnie.dt.backInches(192); //16 feet
    }
	
    /**
     * This will perform setting2 and then go 3 feet forward while running acquirer
     */
    public void setting5() {
        setting2();
        donnie.roller.start();
        donnie.dt.forwardInches(36); //3 feet
    }
	
    /**
     * This will perform setting5 and then stop the acquirer and shoot
     */
    public void setting6() {
        setting5();
        kick();
    }
	
    /**
     * This will perform setting6 and then move robot
     * forward 3 feet while running acquirer
     */
    public void setting7() {
        setting6();
        donnie.roller.start();
        donnie.dt.forwardInches(36); //3 feet
    }
	
    public void setting8() {
        System.out.println("We are now in setting 8.");
    }
    
    /**
     * This stops the acquirer and kicks the ball
     * 
     */
    private void kick() {
        donnie.kicker.shoot();
        donnie.roller.stop();
    }
	
	
	
}
