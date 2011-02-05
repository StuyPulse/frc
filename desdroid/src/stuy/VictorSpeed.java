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
public class VictorSpeed implements SpeedController, PIDSource, Constants {

    Encoder e;
    Victor v;
    PIDController c;

    public VictorSpeed(int victorChannel, int encoderAChannel, int encoderBChannel) {
        v = new Victor(victorChannel);

        e = new Encoder(encoderAChannel, encoderBChannel);
        e.setDistancePerPulse(Constants.ENCODER_CODES_PER_REV);
        e.start();

        c = new PIDController(PDRIVE, IDRIVE, DDRIVE, this, this);
        c.setInputRange(-DriveTrain.kMaxRPM, DriveTrain.kMaxRPM);
        c.setOutputRange(-1, 1);
        c.enable();
    }

    public double pidGet() {
        return e.getDistance();
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
