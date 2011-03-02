/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stuy;

import edu.wpi.first.wpilibj.*;

/**
 *
 * @author Blake
 */
public class VictorSpeed implements SpeedController, Constants {

    Encoder e;
    Victor v;
    PIDController c;
    
    double lastTime;

    /**
     * Make an actual speed controller complete with a Victor, Encoder and PIDController
     * @param victorChannel The PWM chanel for the victor.
     * @param encoderAChannel Digital in for the encoder.
     * @param encoderBChannel Input for the other encoder.
     * @param reverse Not used right.  Was for reversing encoder direction.
     */
    public VictorSpeed(int victorChannel, int encoderAChannel, int encoderBChannel, boolean reverse) {
        v = new Victor(victorChannel);
        
        e= new Encoder(4,encoderAChannel,4,encoderBChannel,reverse,CounterBase.EncodingType.k2X);
        e.setDistancePerPulse(ENCODER_RPM_PER_PULSE);
        e.setPIDSourceParameter(Encoder.PIDSourceParameter.kRate); // use e.getRate() for feedback
        e.start();

        c = new PIDController(SPEED_P, SPEED_I, SPEED_D, e, this);
        c.setInputRange(-DriveTrain.kMaxRPM, DriveTrain.kMaxRPM);
        c.setOutputRange(-1, 1);
        c.enable();
    }

    /**
     * Make a FAKE one just to construct dummy encoders.  Only the first, third,
     * fifth and eighth encoders to be constructed will work properly when we
     * call getRate(); this is an acknowledged bug in the NI software and requires
     * us to make fake Encoders on a different slot.
     * @param encoderAChannel
     * @param encoderBChannel
     * @param reverse
     */
    public VictorSpeed(int encoderAChannel, int encoderBChannel, boolean reverse) {
        e = new Encoder(6,encoderAChannel, 6,encoderBChannel, reverse, CounterBase.EncodingType.k2X);
        e.setDistancePerPulse(ENCODER_RPM_PER_PULSE);
        e.setPIDSourceParameter(Encoder.PIDSourceParameter.kRate); // use e.getRate() for feedback
        e.start();
    }
    
    public void pidWrite(double output) {
        v.set(output);
    }

    /**
     * Set a wheel's speed setpoint.
     * @param speedRPM The desired wheel speed in RPM (revolutions per minute).
     */
    public void set(double speedRPM) {
        c.setSetpoint(speedRPM);
    }

    /**
     * Never call this method.  We need to have one in order to implement the
     * SpeedController interface and pass this class into a DriveTrain, etc.,
     * but we are using Victors which do not use syncGroups.
     */
    public void set(double speed, byte syncGroup) {
        set(speed);
    }

    public double get() {
        return v.get();
    }

    public void disable() {
        v.disable();
    }
}

