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
    int A_FRAME_CHANNEL = 7;

    int ACQUIRER_CHANNEL = 9;
    int KICKMOTOR_CHANNEL = 10;

    /*** DIGITAL IO ***/
    int LIMSWITCH_CHANNEL = 5;



    int ENCODER_CHANNEL_1A = 1;
    int ENCODER_CHANNEL_1B = 2;
    int ENCODER_CHANNEL_2A = 3;
    int ENCODER_CHANNEL_2B = 4;

    /*** ANALOG ***/
    int GYRO_CHANNEL = 1;
    int ACCEL_CHANNEL = 2;

    /*** FIRSTtouch ***/
    int A_FRAME = 9;
    int ACQUIRER_SWITCH_A = 11;
    int ACQUIRER_SWITCH_B = 12;
    int WINCH_REEL = 13;
    int KICK = 14;
    int EMERGENCY_COCK = 15;

}