
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

    DigitalInput bit1 = new DigitalInput(4,AUTON_SWITCH_1);
    DigitalInput bit2 = new DigitalInput(4,AUTON_SWITCH_2);
    DigitalInput bit3 = new DigitalInput(4,AUTON_SWITCH_3);
    DigitalInput bit4 = new DigitalInput(4,AUTON_SWITCH_4);


    public int getAutonSwitch() {

        if (!bit1.get() && !bit2.get() && !bit3.get() && !bit4.get())
            return 0;
        if (!bit1.get() && !bit2.get() && !bit3.get() && bit4.get())
            return 1;
        if (!bit1.get() && !bit2.get() && bit3.get() && !bit4.get())
            return 2;
        if (!bit1.get() && !bit2.get() && bit3.get() && bit4.get())
            return 3;
        if (!bit1.get() && bit2.get() && !bit3.get() && !bit4.get())
            return 4;
        if (!bit1.get() && bit2.get() && !bit3.get() && bit4.get())
            return 5;
        if (!bit1.get() && bit2.get() && bit3.get() && !bit4.get())
            return 6;
        if (!bit1.get() && bit2.get() && bit3.get() && bit4.get())
            return 7;
        else {
            return 0;
        }

    }

}
