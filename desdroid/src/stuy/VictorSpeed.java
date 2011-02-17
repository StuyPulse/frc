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

    public VictorSpeed(int victorChannel, int encoderAChannel, int encoderBChannel) {
        v = new Victor(victorChannel);
        e = new Encoder(encoderAChannel, encoderBChannel);
        e.setDistancePerPulse(ENCODER_RPM_PER_PULSE);
        e.setPIDSourceParameter(Encoder.PIDSourceParameter.kRate); // use e.getRate() for feedback
        e.start();

        c = new PIDController(SPEED_P, SPEED_I, SPEED_D, e, this);
        c.setInputRange(-DriveTrain.kMaxRPM, DriveTrain.kMaxRPM);
        c.setOutputRange(-1, 1);
        c.enable();
    }

    public void pidWrite(double output) {
        v.set(output);
    }

    public void set(double speedRPM) {
        c.setSetpoint(speedRPM);
    }

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
