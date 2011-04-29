
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
    final double[] LINE_DIST = {195,
                                192,
                                189};

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
            default:
                break; // Do nothing.
        }
    }

    private void auton1() {
        score(LINE_DIST[0], CENTER_UPPER_BUTTON, true);
    }

    private void auton2() {
        score(LINE_DIST[1], CENTER_UPPER_BUTTON, true);
    }

    private void auton3() {
        score(LINE_DIST[2], CENTER_UPPER_BUTTON, true);
    }

    private void auton4() {
        score(LINE_DIST[0], CENTER_UPPER_BUTTON, false);
    }

    private void auton5() {
        score(LINE_DIST[1], CENTER_UPPER_BUTTON, false);
    }

    private void auton6() {
        score(LINE_DIST[2], CENTER_UPPER_BUTTON, false);
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
     * Run the robot forward/backward.
     * @param speed -1 to 1, full forward = 1
     */
    private void goSpeed(double speed) {
        // mecanumDrive expects a negative joystick value for forward motion
        des.drive.mecanumDrive_Cartesian(0, -speed, 0, 0, false);
    }

    /**
     * This is the main part of the autonomous method.
     * 1. Drop the wrist and wait 1.5 seconds.
     * 2. Rotate the arm upwards to the specified height.
     * 3. Track the line to the specified distance, then stop.
     * 4. Expectorate the tube onto the peg.
     * 5. After half a second, if back boolean is true, back up for two seconds at half speed, then stop.
     * 6. Cease and desist expectoration.
     * 
     * @param dist Distance in inches to track the line.
     * @param armButtonNum OI height button number that refers to the desired arm height.
     */
    private void score(double dist, int armButtonNum, boolean backUp) {
        des.arm.wrist.set(1);
        Timer.delay(1.5);

        ArmController armctl = new ArmController(des, armButtonNum, 0);
        armctl.start();

        lineTrack(true, false, dist);

        DESdroid.threadEnd(armctl);

        des.grabber.out();
        Timer.delay(.5);

        // Back up at the end
        if (backUp) {
            goSpeed(-.5);
            Timer.delay(2);
            goSpeed(0);
        }
        else {
            Timer.delay(0.75);
        }

        des.grabber.stop();
    }
}
