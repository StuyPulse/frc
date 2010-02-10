/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Developer
 */

package edu.stuy;

import edu.wpi.first.wpilibj.*;


public class BinarySwitch implements Ports {
    DigitalInput bit1 = new DigitalInput(BIT_1_CHANNEL);
    DigitalInput bit2 = new DigitalInput(BIT_2_CHANNEL);
    DigitalInput bit3 = new DigitalInput(BIT_3_CHANNEL);
    DigitalInput bit4 = new DigitalInput(BIT_4_CHANNEL);
    
    
	
	
	
	
	
	
	
	/*
	 * To change this template, choose Tools | Templates
	 * and open the template in the editor.
	 */
	
	
	/**
	 *
	 * @author Prog
	 */
	
    public int getAutonSwitch() {
		
        if (!bit1.get() && !bit2.get() && !bit3.get() && !bit4.get()) {
            return 0;
        }
        if (!bit1.get() && !bit2.get() && !bit3.get() && bit4.get()) {
            return 1;
        }
        if (!bit1.get() && !bit2.get() && bit3.get() && !bit4.get()) {
            return 2;
        }
        if (!bit1.get() && !bit2.get() && bit3.get() && bit4.get()) {
            return 3;
        }
        if (!bit1.get() && bit2.get() && !bit3.get() && !bit4.get()) {
            return 4;
        }
        if (!bit1.get() && bit2.get() && !bit3.get() && bit4.get()) {
            return 5;
        }
        if (!bit1.get() && bit2.get() && bit3.get() && !bit4.get()) {
            return 6;
        }
        if (!bit1.get() && bit2.get() && bit3.get() && bit4.get()) {
            return 7;
        } else {
            return 0;
        }
		
		
        /*
		 int switchNum = 0;
		 int[] binaryValue = new int[4];
		 
		 DigitalInput[] inputs = new DigitalInput[] {bit1, bit2, bit3, bit4};
		 
		 for (int i = 0; i < 4; i++) {
		 if (inputs[i].get()) {
		 binaryValue[i] = 1;
		 } else {
		 binaryValue[i] = 0;
		 }
		 }
		 
		 binaryValue[0] *= 8; //convert all binaryValues to decimal values
		 binaryValue[1] *= 4;
		 binaryValue[2] *= 2;
		 
		 for (int i = 0; i < 4; i++) //finish binary -> decimal conversion
		 switchNum += binaryValue[i];
		 
		 if (switchNum > 8) // only 7 settings in autonomous atm; this is inserted so
		 switchNum = 1; // that BinarySwitch() doesn't return a nonexistent switchNum
		 
		 return switchNum;
		 */
		
	}
}
