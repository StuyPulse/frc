
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stuy;

import edu.wpi.first.wpilibj.*;

/**
 * This is the location of DESdroid's autonomous routines.
 * @author Kevin Wang
 */
public class Autonomous implements Constants {

    DESdroid des;
    int leftValue, middleValue, rightValue;

    final double CENTER_UPPER_LINE_DIST = 200;  // set these
    final double CENTER_MIDDLE_LINE_DIST = 150; // set these

    /**
     * Autonomous constructor.
     * @param d DESdroid instance to control robot components.
     */
    public Autonomous(DESdroid d) {
        des = d;
    }

    /**
     * Update the values of the line tracking sensors.
     */
    private void updateSensorValues() {
        leftValue = des.leftSensor.get() ? 1 : 0;
        middleValue = des.middleSensor.get() ? 1 : 0;
        rightValue = des.rightSensor.get() ? 1 : 0;
    }

    /**
     * Execute autonomous routine.
     * @param setting The autonomous routine to run.
     */
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
                auton5();
                break;
            case 6:
                auton6();
                break;
            case 7:
                auton7();
                break;
            case 8:
                break; // Do nothing.
        }
    }

    /**
     * Raise arm
     * Follow line straight
     * Score center/middle
     */
    private void auton1() {
        des.grabber.in();
        des.arm.wrist.set(1);
        Timer.delay(1);
        des.arm.wrist.set(0);
        des.grabber.stop();
        des.grabber.rotateUp();
        Timer.delay(.2);
        des.grabber.stop();
        double time = Timer.getFPGATimestamp();

        while (!des.arm.setHeight(Arm.POT_MIDDLE_MIDDLE) && Timer.getFPGATimestamp() - time < 2
                && des.isAutonomous() && des.isEnabled()) {
        }
        if (des.isAutonomous() && des.isEnabled()) {
            lineTrack(true, false, CENTER_MIDDLE_LINE_DIST);
        }
        des.grabber.out();
        Timer.delay(1);
        des.grabber.stop();

        // Back up at the end
        goSpeed(-1);
        Timer.delay(1);
        goSpeed(0);
    }

    /**
     * Raise arm
     * Follow line straight
     * Score top
     */
    private void auton2() {
        des.grabber.in();
        des.arm.wrist.set(1);
        Timer.delay(1);
        des.arm.wrist.set(0);
        des.grabber.stop();
        des.grabber.rotateUp();
        Timer.delay(.2);
        des.grabber.stop();
        double time = Timer.getFPGATimestamp();

        while (!des.arm.setHeight(Arm.POT_MIDDLE_TOP) && Timer.getFPGATimestamp() - time < 2
                && des.isAutonomous() && des.isEnabled()) {
        }
        if (des.isAutonomous() && des.isEnabled()) {
            lineTrack(true, false, CENTER_UPPER_LINE_DIST);
        }
        des.grabber.out();
        Timer.delay(1);
        des.grabber.stop();

        // Back up at the end
        goSpeed(-1);
        Timer.delay(1);
        goSpeed(0);
    }

    /**
     * Raise arm
     * Follow line right
     * Score
     */
    private void auton3() {
        des.arm.setHeight(0);
        lineTrack(false, false, 200);
        des.grabber.out();
        Timer.delay(2);
        des.grabber.stop();

        goSpeed(-1);
        Timer.delay(5);
        goSpeed(0);
    }

    /**
     * Drop ubertube
     */
    private void auton4() {
        des.grabber.out();
        Timer.delay(2);
        des.grabber.stop();
    }

    /**
     * Follow line right
     * moves back a little
     * raises arm (fake)
     * goes forward to peg
     */
    public void auton5() {
        lineTrack(false, false, 200);
        goSpeed(-.1);
        Timer.delay(2);
        goSpeed(0);
        // call arm raise here (get this from `arm' branch)
        Timer.delay(2);
        goSpeed(.1);
        Timer.delay(2);
        goSpeed(0);

        goSpeed(-1);
        Timer.delay(5);
        goSpeed(0);
    }

    /**
     * Follow line straight
     * moves back
     * raises arm (fake)
     * goes forward into peg
     */
    public void auton6() {
        lineTrack(true, false, 200);
        goSpeed(-.1);
        Timer.delay(2);
        goSpeed(0);

        // call arm raise here (get this from `arm' branch)
        Timer.delay(2);

        goSpeed(.1);
        Timer.delay(2);
        goSpeed(0);

        goSpeed(-1);
        Timer.delay(5);
        goSpeed(0);
    }

    /**
     * Follow line left
     * moves back
     * raises arm (fake)
     * goes forward into peg
     */
    public void auton7() {
        lineTrack(false, true, 200);
        goSpeed(-.1);
        Timer.delay(2);
        goSpeed(0);

        // call arm raise here (get this from `arm' branch)
        Timer.delay(2);

        goSpeed(.1);
        Timer.delay(2);
        goSpeed(0);

        goSpeed(-1);
        Timer.delay(5);
        goSpeed(0);
    }

    /**
     * Prints the values of the line tracking sensors.
     */
    private void printLineStatus() {
        /*   System.out.println("L: [" + (leftValue == 1 ? "1" : " ") + "] "
        + "M: [" + (middleValue == 1 ? "1" : " ") + "] "
        + "R: [" + (rightValue == 1 ? "1" : " ") + "]"); */
    }

    private int binaryValue(boolean goLeft) {
        if (goLeft) {
            return leftValue * 4 + middleValue * 2 + rightValue;
        }
        return rightValue * 4 + middleValue * 2 + leftValue;
    }

    /**
     * Follow the line forward.
     * @param straightLine Set to true to go straight.
     * @param goLeft If straightLine is false, set to true to go left at the fork, and false to go right.
     */
    public void lineTrack(boolean straightLine, boolean goLeft, double distance) {

        int binaryValue; // a single binary value of the three line tracking
        // sensors
        int previousValue = 0; // the binary value from the previous loop
        double steeringGain; // the amount of steering correction to apply

        // the power profiles for the straight and forked robot path. They are
        // different to let the robot drive more slowly as the robot approaches
        // the fork on the forked line case.
        double powerProfile[];   // the selected power profile
        powerProfile = (straightLine) ? STRAIGHT_PROFILE : FORK_PROFILE;
        double stopTime = (straightLine) ? 2.0 : 4.0; // when the robot should look for end

        boolean atCross = false; // if robot has arrived at end


        double speed, turn, currentDist;
        double startTime = Timer.getFPGATimestamp();

        // loop until robot reaches "T" at end or passes the full distance
        while (!atCross && (des.getAvgDistance() < distance) && des.isAutonomous() && des.isEnabled()
                && Timer.getFPGATimestamp() - startTime < 5) {
            
            int distanceInterval = (int) (powerProfile.length * des.getAvgDistance() / distance);
            updateSensorValues();
            binaryValue = binaryValue(goLeft);
            steeringGain = goLeft ? -DEFAULT_STEERING_GAIN : DEFAULT_STEERING_GAIN;

            // get the default speed and turn rate at this time
            speed = powerProfile[distanceInterval];
            turn = 0;

            // different cases for different line tracking sensor readings
            switch (binaryValue) {
                case 1:  // on line edge
                    turn = 0;
                    break;
                case 7:  // all sensors on (maybe at cross)
                    if (Timer.getFPGATimestamp() > stopTime) {
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
            if (binaryValue != previousValue) {
                printLineStatus();
            }

            // set the robot speed and direction
//            des.drive.arcadeDrive(-speed, -turn);
            des.drive.mecanumDrive_Cartesian(-turn, -speed, 0, 0, false);

            if (binaryValue != 0) {
                previousValue = binaryValue;
            }

            Timer.delay(0.01);
        }
        // Done with loop - stop the robot. Robot ought to be at the end of the line
        des.drive.arcadeDrive(0, 0);
    }

    /**
     * Run the robot forward/backward
     * @param speed -1 to 1, full forward = 1
     */
    private void goSpeed(double speed) {

        // mecanumDrive expects a negative joystick value for forward motion
        des.drive.mecanumDrive_Cartesian(0, -speed, 0, 0, false);
    }
}
