
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
/**
 *
 * @author Alex Carrillo
 */
package stuy;

import edu.wpi.first.wpilibj.*;

public class Autonomous implements Constants {

    DESdroid des;
    int leftValue, middleValue, rightValue;

    public Autonomous(DESdroid d) {
        des = d;
    }

    public void getSensorValues() {
        leftValue = des.leftSensor.get() ? 1 : 0;
        middleValue = des.middleSensor.get() ? 1 : 0;
        rightValue = des.rightSensor.get() ? 1 : 0;
    }

    public void printLineStatus() {
        System.out.println("L: [" + (leftValue == 1 ? "1" : " ") + "] "
                + "M: [" + (middleValue == 1 ? "1" : " ") + "] "
                + "R: [" + (rightValue == 1 ? "1" : " ") + "]");
    }

    public int binaryValue(boolean goLeft) {
        if (goLeft) {
            return leftValue * 4 + middleValue * 2 + rightValue;
        }
        return rightValue * 4 + middleValue * 2 + leftValue;
    }

    /**
     * Goes down line, forks right, moves back, raises arm (fake), goes forward.
     */
    public void setting1() {
        lineTrack(false, false);
        goForward(false);

        // call arm raise here
        Timer.delay(2);

        goForward(true);
    }

    /**
     * Goes down straight line, no fork, moves back, raises arm (fake), goes forward.
     */
    public void setting2() {
        lineTrack(true, false);
        goForward(false);

        // call arm raise here
        Timer.delay(2);

        goForward(true);
    }


    /**
     * Goes down line, forks left, moves back raises arm (fake), goes forward.
     */
    public void setting3() {
        lineTrack(false, true);
        goForward(false);

        // call arm raise here
        Timer.delay(2);

        goForward(true);
    }

    
        /**
     * Raises arm (fake) then goes down line, forks right.
     */
    public void setting4() {
        // call arm raise here
        Timer.delay(2);

        lineTrack(false, false);
    }

    /**
     * Raises arm (fake), goes down straight line, no fork.
     */
    public void setting5() {
        // call arm raise here
        Timer.delay(2);

        lineTrack(true, false);
    }


    /**
     * Raises arm (fake) goes down line, forks left.
     */
    public void setting6() {
        // call arm raise here
        Timer.delay(2);

        lineTrack(false, true);
    }
    
    
    
    /**
     * Goes forward or backwards to have space in between the peg and the robot's
     * bumper so we can raise the arm to score.
     * @param direction Forward/backward-ness.  Forward = true
     * the `magnitude' variable controls the speed
     */
    private void goForward(boolean direction) {
        double magnitude = 0.1;

        // mecanumDrive expects a negative joystick value for forward motion
        double speed = (direction ? -1 : 1) * magnitude;
        
        des.drive.mecanumDrive_Cartesian(0, speed, 0, 0, false);
        Timer.delay(2);
        des.drive.mecanumDrive_Cartesian(0, 0, 0, 0, false);
    }

    public void lineTrack(boolean straightLine, boolean goLeft) {

        int binaryValue; // a single binary value of the three line tracking
        // sensors
        int previousValue = 0; // the binary value from the previous loop
        double steeringGain; // the amount of steering correction to apply

        // the power profiles for the straight and forked robot path. They are
        // different to let the robot drive more slowly as the robot approaches
        // the fork on the forked line case.
        double powerProfile[];   // the selected power profile
//        powerProfile = (straightLine) ? STRAIGHT_PROFILE : FORK_PROFILE;
        powerProfile = (straightLine) ? FileIO.getArray("straightLine.txt") : FileIO.getArray("forkProfile.txt");
        double stopTime = (straightLine) ? 2.0 : 4.0; // when the robot should look for end

        boolean atCross = false; // if robot has arrived at end

        // time the path over the line
        Timer timer = new Timer();
        timer.start();
        timer.reset();

        double time;
        double speed, turn;

        // loop until robot reaches "T" at end or 8 seconds has past
        while ((time = timer.get()) < 8.0 && !atCross) {
            int timeInSeconds = (int) time;
            getSensorValues();
            binaryValue = binaryValue(goLeft);
            steeringGain = goLeft ? -DEFAULT_STEERING_GAIN : DEFAULT_STEERING_GAIN;

            // get the default speed and turn rate at this time
            speed = powerProfile[timeInSeconds];
            turn = 0;

            // different cases for different line tracking sensor readings
            switch (binaryValue) {
                case 1:  // on line edge
                    turn = 0;
                    break;
                case 7:  // all sensors on (maybe at cross)
                    if (time > stopTime) {
                        atCross = true;
                        speed = -.1;
                    }
                    break;
                case 0:  // all sensors off
                    if (previousValue == 0 || previousValue == 1) {
                        turn = steeringGain;
                    } else {
                        turn = -steeringGain;
                    }
                    break;
                default:  // all other cases
                    turn = -steeringGain;
            }
            

            // set the robot speed and direction
            des.drive.mecanumDrive_Cartesian(-turn, -speed, 0.0, 0.0, false);

            // print current status for debugging
            if (binaryValue != previousValue) {
                printLineStatus();
                System.out.println("forward " + -speed + " strafe " + -turn);
            }


            if (binaryValue != 0)
                previousValue = binaryValue;

            Timer.delay(0.01);
        }
        // Done with loop - stop the robot. Robot ought to be at the end of the line
        des.drive.arcadeDrive(0, 0);
    }
}
