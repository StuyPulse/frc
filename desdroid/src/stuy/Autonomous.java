
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

public class Autonomous {
    DESdroid des;

    DigitalInput left; // digital inputs for line tracking sensors
    DigitalInput middle;
    DigitalInput right;

    Gyro gyro;

    OperatorInterface oi;

    public Autonomous(DESdroid d) {
        des = d;

        left = new DigitalInput(1);
        middle = new DigitalInput(2);
        right = new DigitalInput(3);

        // set the MotorSafety expiration timer
        des.drive.setExpiration(15);


        gyro = new Gyro(0);

        oi = new OperatorInterface();
    }

    public void lineTrackStraight() {

        int binaryValue; // a single binary value of the three line tracking
                        // sensors
        int previousValue = 0; // the binary value from the previous loop
        double steeringGain; // the amount of steering correction to apply

        // the power profiles for the straight and forked robot path. They are
        // different to let the robot drive more slowly as the robot approaches
        // the fork on the forked line case.


        double forkProfile[] = {0.70, 0.70, 0.55, 0.60, 0.60, 0.50, 0.40, 0.00};
        double straightProfile[] = {0.7, 0.7, 0.6, 0.6, 0.35, 0.35, 0.35, 0.0};

        double powerProfile[];   // the selected power profile

        // set the straightLine and left-right variables depending on chosen path
        boolean straightLine;
        boolean goLeft;
        switch (oi.getAutonSwitch()) {
            case 1: // Go straight
                straightLine = true;
                goLeft = false;
            case 2: // Go left
                straightLine = false;
                goLeft = true;
            case 3: // Go right
                straightLine = false;
                goLeft = false;
            default:
                straightLine = true;
                goLeft = false;
        }
//        straightLine = des.ds.getDigitalIn(des.DIGITAL_IN_STRAIGHT_LINE);
        powerProfile = (straightLine) ? straightProfile : forkProfile;
        double stopTime = (straightLine) ? 2.0 : 4.0; // when the robot should look for end
//        goLeft = !des.ds.getDigitalIn(des.DIGITAL_IN_GO_LEFT) && !straightLine;
        System.out.println("StraightLine: " + straightLine);
        System.out.println("GoingLeft: " + goLeft);


        boolean atCross = false; // if robot has arrived at end

        // time the path over the line
        Timer timer = new Timer();
        timer.start();
        timer.reset();

        int oldTimeInSeconds = -1;
        double time;
        double speed, turn;

        // loop until robot reaches "T" at end or 8 seconds has past
        while ((time = timer.get()) < 8.0 && !atCross) {
            int timeInSeconds = (int) time;
            // read the sensors
            int leftValue = left.get() ? 1 : 0;
            int middleValue = middle.get() ? 1 : 0;
            int rightValue = right.get() ? 1 : 0;
            // compute the single value from the 3 sensors. Notice that the bits
            // for the outside sensors are flipped depending on left or right
            // fork. Also the sign of the steering direction is different for left/right.
            if (goLeft) {
                binaryValue = leftValue * 4 + middleValue * 2 + rightValue;
                steeringGain = -des.defaultSteeringGain;
            } else {
                binaryValue = rightValue * 4 + middleValue * 2 + leftValue;
                steeringGain = des.defaultSteeringGain;
            }

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
            if (binaryValue != previousValue) {
                System.out.println("Time: " + time + " Sensor: " + binaryValue + " speed: " + speed + " turn: " + turn + " atCross: " + atCross);
            }

            // set the robot speed and direction
            // for summer drive train, "normal" wheels
            des.drive.arcadeDrive(speed, turn);

            // Try this for mecanum drive train:
            //des.drive.mecanumDrive_Polar(speed, turn, turn);

            if (binaryValue != 0) {
                previousValue = binaryValue;
            }
            oldTimeInSeconds = timeInSeconds;

            Timer.delay(0.01);
        }
        // Done with loop - stop the robot. Robot ought to be at the end of the line
        des.drive.arcadeDrive(0, 0);
    }

}
