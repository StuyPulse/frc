/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
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
   // int DRIVE_3_CHANNEL = 3;
   // int DRIVE_4_CHANNEL = 4;

    int ACQUIRER_CHANNEL = 5;
    int KICKMOTOR_CHANNEL = 3;

    /*** DIGITAL IO ***/
    int LIMSWITCH_CHANNEL = 12;

    int BIT_1_CHANNEL = 14;
    int BIT_2_CHANNEL = 7;
    int BIT_3_CHANNEL = 8;
    int BIT_4_CHANNEL = 9;

    int ENCODER_CHANNEL_1A = 10;
    int ENCODER_CHANNEL_1B = 4;
    int ENCODER_CHANNEL_2A = 11;
    int ENCODER_CHANNEL_2B = 13;

    /*** ANALOG ***/
    int GYRO_CHANNEL = 2;

}