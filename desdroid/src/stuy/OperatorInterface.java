/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stuy;

import edu.wpi.first.wpilibj.DriverStation;
import edu.wpi.first.wpilibj.DriverStationEnhancedIO;
import edu.wpi.first.wpilibj.DriverStationEnhancedIO.EnhancedIOException;

/**
 *
 * @author Kevin Wang
 */
public class OperatorInterface implements Constants {
    DriverStationEnhancedIO enhancedIO;

    public OperatorInterface() {
        enhancedIO = DriverStation.getInstance().getEnhancedIO();  //get driverstation IO instance
        try {
            enhancedIO.setDigitalConfig(BIT_1_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(BIT_2_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(BIT_3_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(BIT_4_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
        }
        catch (EnhancedIOException e) {
            System.out.println("Enhanced IO exception");
        }
    }

    public int getAutonSwitch() {
        try {
            int switchNum = 0;
            int[] binaryValue = new int[4];
            boolean[] dIO = new boolean[]{enhancedIO.getDigital(BIT_1_CHANNEL), enhancedIO.getDigital(BIT_2_CHANNEL), enhancedIO.getDigital(BIT_3_CHANNEL), enhancedIO.getDigital(BIT_4_CHANNEL)};
            for (int i = 0; i < 4; i++) {
                if (dIO[i]) {
                    binaryValue[i] = 1;
                } else {
                    binaryValue[i] = 0;
                }
            }

            binaryValue[0] *= 8; //convert all binaryValues to decimal values
            binaryValue[1] *= 4;
            binaryValue[2] *= 2;
            for (int i = 0; i < 4; i++) //finish binary -> decimal conversion
            {
                switchNum += binaryValue[i];
            }
            if (switchNum > 11) {
                switchNum = 1; // that BinarySwitch() doesn't return a nonexistent switchNum
            }
            return switchNum;
        } catch (EnhancedIOException ex) {
          //  ex.printStackTrace();
          //  System.err.println("binary switch error!");
            return 1;
        }
    }

    public int getAutonSetting() {
        if (getDoNothingSwitch()) {
            return 5;
        }
        else if (getDropUbertubeSwitch()) {
            return 4;
        }
        else {
            return getDirectionSwitch();
        }
    }

    public int getDirectionSwitch() {
        if (getDirectionSwitchLeft()) {
            return 2;
        }
        else if (getDirectionSwitchRight()) {
            return 3;
        }
        else {
            return 1;
        }
    }

    public boolean getDirectionSwitchLeft() {
        try {
            return enhancedIO.getDigital(DIRECTION_SWITCH_LEFT);
        }
        catch (EnhancedIOException e) {
            e.printStackTrace();
            return false;
        }
    }

    public boolean getDirectionSwitchRight() {
        try {
            return enhancedIO.getDigital(DIRECTION_SWITCH_RIGHT);
        }
        catch (EnhancedIOException e) {
            e.printStackTrace();
            return false;
        }
    }

    public boolean getDropUbertubeSwitch() {
        try {
            return enhancedIO.getDigital(DROP_UBERTUBE_SWITCH);
        }
        catch (EnhancedIOException e) {
            e.printStackTrace();
            return false;
        }
    }

    public boolean getDoNothingSwitch() {
        try {
            return enhancedIO.getDigital(DO_NOTHING_SWITCH);
        }
        catch (EnhancedIOException e) {
            e.printStackTrace();
            return false;
        }
    }
}
