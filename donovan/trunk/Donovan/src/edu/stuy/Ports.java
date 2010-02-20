/*
 * Port/channel mappings for Donovan
 * Subject to change
 */

package edu.stuy;

/**
 *
 * @author Developer
 */
public interface Ports {
    //PWM OUT is 1-14
    //DIGITAL IO is 1-10
    //ANALOG is 1-8

    /*** VERY SUBJECT TO CHANGE ***/
     static final int TO_FEET = 12;

    /*** USB PORTS ***/
    int LSTICK_PORT = 1;
    int RSTICK_PORT = 2;
    int SHOOTSTICK_PORT = 3;

    /*** PWM OUT ***/
    int DRIVE_1_CHANNEL = 1;
    int DRIVE_2_CHANNEL = 2;
    int DRIVE_3_CHANNEL = 3;
    int DRIVE_4_CHANNEL = 4;

    int SHIFTERLEFT_CHANNEL = 6;
    int SHIFTERRIGHT_CHANNEL = 5;
    int A_FRAME_CHANNEL = 8;

    int WINCH_CHANNEL = 10;

    int ACQUIRER_CHANNEL = 9;
    int KICKMOTOR_CHANNEL = 7;

    /*** DIGITAL IO ***/
    int LIMSWITCH_CHANNEL = 5;



    int ENCODER_CHANNEL_1A = 1;
    int ENCODER_CHANNEL_1B = 2;
    int ENCODER_CHANNEL_2A = 3;
    int ENCODER_CHANNEL_2B = 4;

    /*** ANALOG ***/
    int GYRO_CHANNEL = 1;
    int ACCEL_CHANNEL = 2; //does not exist

    /*** FIRSTtouch ***/
    int A_FRAME_SWITCH = 2;
    int ACQUIRER_SWITCH_A = 8; //reverse?
    int ACQUIRER_SWITCH_B = 6; //forward?
    int WINCH_SWITCH = 4;
    int KICK_SWITCH = 3;
    int E_COCK_SWITCH = 1;

    int INDICATOR_LIGHT = 11; //connected to LED3 pin,

    int LED1 = 7; //order possibly reversed
    int LED2 = 9; //all set to outputs
    int LED3 = 11;
    int LED4 = 13;
    int LED5 = 15;

    int BIT_4_CHANNEL = 16; //possibly reversed
    int BIT_3_CHANNEL = 14;
    int BIT_2_CHANNEL = 12;
    int BIT_1_CHANNEL = 10;


    boolean COCKED = true;
    boolean NOT_COCKED = false;
}