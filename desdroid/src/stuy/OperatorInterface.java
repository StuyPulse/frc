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

    /**
     * Use a binary switch to set the autonomous mode setting.
     * @return Autonomous setting to run.
     */
    public int getAutonSetting() {
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
            System.out.println("Binary switch error!");
            return 5; // Do nothing in case of failure
        }
    }
}
