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

   double SCALE = 10000;

   
    public boolean highGear = false;
    //public Gyro gyro;
    Encoder encoderLeft;
    Encoder encoderRight;
    Servo shifterLeft;
    Servo shifterRight;
    PIDController straightController;
    final double DISTANCE_PER_PULSE = 12.0 / 530.0; // 250 pulses per revolution, 530 pulses per foot
    Donovan donnie;


    public DonovanDriveTrain(int motor1, int motor2, int motor3, int motor4, Donovan d) {
        super(motor1, motor2, motor3, motor4);
        donnie = d;
        encoderLeft = new Encoder(ENCODER_CHANNEL_1A, ENCODER_CHANNEL_1B, true);
        encoderRight = new Encoder(ENCODER_CHANNEL_2A, ENCODER_CHANNEL_2B, true);
        shifterLeft = new Servo(SHIFTERLEFT_CHANNEL);
        shifterRight = new Servo(SHIFTERRIGHT_CHANNEL);

        encoderLeft.setDistancePerPulse(DISTANCE_PER_PULSE);
        encoderRight.setDistancePerPulse(DISTANCE_PER_PULSE);

        setInvertedMotor(RobotDrive.MotorType.kFrontRight, true);
        setInvertedMotor(RobotDrive.MotorType.kRearRight, true);
        setInvertedMotor(RobotDrive.MotorType.kFrontLeft, true);
        setInvertedMotor(RobotDrive.MotorType.kRearLeft, true);

        encoderLeft.start();
        encoderRight.start();

        straightController = new PIDController(PVAL, IVAL, DVAL, donnie.gyro, new PIDOutput() {

            public void pidWrite(double output) {
                arcadeDrive(0, output);
                System.out.println("output: " + output);
            }
        }, 0.005);

        straightController.setInputRange(-360.0, 360.0);
        straightController.setTolerance(1 / 90. * 100);
        straightController.disable();


        if (shifterLeft.get() == 1 && shifterRight.get() == 1) {
            highGear = true;
        }
    }

    /*
     * This constructor for testing on Michael1, which not have quad encoders.
     */
    public DonovanDriveTrain(int motor1, int motor2, int gyroport) {
        super(motor1, motor2);
        shifterLeft = new Servo(SHIFTERLEFT_CHANNEL);
        shifterRight = new Servo(SHIFTERRIGHT_CHANNEL);

        encoderLeft = new Encoder(ENCODER_CHANNEL_1A, ENCODER_CHANNEL_1B);
        encoderRight = new Encoder(ENCODER_CHANNEL_2A, ENCODER_CHANNEL_2B);

        encoderLeft.setDistancePerPulse(DISTANCE_PER_PULSE);
        encoderRight.setDistancePerPulse(DISTANCE_PER_PULSE);


        //must set distance per pulse for encoders
        //gyro = new Gyro(gyroport);

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
    public void forwardInchesStraight(int inches) {
        encoderRight.reset();
        encoderLeft.reset();
        double lm;
        double rm;
        int i = 0;
        while ((getAvgDistance() < inches) && donnie.isAutonomous() && donnie.isEnabled()) {
            if(i%10 == 0)
                System.out.println("diff: " + (encoderLeft.get()-encoderRight.get()));
            else if(i%50 == 0)
                    System.out.println("left: " + encoderLeft.get() + "  right: " + encoderRight.get());
            lm = .5 + ((encoderRight.get() - encoderLeft.get()) / (SCALE));
            rm = .5 + ((encoderLeft.get() - encoderRight.get()) / SCALE);
            tankDrive((-1*lm), (-1*rm));
            i++;
        }
        tankDrive(0, 0);
    }

    /*
    public void forwardInchesTest(int inches) {

    encoderLeft.reset();
    encoderRight.reset();
    donnie.gyro.reset();


    straightController.setSetpoint(donnie.gyro.getAngle()); //0 ?

    while (getAvgDistance() < inches) {
    straightController.disable();

    System.out.println("onTarget: " + straightController.onTarget());
    System.out.println("gyro angle: " + donnie.gyro.getAngle());
    if (straightController.onTarget()) {
    straightController.disable();
    arcadeDrive(-0.5, 0); //speed may need adjustment
    } else {
    straightController.enable();
    }
    arcadeDrive(0, 0);
    }
    }
     */
    public void forwardInches(int inches) {
        encoderLeft.reset();
        encoderRight.reset();

        while ((getAvgDistance() < inches)&& donnie.isAutonomous() && donnie.isEnabled()) {
            arcadeDrive(-0.5, 0); //speed may need adjustment
        }
        arcadeDrive(0, 0);
    }

    /**
     * This move the robot backward in inches
     */
    public void backInches(int inches) {


        encoderLeft.reset();
        encoderRight.reset();

        while ((getAvgDistance() > -inches)&& donnie.isAutonomous() && donnie.isEnabled()) {
            arcadeDrive(0.5, 0); //speed may need adjustment
        }
        arcadeDrive(0, 0);


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
        //System.out.println("left: " + encoderLeft.getDistance() + " right: " + encoderRight.getDistance());
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

    public boolean getGear() {
        return highGear;
    }
}
