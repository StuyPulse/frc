
/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package edu.stuy;
import edu.wpi.first.wpilibj.*;
/**
 *
 * @author Prog
 */
public class BinarySwitch {

    final int AUTON_SWITCH_1 = 1;
    final int AUTON_SWITCH_2 = 2;
    final int AUTON_SWITCH_3 = 3;
    final int AUTON_SWITCH_4 = 4;

    DigitalInput binarySwitch1 = new DigitalInput(4,AUTON_SWITCH_1);
    DigitalInput binarySwitch2 = new DigitalInput(4,AUTON_SWITCH_2);
    DigitalInput binarySwitch3 = new DigitalInput(4,AUTON_SWITCH_3);
    DigitalInput binarySwitch4 = new DigitalInput(4,AUTON_SWITCH_4);


    public int getAutonSwitch() {

        if (!binarySwitch1.get() && !binarySwitch2.get() && !binarySwitch3.get() && !binarySwitch4.get())
            return 0;
        if (!binarySwitch1.get() && !binarySwitch2.get() && !binarySwitch3.get() && binarySwitch4.get())
            return 1;
        if (!binarySwitch1.get() && !binarySwitch2.get() && binarySwitch3.get() && !binarySwitch4.get())
            return 2;
        if (!binarySwitch1.get() && !binarySwitch2.get() && binarySwitch3.get() && binarySwitch4.get())
            return 3;
        if (!binarySwitch1.get() && binarySwitch2.get() && !binarySwitch3.get() && !binarySwitch4.get())
            return 4;
        if (!binarySwitch1.get() && binarySwitch2.get() && !binarySwitch3.get() && binarySwitch4.get())
            return 5;
        if (!binarySwitch1.get() && binarySwitch2.get() && binarySwitch3.get() && !binarySwitch4.get())
            return 6;
        if (!binarySwitch1.get() && binarySwitch2.get() && binarySwitch3.get() && binarySwitch4.get())
            return 7;
        else {
            return 0;
        }

    }

}
