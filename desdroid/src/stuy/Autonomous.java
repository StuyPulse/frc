
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

    public Autonomous(DESdroid d) {
        des = d;

        left = new DigitalInput(1);
        middle = new DigitalInput(2);
        right = new DigitalInput(3);

        gyro = new Gyro(0);
    }

    public void lineTrackStraight() {

    }



}
