/*
 * Operator Interface class
 */
package edu.stuy;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.DriverStationEnhancedIO.EnhancedIOException;

/**
 *
 * @author Prog694
 */
public class DonovanOI implements Ports {

    private DriverStationEnhancedIO enhancedIO;
    private Donovan donnie;
    Timer timer;

    //Might not have to pass a donovan object -EM
    public DonovanOI(Donovan d) {
        donnie = d;
        enhancedIO = DriverStation.getInstance().getEnhancedIO();  //get driverstation IO instance
        timer = new Timer();
        try {
            enhancedIO.setDigitalConfig(LED1, DriverStationEnhancedIO.tDigitalConfig.kOutput);
            enhancedIO.setDigitalConfig(LED2, DriverStationEnhancedIO.tDigitalConfig.kOutput);
            enhancedIO.setDigitalConfig(LED3, DriverStationEnhancedIO.tDigitalConfig.kOutput);
            enhancedIO.setDigitalConfig(LED4, DriverStationEnhancedIO.tDigitalConfig.kOutput);
            enhancedIO.setDigitalConfig(LED5, DriverStationEnhancedIO.tDigitalConfig.kOutput);

            enhancedIO.setDigitalConfig(BIT_1_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(BIT_2_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(BIT_3_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(BIT_4_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(A_FRAME_SWITCH, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(ACQUIRER_SWITCH_A, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(ACQUIRER_SWITCH_B, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(WINCH_SWITCH, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(KICK_SWITCH, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(E_COCK_SWITCH, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);

            // no analog in setup
        } //normally low; tie switch to +
        catch (DriverStationEnhancedIO.EnhancedIOException ex) {
            System.out.println("Enhanced IO Exception");
        }
    }

    /**
     * if returns 1 -> target is wayyyyy off to the left
     * if returns 2 -> target is kind of off to the left
     * if returns 3 -> target is in the central center!!
     * if returns 4 -> target is kinda  off to the right
     * if returns 5 -> target is wayyyy off to the right
     * @param target
     * @return different cases
     */
    public int getTargetLocation(DonovanTarget target) {
        double angle = target.getHorizontalAngle();
        if (angle >= 14) {
            return 1;
        } else if (angle > 2) {
            return 2;
        } else if (angle > -2) {
            return 3;
        } else if (angle > -14) {
            return 4;
        } else {
            return 5;
        }
    }

    public void resetLEDs() {
        try {
            enhancedIO.setDigitalOutput(LED1, false);
            enhancedIO.setDigitalOutput(LED2, false);
            enhancedIO.setDigitalOutput(LED3, false);
            enhancedIO.setDigitalOutput(LED4, false);
            enhancedIO.setDigitalOutput(LED5, false);
        } catch (EnhancedIOException ex) {
           // do nothing
            // ex.printStackTrace();
        }
    }

    public int lightLEDs(DonovanTarget target) {
        int targetCase = getTargetLocation(target);
        //System.err.println("targetcase: " + targetCase);
        try {
            switch (targetCase) {
                case 1:
                    enhancedIO.setDigitalOutput(LED1, true);
                    enhancedIO.setDigitalOutput(LED2, false);
                    enhancedIO.setDigitalOutput(LED3, false);
                    enhancedIO.setDigitalOutput(LED4, false);
                    enhancedIO.setDigitalOutput(LED5, false);
                    break;
                case 2:
                    enhancedIO.setDigitalOutput(LED1, false);
                    enhancedIO.setDigitalOutput(LED2, true);
                    enhancedIO.setDigitalOutput(LED3, false);
                    enhancedIO.setDigitalOutput(LED4, false);
                    enhancedIO.setDigitalOutput(LED5, false);
                    break;
                case 3:
                    enhancedIO.setDigitalOutput(LED1, false);
                    enhancedIO.setDigitalOutput(LED2, false);
                    enhancedIO.setDigitalOutput(LED3, true);
                    enhancedIO.setDigitalOutput(LED4, false);
                    enhancedIO.setDigitalOutput(LED5, false);
                    break;
                case 4:
                    enhancedIO.setDigitalOutput(LED1, false);
                    enhancedIO.setDigitalOutput(LED2, false);
                    enhancedIO.setDigitalOutput(LED3, false);
                    enhancedIO.setDigitalOutput(LED4, true);
                    enhancedIO.setDigitalOutput(LED5, false);
                    break;
                case 5:
                    enhancedIO.setDigitalOutput(LED1, false);
                    enhancedIO.setDigitalOutput(LED2, false);
                    enhancedIO.setDigitalOutput(LED3, false);
                    enhancedIO.setDigitalOutput(LED4, false);
                    enhancedIO.setDigitalOutput(LED5, true);
                    break;
                default:
                    enhancedIO.setDigitalOutput(LED1, false);
                    enhancedIO.setDigitalOutput(LED2, false);
                    enhancedIO.setDigitalOutput(LED3, false);
                    enhancedIO.setDigitalOutput(LED4, false);
                    enhancedIO.setDigitalOutput(LED5, false);
                    break;
            }
        } catch (DriverStationEnhancedIO.EnhancedIOException ex) {
            System.out.println("Enhanced IO Exception");
            return 1;
        }
        return 0;
    }

      public void testLEDs() {
        try {
            enhancedIO.setDigitalOutput(LED1, true);
            enhancedIO.setDigitalOutput(LED2, true);
            enhancedIO.setDigitalOutput(LED3, true);
            enhancedIO.setDigitalOutput(LED4, true);
            enhancedIO.setDigitalOutput(LED5, true);
        } catch (EnhancedIOException ex) {
           // ex.printStackTrace();
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

            DriverStationLCD.getInstance().println(DriverStationLCD.Line.kUser2, 1, binaryValue[0] + " " + binaryValue[1] + " " + binaryValue[2] + " " + binaryValue[3]);

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

  

    public boolean getA_Frame() {
        try {
            return enhancedIO.getDigital(A_FRAME_SWITCH);
        } catch (EnhancedIOException ex) {
           // ex.printStackTrace();
        }
        return false;
    }

    public boolean getWench() {
        try {
            return enhancedIO.getDigital(WINCH_SWITCH);
        } catch (EnhancedIOException ex) {
            //ex.printStackTrace();
        }
        return false;
    }

    public boolean getKick() {
        try {
            return enhancedIO.getDigital(KICK_SWITCH);
        } catch (EnhancedIOException ex) {
          //  ex.printStackTrace();
        }
        return false;
    }

    public boolean getCock() {
        try {
            return enhancedIO.getDigital(E_COCK_SWITCH);
        } catch (EnhancedIOException ex) {
           // ex.printStackTrace();
        }
        return false;
    }

    public boolean getAcquirerForward() {
        try {
            return enhancedIO.getDigital(ACQUIRER_SWITCH_A);
        } catch (EnhancedIOException ex) {
          //  ex.printStackTrace();
        }
        return false;
    }

    public boolean getAcquirerReverse() {
        try {
            return enhancedIO.getDigital(ACQUIRER_SWITCH_B);
        } catch (EnhancedIOException ex) {
           // ex.printStackTrace();
        }
        return false;
    }
}


