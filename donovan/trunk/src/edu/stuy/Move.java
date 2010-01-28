package edu.stuy;

//Should these methods be in DonovanDriveTrain.java ?
//Do we really need a Move class?

/**
 * This is for the robot to drive itself
 * @author Prog
 */
public class Move {

    /**
     * This will move the robot forward in inches
     */
    public void forwardInches(int inches) {

    }

    /**
     * This will move the robot forward in feet
     */
    public void forwardFeet(int feet) {
        forwardInches(feet * 12);
    }

    /**
     * This will move the robot backward in inches
     */
    public void backInches(int inches) {

    }

    /**
     * This will move the robot backward in feet
     */
    public void backFeet(int feet) {
        backInches(feet * 12);
    }
}
