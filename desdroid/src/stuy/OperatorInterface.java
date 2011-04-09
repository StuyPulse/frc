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
     * Operator interface constructor, setting digital inputs pulled up.
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
            enhancedIO.setDigitalConfig(OI_DRAWBRIDGE_SWITCH_PORT, DriverStationEnhancedIO.tDigitalConfig.kInputPullUp);
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
            
            FileIO.reportError("OI", e, "Failed to set stuffs broken LED");
        }
    }

    /**
     * Use a thumbwheel switch to set the autonomous mode setting. Because the switch begins at 0 (January), 1 is added to the switch value to get the auton setting number.
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

            return switchNum + 1; // Because January is 1, not 0
        }
        catch (EnhancedIOException e) {
            setStuffsBrokenLED(true);
            FileIO.reportError("OI", e, "Failed to read from auton switch");
            return -1; // Do nothing in case of failure
        }
    }

    /**
     * Determines which height button is pressed. All eleven (8 logically because
     * side buttons are wired together) arm height buttons are wired by means of
     * resistors to one analog input. Depending on the button that is pressed, a
     * different voltage is read by the analog input. Each resistor reduces the
     * voltage by about 1/8 the maximum voltage.
     *
     * @return An integer value representing the height button that was pressed.
     */
    public int getHeightButton() {
        return (int) ((getRawAnalogVoltage() / (getMaxVoltage() / 8)) + .5);
    }

    /**
     * Gets the voltage read by the arm height button analog input.
     * @return The voltage of the arm height button analog input.
     */
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

    /**
     * Check if a height button is being pressed.
     * @return True if a height button is being pressed.
     */
    public boolean isHeightButtonPressed() {
        return getHeightButton() != 0;
    }

    /**
     * Checks the state of the minibot switch.
     * @return True if pressed.
     */
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

    /**
     * Checks the state of the drawbridge switch.
     * @return True if pressed.
     */
    public boolean getDrawbridgeSwitch() {
        boolean value;
        try {
            value = !enhancedIO.getDigital(OI_DRAWBRIDGE_SWITCH_PORT);
        }
        catch (EnhancedIOException e) {
            FileIO.reportError("OI", e, "Failed to read drawbridge switch");
            setStuffsBrokenLED(true);
            value = false;
        }
        return value;
    }

    /**
     * Checks the state of the extra button.
     * @return True if pressed.
     */
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

    /**
     * Maps the position of the trim potentiometer to a range between -maxTrim
     * and maxTrim for adjusting the arm position control setpoint.
     * 
     * @param maxTrim The range of arm pot voltage that the trim pot affects.
     * @return 0 if the trim pot is in the center position. Otherwise, -maxTrim to maxTrim.
     */
    public double getTrimAmount(double maxTrim) {
        double potVoltage;
        try {
            potVoltage = enhancedIO.getAnalogIn(OI_TRIM_POT_PORT);
        }
        catch (EnhancedIOException e) {
            potVoltage = 1.65;  // Magic number obtained through guessing.
            FileIO.reportError("OI", e, "Failed to read trim pot");
            setStuffsBrokenLED(true);
        }
        double trimAmount = (((potVoltage - (getMaxVoltage() / 2)) * 2) / getMaxVoltage()) * maxTrim;
        return trimAmount;
    }

    /**
     * Sets the button light to turn on. Button lights on the OI are controlled
     * by 5 digital outputs; four for binary, and one to enable/disable the
     * lights. These light numbers are defined in Constants.
     *
     * @param lightNum The number of the light to turn on.
     */
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

    /**
     * Outputs high on the disable bit to turn off all button lights.
     */
    public void lightsOff() {
        try {
            enhancedIO.setDigitalOutput(LIGHT_DISABLE_CHANNEL, true);
        }
        catch (EnhancedIOException e) {
            FileIO.reportError("OI", e, "Failed to turn lights off");
            setStuffsBrokenLED(true);
        }
    }

    /**
     * Reads the value of an analog input wired directly from the 3.3v pin.
     * This is effectively the voltage read by the Cypress board which is being
     * sent out of the 3.3v pin. Math is done on this voltage to determine
     * height buttons and the trim pot mapping.
     * @return The voltage of the Cypress board.
     */
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
