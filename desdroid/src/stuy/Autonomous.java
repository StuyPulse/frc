
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
    final double CENTER_UPPER_LINE_DIST = 206;  // this works on our practice field
    final double CENTER_UPPER_LINE_DIST_LESS = 203;   // these might work if 206 is too much
    final double CENTER_UPPER_LINE_DIST_LESS_LESS = 201;
    final double CENTER_UPPER_LINE_DIST_LESS_LESS_LESS = 196;

    final double CENTER_MIDDLE_LINE_DIST = 208; // not tuned, probably too much

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
                auton8();
                break;
            case 9:
                auton9();
                break;
            case 10:
                auton10();
                break;
            case 11:
                auton11();
                break;
            default:
                break; // Do nothing.
        }
    }

    /**
     * Raise arm
     * Follow line straight
     * Score center/middle
     */
    private void auton1() {
        score(CENTER_MIDDLE_LINE_DIST, CENTER_MIDDLE_BUTTON, true);
    }

    /**
     * Raise arm
     * Follow line straight
     * Score top
     */
    private void auton2() {
        score(CENTER_UPPER_LINE_DIST, CENTER_UPPER_BUTTON, true);
    }

    /**
     * Drop ubertube
     */
    private void auton3() {
        des.arm.wrist.set(1);
        Timer.delay(1);
        des.arm.wrist.set(0);
        des.grabber.out();
        Timer.delay(2);
        des.grabber.stop();
    }


    private void auton4() {
        Timer.delay(3);
        score(CENTER_MIDDLE_LINE_DIST, CENTER_MIDDLE_BUTTON, true);
    }

    /**
     * Delay for 3 seconds, then line track and score center top.
     */
    private void auton5() {
        Timer.delay(3);
        score(CENTER_UPPER_LINE_DIST, CENTER_UPPER_BUTTON, true);
    }

    private void auton6() {
        score(CENTER_UPPER_LINE_DIST_LESS, CENTER_UPPER_BUTTON, true);
    }

    private void auton7() {
        score(CENTER_UPPER_LINE_DIST_LESS_LESS, CENTER_UPPER_BUTTON, true);
    }

    private void auton8() {
        score(CENTER_UPPER_LINE_DIST_LESS_LESS_LESS, CENTER_UPPER_BUTTON, true);
    }


    private void auton9() {
        score(CENTER_UPPER_LINE_DIST_LESS, CENTER_UPPER_BUTTON, false);
    }

    private void auton10() {
        score(CENTER_UPPER_LINE_DIST_LESS_LESS, CENTER_UPPER_BUTTON, false);
    }

    private void auton11() {
        score(CENTER_UPPER_LINE_DIST_LESS_LESS_LESS, CENTER_UPPER_BUTTON, false);
    }

    /**
     * Prints the values of the line tracking sensors.
     */
    private int getBinaryValue(boolean goLeft) {
        if (goLeft) {
            return leftValue * 4 + middleValue * 2 + rightValue;
        }
        return rightValue * 4 + middleValue * 2 + leftValue;
    }

    /**
     * Follow the line forward.
     * @param straightLine Set to true to go straight.
     * @param goLeft If straightLine is false, set to true to go left at the fork, and false to go right.
     * @param distance Distance to track the line in inches.
     */
    public void lineTrack(boolean straightLine, boolean goLeft, double distance) {

        des.drive.resetEncoders();

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


        double speed, turn;
        double startTime = Timer.getFPGATimestamp();

        // loop until robot reaches "T" at end or passes the full distance
        while (!atCross && (des.drive.getAvgDistance() < distance) && des.isAutonomous() && des.isEnabled()
                && Timer.getFPGATimestamp() - startTime < 6) {
            int distanceInterval = (int) (powerProfile.length * des.drive.getAvgDistance() / distance);
            
            if (distanceInterval >= powerProfile.length) {
                distanceInterval = powerProfile.length - 1;
            }
            if (distanceInterval < 0) {
                distanceInterval = 0;
            }
            updateSensorValues();
            binaryValue = getBinaryValue(goLeft);
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
     * Follow the line forward or backward.
     * @param straightLine Set to true to go straight.
     * @param goLeft If straightLine is false, set to true to go left at the fork, and false to go right.
     * @param distance Distance to track the line in inches.
     * @param forward Go forward (for hanging a tube) or backward (for returning to the start position)
     */
    public void lineTrack(boolean straightLine, boolean goLeft, double distance, boolean forward) {

        des.drive.resetEncoders();

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


        double speed, turn;
        double startTime = Timer.getFPGATimestamp();

        // loop until robot reaches "T" at end or passes the full distance
        while (!atCross &&
                forward ? (des.drive.getAvgDistance() < distance) :
                          (des.drive.getAvgDistance() > -distance)   // going backwards makes encoders report negative values
                && des.isAutonomous() && des.isEnabled()
                && Timer.getFPGATimestamp() - startTime < 5) {
            int distanceInterval = (int) (powerProfile.length * ((forward ? 1 : -1) * des.drive.getAvgDistance()) / distance);

            if (distanceInterval >= powerProfile.length) {
                distanceInterval = powerProfile.length - 1;
            }
            if (distanceInterval < 0) {
                distanceInterval = 0;
            }
            updateSensorValues();
            binaryValue = getBinaryValue(goLeft);
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
            // set the robot speed and direction
            des.drive.mecanumDrive_Cartesian(-turn, forward ? -speed : speed, 0, 0, false);

            if (binaryValue != 0) {
                previousValue = binaryValue;
            }

            Timer.delay(0.01);
        }
        // Done with loop - stop the robot. Robot ought to be at the end of the line
        des.drive.arcadeDrive(0, 0);
    }
    
    /**
     * Run the robot forward/backward.
     * @param speed -1 to 1, full forward = 1
     */
    private void goSpeed(double speed) {

        // mecanumDrive expects a negative joystick value for forward motion
        des.drive.mecanumDrive_Cartesian(0, -speed, 0, 0, false);
    }

    /**
     * This is the main part of the autonomous method.
     * 1. Intake tube while releasing wrist so the ubertube does not slip out of the grabber.
     * 2. After 1 second (to allow time for the grabber to fall), rotate the tube upwards a bit.
     * 3. After .2 seconds, stop the grabber rollers.
     * 4. Rotate the arm upwards to the specified height.
     * 5. Track the line to the specified distance, then stop.
     * 6. Expectorate the tube onto the peg for one second.
     * 7. Pause for a second, then back up at 1/2 speed for a second.
     * 
     * @param dist Distance in inches to track the line.
     * @param armButtonNum OI height button number that refers to the desired arm height.
     */
    private void score(double dist, int armButtonNum, boolean back) {
        des.grabber.in();
        des.arm.wrist.set(1);
        Timer.delay(2);
        des.grabber.rotateUp(true);
        Timer.delay(.2);
        des.grabber.stop();

        ArmController armctl = new ArmController(des, armButtonNum, 0);
        armctl.start();

        lineTrack(true, false, dist);


        DESdroid.threadEnd(armctl);

        des.grabber.out();
        Timer.delay(.5);

        if (back) {
            // Back up at the end
            goSpeed(-.5);
            Timer.delay(2);
            goSpeed(0);
        }

        des.grabber.stop();
    }
}
