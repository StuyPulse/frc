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
    
    /**
     * Operator interface constructor, setting digital inputs pulled down.
     */
    public OperatorInterface() {
        enhancedIO = DriverStation.getInstance().getEnhancedIO();  //get driverstation IO instance
        try {
            enhancedIO.setDigitalConfig(ERROR_LED, DriverStationEnhancedIO.tDigitalConfig.kOutput);

            enhancedIO.setDigitalConfig(LIGHT_BIT_A_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kOutput);
            enhancedIO.setDigitalConfig(LIGHT_BIT_B_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kOutput);
            enhancedIO.setDigitalConfig(LIGHT_BIT_C_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kOutput);
            enhancedIO.setDigitalConfig(LIGHT_BIT_D_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kOutput);
            enhancedIO.setDigitalConfig(LIGHT_DISABLE_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kOutput);

            enhancedIO.setDigitalConfig(BIT_1_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullUp);
            enhancedIO.setDigitalConfig(BIT_2_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullUp);
            enhancedIO.setDigitalConfig(BIT_3_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullUp);
            enhancedIO.setDigitalConfig(BIT_4_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullUp);

            enhancedIO.setDigitalConfig(OI_MINIBOT_SWITCH_PORT, DriverStationEnhancedIO.tDigitalConfig.kInputPullUp);
            enhancedIO.setDigitalConfig(OI_WING_SWITCH_PORT, DriverStationEnhancedIO.tDigitalConfig.kInputPullUp);
            enhancedIO.setDigitalConfig(OI_EXTRA_BUTTON_PORT, DriverStationEnhancedIO.tDigitalConfig.kInputPullUp);
        }
        catch (EnhancedIOException e) {

            FileIO.reportError("OI", e, "Failed to initialize operator interface");

        }
    }

    /**
     * Sets the error light. True turns it on.
     */
    public void setStuffsBrokenLED(boolean val) {
        try {
            enhancedIO.setDigitalOutput(ERROR_LED, !val);
        }
        catch (EnhancedIOException e) {
            //setStuffsBrokenLED(true); //RECURSION
            FileIO.reportError("OI", e, "Failed to set stuffs broken LED");
        }
    }
    /**
     * Use a thumbwheel switch to set the autonomous mode setting.
     * @return Autonomous setting to run.
     */
    public int getAutonSetting() {
        try {
            int switchNum = 0;
            int[] binaryValue = new int[4];

            boolean[] dIO = {!enhancedIO.getDigital(BIT_1_CHANNEL), !enhancedIO.getDigital(BIT_2_CHANNEL), !enhancedIO.getDigital(BIT_3_CHANNEL), !enhancedIO.getDigital(BIT_4_CHANNEL)};

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

            if (switchNum > 4) {
                switchNum = 4; // that getAutonSetting() doesn't return a nonexistent switchNum
            }

            return switchNum + 1; // Because January is 1, not 0
        }
        catch (EnhancedIOException e) {
            setStuffsBrokenLED(true);
            FileIO.reportError("OI", e, "Failed to read from auton switch");
            return -1; // Do nothing in case of failure
        }
    }

    public int getHeightButton() {
        double analogVoltage;
        try {
            analogVoltage = enhancedIO.getAnalogIn(OI_BUTTON_ANALOG_PORT);
        }
        catch (EnhancedIOException e) {
            setStuffsBrokenLED(true);
            FileIO.reportError("OI", e, "Failed to get height button");
            analogVoltage = 0;
        }
//        int buttonNum = (int) ((analogVoltage / (2.26 / 8)) + .5);
        int buttonNum = (int) ((analogVoltage / (getMaxVoltage() / 8)) + .5);
        return buttonNum;
    }

    public double getRawAnalogVoltage() {
        try {
            return enhancedIO.getAnalogIn(OI_BUTTON_ANALOG_PORT);
        }
        catch (EnhancedIOException e) {
            FileIO.reportError("OI", e, "Failed to read height button input");
            setStuffsBrokenLED(true);
            return 0;
        }
    }

    public boolean isHeightButtonPressed() {
        return getHeightButton() != 0;
    }

    public boolean getMinibotSwitch() {
        boolean value;
        try {
            value = !enhancedIO.getDigital(OI_MINIBOT_SWITCH_PORT);
        }
        catch (EnhancedIOException e) {
            value = false;
            FileIO.reportError("OI", e, "Failed to read minibot switch");
            setStuffsBrokenLED(true);
        }
        return value;
    }

    public boolean getWingSwitch() {
        boolean value;
        try {
            value = !enhancedIO.getDigital(OI_WING_SWITCH_PORT);
        }
        catch (EnhancedIOException e) {
            FileIO.reportError("OI", e, "Failed to read wing switch");
            setStuffsBrokenLED(true);
            value = false;
        }
        return value;
    }

    public boolean getExtraButton() {
        boolean value;
        try {
            value = !enhancedIO.getDigital(OI_EXTRA_BUTTON_PORT);
        }
        catch (EnhancedIOException e) {
            value = false;
            FileIO.reportError("OI", e, "Failed to read extra button");
            setStuffsBrokenLED(true);
        }
        return value;
    }

    public double getTrimAmount(double maxTrim) {
        double potVoltage;
        try {
            potVoltage = enhancedIO.getAnalogIn(OI_TRIM_POT_PORT);
        }
        catch (EnhancedIOException e) {
            potVoltage = 1.65;
            FileIO.reportError("OI", e, "Failed to read trim pot");
            setStuffsBrokenLED(true);
        }
        double trimAmount = (((potVoltage - (getMaxVoltage() / 2)) * 2) / getMaxVoltage()) * maxTrim;
        return trimAmount;
    }

    public void setLight(int lightNum) {
        String binaryString = DECIMAL_BINARY_TABLE[lightNum];
        boolean[] binaryOutputs = new boolean[4];
        for (int i = 0; i < 4; i++) {
            binaryOutputs[i] = binaryString.toCharArray()[i] == '1';
        }
        try {
            enhancedIO.setDigitalOutput(LIGHT_DISABLE_CHANNEL, false);
            enhancedIO.setDigitalOutput(LIGHT_BIT_D_CHANNEL, binaryOutputs[0]);
            enhancedIO.setDigitalOutput(LIGHT_BIT_C_CHANNEL, binaryOutputs[1]);
            enhancedIO.setDigitalOutput(LIGHT_BIT_B_CHANNEL, binaryOutputs[2]);
            enhancedIO.setDigitalOutput(LIGHT_BIT_A_CHANNEL, binaryOutputs[3]);
        }
        catch (EnhancedIOException e) {

            FileIO.reportError("OI", e, "Failed to set button lights");
            setStuffsBrokenLED(true);
        }
    }

    public void lightsOff() {
        try {
            enhancedIO.setDigitalOutput(LIGHT_DISABLE_CHANNEL, true);
        }
        catch (EnhancedIOException e) {
            FileIO.reportError("OI", e, "Failed to turn lights off");
            setStuffsBrokenLED(true);
        }
    }

    public double getMaxVoltage() {
        try {
            return enhancedIO.getAnalogIn(OI_MAX_VOLTAGE_INPUT);
        }
        catch (EnhancedIOException e) {
            FileIO.reportError("OI", e, "Failed to get max voltage");
            setStuffsBrokenLED(true);
            return 2.2;
        }
    }
}
