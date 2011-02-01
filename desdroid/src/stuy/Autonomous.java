
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
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

    public void run(int setting) {
        switch (setting) {
            case 1:
                auton1();
                break;
            case 2:
                auton2();
                break;
            case 3:
                auton3();
                break;
            case 4:
                auton4();
                break;
            case 5:
                break; // Do nothing.
        }
    }

    public void printLineStatus() {
        System.out.println("L: [" + (leftValue == 1 ? "1" : " ") + "] "
                + "M: [" + (middleValue == 1 ? "1" : " ") + "] "
                + "R: [" + (rightValue == 1 ? "1" : " ") + "]");
    }

    public int binaryValue(boolean goLeft) {
        if (goLeft)
            return leftValue * 4 + middleValue * 2 + rightValue;
        return rightValue * 4 + middleValue * 2 + leftValue;
    }

    /**
     * Follow line straight
     * Score
     * Back up along line
     */
    public void auton1() {
        des.arm.setHeight(0);
        lineTrack(true, false);
        des.grabber.out();
        Timer.delay(2);
        des.grabber.stop();
        backTrack(true, false);
    }

    /**
     * Follow line left
     * Score
     * Back up along line
     */
    public void auton2() {
        des.arm.setHeight(0);
        lineTrack(false, true);
        des.grabber.out();
        Timer.delay(2);
        des.grabber.stop();
        backTrack(false, true);
    }

    /**
     * Follow line right
     * Score
     * Back up along line
     */
    public void auton3() {
        des.arm.setHeight(0);
        lineTrack(false, false);
        des.grabber.out();
        Timer.delay(2);
        des.grabber.stop();
        backTrack(false, false);
    }

    /**
     * Drop übertube
     */
    public void auton4() {
        des.grabber.out();
        Timer.delay(2);
        des.grabber.stop();
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
        powerProfile = (straightLine) ? FileIO.getArray("straightProfile.txt") : FileIO.getArray("forkProfile.txt");
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
                        speed = 0;
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
            // print current status for debugging
            if (binaryValue != previousValue)
                printLineStatus();

            // set the robot speed and direction
            des.drive.arcadeDrive(-speed, -turn);

            if (binaryValue != 0)
                previousValue = binaryValue;

            Timer.delay(0.01);
        }
        // Done with loop - stop the robot. Robot ought to be at the end of the line
        des.drive.arcadeDrive(0, 0);
    }
        public void backTrack(boolean straightLine, boolean goLeft) {

        int binaryValue; // a single binary value of the three line tracking
        // sensors
        int previousValue = 0; // the binary value from the previous loop
        double steeringGain; // the amount of steering correction to apply

        // the power profiles for the straight and forked robot path. They are
        // different to let the robot drive more slowly as the robot approaches
        // the fork on the forked line case.
        double powerProfile[];   // the selected power profile
//        powerProfile = (straightLine) ? STRAIGHT_PROFILE : FORK_PROFILE;
        powerProfile = (straightLine) ? FileIO.getArray("straightProfile.txt") : FileIO.getArray("forkProfile.txt");
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
                        speed = 0;
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
            // print current status for debugging
            if (binaryValue != previousValue)
                printLineStatus();

            // set the robot speed and direction
            des.drive.arcadeDrive(-speed, -turn);

            if (binaryValue != 0)
                previousValue = binaryValue;

            Timer.delay(0.01);
        }
        // Done with loop - stop the robot. Robot ought to be at the end of the line
        des.drive.arcadeDrive(0, 0);
    }
}
