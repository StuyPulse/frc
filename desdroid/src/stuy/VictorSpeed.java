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
    DigitalInput A, B;
    

    double lastTime;

    public VictorSpeed(int victorChannel, int encoderAChannel, int encoderBChannel, boolean reverse) {
        v = new Victor(victorChannel);
        A= new DigitalInput(encoderAChannel);
        B= new DigitalInput(encoderBChannel);
        //e = new DESencoder(encoderAChannel, encoderBChannel, reverse, CounterBase.EncodingType.k2X);
        e= new Encoder(A, B,reverse,CounterBase.EncodingType.k2X);
        e= new Encoder(A,B,reverse,CounterBase.EncodingType.k2X);
        e.setDistancePerPulse(ENCODER_RPM_PER_PULSE);
        e.setPIDSourceParameter(Encoder.PIDSourceParameter.kRate); // use e.getRate() for feedback
        e.start();

        c = new PIDController(PDRIVE, IDRIVE, DDRIVE, e, this);
        c.setInputRange(-DriveTrain.kMaxRPM, DriveTrain.kMaxRPM);
        c.setOutputRange(-1, 1);
//        c.enable();
    }

/*    public VictorSpeed( int encoderAChannel, int encoderBChannel, boolean reverse) {
        e = new DESencoder(encoderAChannel, encoderBChannel, reverse, CounterBase.EncodingType.k2X);

        e.setDistancePerPulse(ENCODER_RPM_PER_PULSE);
        e.setPIDSourceParameter(Encoder.PIDSourceParameter.kRate); // use e.getRate() for feedback
        e.start();
/*
        c = new PIDController(PDRIVE, IDRIVE, DDRIVE, e, this);
        c.setInputRange(-DriveTrain.kMaxRPM, DriveTrain.kMaxRPM);
        c.setOutputRange(-1, 1);
        c.enable();
    }*/
    
    public void pidWrite(double output) {
        v.set(output);
    }
    //public void free(){
      //  e.free();
    //}


//    public double getRate() {
//        boolean itsMyFirstTimeBeGentle;
//        double timeDifference = Timer.getFPGATimestamp() - lastTime;
//        lastTime = Timer.getFPGATimestamp();
//        return timeDifference;
//    }

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

