package stuy;

import edu.wpi.first.wpilibj.*;

public class VictorSpeed implements SpeedController, Constants, PIDSource {

    Encoder e;
    Victor v;
    PIDController c;
    double lastDistance, lastTime;

    public VictorSpeed(int victorChannel, int encoderAChannel, int encoderBChannel) {
        v = new Victor(victorChannel);

        e = new Encoder(encoderAChannel, encoderBChannel);
        e.setDistancePerPulse(ENCODER_RPM_PER_PULSE);
        e.setPIDSourceParameter(Encoder.PIDSourceParameter.kRate); // use e.getRate() for feedback
        e.start();
        lastDistance = e.getDistance();
        lastTime = Timer.getFPGATimestamp();

        c = new PIDController(PDRIVE, IDRIVE, DDRIVE, this, this);
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

    public double pidGet() {
        double currentTime = Timer.getFPGATimestamp();
        double currentDistance = e.getDistance();

        double speed = (currentDistance - lastDistance) / (currentTime - lastTime);

        lastTime = Timer.getFPGATimestamp();
        lastDistance = e.getDistance();

        return speed;
    }

    public double get() {
        return v.get();
    }

    public void disable() {
        v.disable();
    }
}
