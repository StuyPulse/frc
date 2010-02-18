/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
//@TODO: use a PID to drive straight, if necessary
package edu.stuy;

import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Prog
 */
public class DonovanDriveTrain extends RobotDrive implements Ports {

    public boolean highGear = false;
    public Gyro gyro;
    Encoder encoderLeft;
    Encoder encoderRight;
    Servo shifterLeft;
    Servo shifterRight;
    Servo a_Frame;
    final double DISTANCE_PER_PULSE = 12.0 / 530.0; // 250 pulses per revolution, 530 pulses per foot

    public DonovanDriveTrain(int motor1, int motor2, int gyroport) {
        super(motor1, motor2);
        shifterLeft = new Servo(SHIFTERLEFT_CHANNEL);
        shifterRight = new Servo(SHIFTERRIGHT_CHANNEL);

        encoderLeft = new Encoder(ENCODER_CHANNEL_1A, ENCODER_CHANNEL_1B);
        encoderRight = new Encoder(ENCODER_CHANNEL_2A, ENCODER_CHANNEL_2B);

        encoderLeft.setDistancePerPulse(DISTANCE_PER_PULSE);
        encoderRight.setDistancePerPulse(DISTANCE_PER_PULSE);


        //must set distance per pulse for encoders
        gyro = new Gyro(gyroport);


    }

    /*
     * This constructor for testing on Michael1, which not have quad encoders.
     */
    public DonovanDriveTrain(int motor1, int motor2, int motor3, int motor4) {
        super(motor1, motor2, motor3, motor4);
        encoderLeft = new Encoder(ENCODER_CHANNEL_1A, ENCODER_CHANNEL_1B, true);
        encoderRight = new Encoder(ENCODER_CHANNEL_2A, ENCODER_CHANNEL_2B, true);
        shifterLeft = new Servo(SHIFTERLEFT_CHANNEL);
        shifterRight = new Servo(SHIFTERRIGHT_CHANNEL);
        a_Frame = new Servo(A_FRAME_CHANNEL);

        encoderLeft.setDistancePerPulse(DISTANCE_PER_PULSE);
        encoderRight.setDistancePerPulse(DISTANCE_PER_PULSE);

        setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
        setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);

        encoderLeft.start();
        encoderRight.start();

        if (shifterLeft.get() == 1 && shifterRight.get() == 1) {
            highGear = true;
        }
    }

    /*
     * this returns encoder values
     */
    public double getLeftEnc() {
        return encoderLeft.getDistance();
    }

    public double getRightEnc() {
        return encoderRight.getDistance();
    }

    /**
     * This move the robot forward in inches
     */
    public void forwardInches(int inches) {


        encoderLeft.reset();
        encoderRight.reset();

        while (getAvgDistance() < inches) {
            arcadeDrive(-0.5, 0); //speed may need adjustment
        }
arcadeDrive(0,0);
    }

    /**
     * This move the robot backward in inches
     */
    public void backInches(int inches) {


        encoderLeft.reset();
        encoderRight.reset();

        while (getAvgDistance() > -inches) {
            arcadeDrive(0.5, 0); //speed may need adjustment
        }
arcadeDrive(0,0);


    }

    public void resetEncoders() {
        encoderLeft.reset();
        encoderRight.reset();
    }


    /*
     * This return the averge distance read by the encoders, in inches
     */
    public void shift() {
        if (highGear) {
            shifterLeft.set(0);
            shifterRight.set(0);
        } else {
            shifterLeft.set(1);
            shifterRight.set(1);

        }
        highGear = !highGear;


    }

    public double getAvgDistance() {
        System.out.println("left: " + encoderLeft.getDistance() + " right: " + encoderRight.getDistance());
        return (encoderLeft.getDistance() + encoderRight.getDistance()) / 2.0;

    }
    /*
     *  Set gear high
     */

    public void setHigh() {

        shifterLeft.set(1);
        shifterRight.set(1);
        System.out.println("I set your gears high");
        highGear = true;
    }

    /*
     * Set gear low
     */
    public void setLow() {
        shifterLeft.set(0);
        shifterRight.set(0);
        System.out.println("I set your gears low");
        highGear = false;
    }
}
