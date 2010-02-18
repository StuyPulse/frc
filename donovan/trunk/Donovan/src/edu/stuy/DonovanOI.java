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
public class DonovanOI implements Ports{

    //if(getHorizontalAngle())
    final int led1 = 2;
    final int led2 = 4;
    final int led3 = 6;
    final int led4 = 8;
    final int led5 = 10;

    final int BIT_1_CHANNEL = 1;
    final int BIT_2_CHANNEL = 3;
    final int BIT_3_CHANNEL = 5;
    final int BIT_4_CHANNEL = 7;

    private DriverStationEnhancedIO enhancedIO;
    private Donovan donnie;

    Timer timer;
    /*
     * IDK what these will be
     */



    

    

    //Might not have to pass a donovan object -EM
    public DonovanOI(Donovan d) {
        donnie = d;
        enhancedIO = DriverStation.getInstance().getEnhancedIO();  //get driverstation IO instance
        timer = new Timer();
        try {
            enhancedIO.setDigitalConfig(led1, DriverStationEnhancedIO.tDigitalConfig.kOutput);
            enhancedIO.setDigitalConfig(led2, DriverStationEnhancedIO.tDigitalConfig.kOutput);
            enhancedIO.setDigitalConfig(led3, DriverStationEnhancedIO.tDigitalConfig.kOutput);
            enhancedIO.setDigitalConfig(led4, DriverStationEnhancedIO.tDigitalConfig.kOutput);
            enhancedIO.setDigitalConfig(led5, DriverStationEnhancedIO.tDigitalConfig.kOutput);

            enhancedIO.setDigitalConfig(BIT_1_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(BIT_2_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(BIT_3_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(BIT_4_CHANNEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(A_FRAME, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(ACQUIRER_SWITCH_A, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(ACQUIRER_SWITCH_B, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(WINCH_REEL, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(KICK, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);
            enhancedIO.setDigitalConfig(EMERGENCY_COCK, DriverStationEnhancedIO.tDigitalConfig.kInputPullDown);




            // no analog in setup
        } //normally low; tie switch to +
        catch (DriverStationEnhancedIO.EnhancedIOException ex) {
            System.out.println("Enhanced IO Exception");
        }
    }

    /**
     * if returns 1 -> target is wayyyyy off to the left
     * if returns 2 -> target is kind of off to the left
     * if returns 3 -> target is in the fucking center!!
     * if returns 4 -> target is kinda  off to the right
     * if returns 5 -> target is wayyyy off to the right
     * @param target
     * @return different cases
     */
    public int getTargetLocation(DonovanTarget target) {
        double angle = target.getHorizontalAngle();
        if (angle >= 14) {
            return 1;
        } else if (angle > 3.5) {
            return 2;
        } else if (angle > -3.5) {
            return 3;
        } else if (angle > -14) {
            return 4;
        } else {
            return 5;
        }
    }

    public void resetLEDs() {
        try {
            enhancedIO.setDigitalOutput(led1, false);
            enhancedIO.setDigitalOutput(led2, false);
            enhancedIO.setDigitalOutput(led3, false);
            enhancedIO.setDigitalOutput(led4, false);
            enhancedIO.setDigitalOutput(led5, false);
        } catch (EnhancedIOException ex) {
            ex.printStackTrace();
        }
    }

    

    public int lightLEDs(DonovanTarget target) {
        int targetCase = getTargetLocation(target);
        System.err.println("targetcase: " + targetCase);
        try {
            switch (targetCase) {
                case 1:
                    enhancedIO.setDigitalOutput(led1, true);
                    enhancedIO.setDigitalOutput(led2, false);
                    enhancedIO.setDigitalOutput(led3, false);
                    enhancedIO.setDigitalOutput(led4, false);
                    enhancedIO.setDigitalOutput(led5, false);
                    break;
                case 2:
                    enhancedIO.setDigitalOutput(led1, false);
                    enhancedIO.setDigitalOutput(led2, true);
                    enhancedIO.setDigitalOutput(led3, false);
                    enhancedIO.setDigitalOutput(led4, false);
                    enhancedIO.setDigitalOutput(led5, false);
                    break;
                case 3:
                    enhancedIO.setDigitalOutput(led1, false);
                    enhancedIO.setDigitalOutput(led2, false);
                    enhancedIO.setDigitalOutput(led3, true);
                    enhancedIO.setDigitalOutput(led4, false);
                    enhancedIO.setDigitalOutput(led5, false);
                    break;
                case 4:
                    enhancedIO.setDigitalOutput(led1, false);
                    enhancedIO.setDigitalOutput(led2, false);
                    enhancedIO.setDigitalOutput(led3, false);
                    enhancedIO.setDigitalOutput(led4, true);
                    enhancedIO.setDigitalOutput(led5, false);
                    break;
                case 5:
                    enhancedIO.setDigitalOutput(led1, false);
                    enhancedIO.setDigitalOutput(led2, false);
                    enhancedIO.setDigitalOutput(led3, false);
                    enhancedIO.setDigitalOutput(led4, false);
                    enhancedIO.setDigitalOutput(led5, true);
                    break;
                default:
                    enhancedIO.setDigitalOutput(led1, false);
                    enhancedIO.setDigitalOutput(led2, false);
                    enhancedIO.setDigitalOutput(led3, false);
                    enhancedIO.setDigitalOutput(led4, false);
                    enhancedIO.setDigitalOutput(led5, false);
                    break;
            }
        } catch (DriverStationEnhancedIO.EnhancedIOException ex) {
            System.out.println("Enhanced IO Exception");
            return 1;
        }
        return 0;
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
            if (switchNum > 9) {
                switchNum = 1; // that BinarySwitch() doesn't return a nonexistent switchNum
            }
            return switchNum;
        } catch (EnhancedIOException ex) {
            ex.printStackTrace();
            System.err.println("binary switch error!");
            return 1;
        }


    }
    public void testLEDs() {
        try {
            enhancedIO.setDigitalOutput(led1, true);
            enhancedIO.setDigitalOutput(led2, true);
            enhancedIO.setDigitalOutput(led3, true);
            enhancedIO.setDigitalOutput(led4, true);
            enhancedIO.setDigitalOutput(led5, true);
        } catch (EnhancedIOException ex) {
            ex.printStackTrace();
        }
        
        
    }

    public boolean getA_Frame() {
        try {
            return enhancedIO.getDigital(A_FRAME);
        } catch (EnhancedIOException ex) {
            ex.printStackTrace();
        }
        return false;
    }
    public void deployA_Frame() {
        donnie.dt.a_Frame.set(0.25);
    }

    public boolean getAWench() {
        try {
            return enhancedIO.getDigital(WINCH_REEL);
        } catch (EnhancedIOException ex) {
            ex.printStackTrace();
        }
        return false;
    }

    public void deployAWench() {
        //reel a wench
    }

    public boolean getAKick() {
        try {
            return enhancedIO.getDigital(KICK);
        } catch (EnhancedIOException ex) {
            ex.printStackTrace();
        }
    return false;
    }

    public void deployAKick() {
        donnie.kicker.runKicker();
        donnie.kicker.shoot();
    }

    public boolean getACock() {
        try {
            return enhancedIO.getDigital(EMERGENCY_COCK);
        } catch (EnhancedIOException ex) {
            ex.printStackTrace();
        }
    return false;
    }

    public void deployACock() {
        donnie.kicker.cock();
    }

    public boolean getAcquirerForward() {
        try {
            return enhancedIO.getDigital(ACQUIRER_SWITCH_A);
        } catch (EnhancedIOException ex) {
            ex.printStackTrace();
        }
        return false;
    }

    public void deployAcquirerForward() {
        donnie.roller.start();
    }

    public boolean getAcquirerReverse() {
        try {
            return enhancedIO.getDigital(ACQUIRER_SWITCH_B);
        } catch (EnhancedIOException ex) {
            ex.printStackTrace();
        }
    return false;
    }

    public void deployAcquirerReverse() {
        donnie.roller.startReverse();
    }




}


