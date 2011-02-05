/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stuy;

import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.DriverStationEnhancedIO;
import edu.wpi.first.wpilibj.DriverStationEnhancedIO.EnhancedIOException;

/**
 * Handles input from the operator interface using the Cypress FirstTouch I/O module.
 * @author Kevin Wang
 */
public class OperatorInterface implements Constants {
    DriverStationEnhancedIO enhancedIO;
    DESdroid des;

    /**
     * Operator interface constructor, setting digital inputs pulled down.
     */
    public OperatorInterface(DESdroid d) {
        enhancedIO = DriverStation.getInstance().getEnhancedIO();  //get driverstation IO instance
        des = d;
        try {
            enhancedIO.setDigitalConfig(BROKEN_LIGHT, DriverStationEnhancedIO.tDigitalConfig.kOutput);

            enhancedIO.setDigitalConfig(BIT_1_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(BIT_2_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(BIT_3_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(BIT_4_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);

            enhancedIO.setDigitalConfig(OI_LEFT_BOTTOM_BUTTON, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(OI_LEFT_MIDDLE_BUTTON, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(OI_LEFT_TOP_BUTTON, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(OI_MIDDLE_BOTTOM_BUTTON, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(OI_MIDDLE_MIDDLE_BUTTON, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(OI_MIDDLE_TOP_BUTTON, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(OI_RIGHT_BOTTOM_BUTTON, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(OI_RIGHT_MIDDLE_BUTTON, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(OI_RIGHT_TOP_BUTTON, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
        }
        catch (EnhancedIOException e) {
            System.out.println("Error initializing the operator interface.");
        }
    }

    /**
     * Sets the broken light.
     */
    public void setStuffsBrokenLED(boolean val) {
        try {
            enhancedIO.setDigitalOutput(BROKEN_LIGHT, val);
        }
        catch (EnhancedIOException e) {
            System.out.println("Error LED is broken.");
        }
    }
    /**
     * Use a binary switch to set the autonomous mode setting.
     * @return Autonomous setting to run.
     */
    public int getAutonSetting(DESdroid d) {
        des = d;
        try {
            int switchNum = 0;
            int[] binaryValue = new int[4];

            boolean[] dIO = new boolean[]{enhancedIO.getDigital(BIT_1_CHANNEL), enhancedIO.getDigital(BIT_2_CHANNEL), enhancedIO.getDigital(BIT_3_CHANNEL), enhancedIO.getDigital(BIT_4_CHANNEL)};

            for (int i = 0; i < 4; i++) {
                if (dIO[i]) {
                    binaryValue[i] = 1;
                }
                else {
                    binaryValue[i] = 0;
                }
            }

            binaryValue[0] *= 8; // convert all binaryValues to decimal values
            binaryValue[1] *= 4;
            binaryValue[2] *= 2;

            for (int i = 0; i < 4; i++) { // finish binary -> decimal conversion
                switchNum += binaryValue[i];
            }

            if (switchNum > 5) {
                switchNum = 1; // that getAutonSetting() doesn't return a nonexistent switchNum
            }

            return switchNum;
        }
        catch (EnhancedIOException e) {
            setStuffsBrokenLED(true);
            return 5; // Do nothing in case of failure
        }
    }

    public boolean[] getArmButtons() {
        boolean[] armButtons = new boolean[9];
        try {
            armButtons[0] = enhancedIO.getDigital(OI_LEFT_BOTTOM_BUTTON);
            armButtons[1] = enhancedIO.getDigital(OI_LEFT_MIDDLE_BUTTON);
            armButtons[2] = enhancedIO.getDigital(OI_LEFT_TOP_BUTTON);
            armButtons[3] = enhancedIO.getDigital(OI_MIDDLE_BOTTOM_BUTTON);
            armButtons[4] = enhancedIO.getDigital(OI_MIDDLE_MIDDLE_BUTTON);
            armButtons[5] = enhancedIO.getDigital(OI_MIDDLE_TOP_BUTTON);
            armButtons[6] = enhancedIO.getDigital(OI_RIGHT_BOTTOM_BUTTON);
            armButtons[7] = enhancedIO.getDigital(OI_RIGHT_MIDDLE_BUTTON);
            armButtons[8] = enhancedIO.getDigital(OI_RIGHT_TOP_BUTTON);
        }
        catch (EnhancedIOException e) {
            setStuffsBrokenLED(true);
        }
        return armButtons;
    }
}
