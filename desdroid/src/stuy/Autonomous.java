
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

    DigitalInput left; // digital inputs for line tracking sensors
    DigitalInput middle;
    DigitalInput right;

    Gyro gyro;

    public Autonomous(DESdroid d) {
        des = d;

        left = new DigitalInput(LINE_SENSOR_LEFT_CHANNEL);
        middle = new DigitalInput(LINE_SENSOR_MIDDLE_CHANNEL);
        right = new DigitalInput(LINE_SENSOR_RIGHT_CHANNEL);

        gyro = new Gyro(GYRO_CHANNEL);
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
        }
    }

    public void lineTrackStraight() {

    }

    /**
     * Follow line straight
     * Score
     * Back up along line
     */
    public void auton1() {

    }

    /**
     * Follow line left
     * Score
     * Back up along line
     */
    public void auton2() {

    }

    /**
     * Follow line right
     * Score
     * Back up along line
     */
    public void auton3() {

    }

    /**
     * Drop uebertube
     */
    public void auton4() {

    }
}
