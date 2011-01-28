
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

    public void lineTrackStraight() {

    }



}
