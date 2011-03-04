package stuy;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.RobotDrive.*;

/**
 * A custom drive train class for our mecanum wheels.  Uses PID based speed
 * control on each of the four wheels.
 */
public class DriveTrain extends RobotDrive implements Constants {

    int kFrontLeft_val = 0;
    int kFrontRight_val = 1;
    int kRearLeft_val = 2;
    int kRearRight_val = 3;
    VictorSpeed driveFrontLeft, driveRearLeft, driveFrontRight, driveRearRight;
    VictorSpeed dummyFLeft, dummyRLeft, dummyFRight, dummyRRight;
    /**
     * Whether the robot is driven with speed control.  False = voltage control.
     */
    boolean speedControl;
    /**
     * The maximum number of RPM (revolutions per minute) to set as the setpoint
     * speed on any of the wheels.  1 if in voltage mode.
     */
    int kMaxRPM = 600;
    /**
     * Multiply each wheel speed by its relative multiplier. (indexed by
     * kFrontLeft_val, kFrontRight_val, kRearLeft_val, kRearRight_val.
     */
    double[] weightGains = {1, 1, 1.05, 1.05}; // 4 weight gains
    /**
     * Ignore joystick inputs that are less than this number in absolute value.
     * Scale the rest of the inputs to still allow for the full output range (-1 to 1)
     */
    static double minJoystickValue = 0.1;

    public DriveTrain(SpeedController frontLeftMotor, SpeedController rearLeftMotor,
            SpeedController frontRightMotor, SpeedController rearRightMotor) {
        super(frontLeftMotor, rearLeftMotor, frontRightMotor, rearRightMotor);
    }

    public DriveTrain(boolean speedControl) {
        super(null, null, null, null);
        this.speedControl = speedControl;

        if (speedControl) {
            kMaxRPM = 600;

            // Do NOT change the order of these constructors!
            driveFrontLeft = new VictorSpeed(CHANNEL_FRONT_LEFT, CHANNEL_FRONT_LEFT_ENC_A, CHANNEL_FRONT_LEFT_ENC_B, true);
            dummyFLeft = new VictorSpeed(CHANNEL_FRONT_LEFT_ENC_A, CHANNEL_FRONT_LEFT_ENC_B, true);
            driveFrontRight = new VictorSpeed(CHANNEL_FRONT_RIGHT, CHANNEL_FRONT_RIGHT_ENC_A, CHANNEL_FRONT_RIGHT_ENC_B, false);
            dummyFRight = new VictorSpeed(CHANNEL_FRONT_RIGHT_ENC_A, CHANNEL_FRONT_RIGHT_ENC_B, false);
            driveRearLeft = new VictorSpeed(CHANNEL_REAR_LEFT, CHANNEL_REAR_LEFT_ENC_A, CHANNEL_REAR_LEFT_ENC_B, true);
            dummyRLeft = new VictorSpeed(CHANNEL_REAR_LEFT_ENC_A, CHANNEL_REAR_LEFT_ENC_B, true);
            dummyRRight = new VictorSpeed(CHANNEL_REAR_RIGHT_ENC_A, CHANNEL_REAR_RIGHT_ENC_B, true);
            driveRearRight = new VictorSpeed(CHANNEL_REAR_RIGHT, CHANNEL_REAR_RIGHT_ENC_A, CHANNEL_REAR_RIGHT_ENC_B, true);

            m_frontLeftMotor = driveFrontLeft;
            m_frontRightMotor = driveFrontRight;
            m_rearLeftMotor = driveRearLeft;
            m_rearRightMotor = driveRearRight;


            driveFrontLeft.c.disable();
            driveFrontRight.c.disable();
            driveRearLeft.c.disable();
            driveRearRight.c.disable();

            driveFrontLeft.c.setInputRange(-kMaxRPM, kMaxRPM);
            driveFrontRight.c.setInputRange(-kMaxRPM, kMaxRPM);
            driveRearLeft.c.setInputRange(-kMaxRPM, kMaxRPM);
            driveRearRight.c.setInputRange(-kMaxRPM, kMaxRPM);

            driveFrontLeft.c.setPID(SPEED_P, SPEED_I, SPEED_D);
            driveFrontRight.c.setPID(SPEED_P, SPEED_I, SPEED_D);
            driveRearLeft.c.setPID(SPEED_P, SPEED_I, SPEED_D);
            driveRearRight.c.setPID(SPEED_P, SPEED_I, SPEED_D);

            driveFrontLeft.c.enable();
            driveFrontRight.c.enable();
            driveRearLeft.c.enable();
            driveRearRight.c.enable();
        } else {
            kMaxRPM = 1;

            m_frontLeftMotor = new Victor(CHANNEL_FRONT_LEFT);
            m_frontRightMotor = new Victor(CHANNEL_FRONT_RIGHT);
            m_rearLeftMotor = new Victor(CHANNEL_REAR_LEFT);
            m_rearRightMotor = new Victor(CHANNEL_REAR_RIGHT);
        }

        setInvertedMotor(MotorType.kFrontRight, true);
        setInvertedMotor(MotorType.kRearRight, true);
    }

    /**
     * Call this method to drive the robot.
     * @param x Horizontal component of the speed ("strafing")
     * @param y Forward component of speed
     * @param rotation Rotational speeds
     * @param gyroAngle Gyro angle in order to do field-oriented drive (rotate
     * speed vector by this angle to maintain constant orientation relative to
     * the driver).  Measured in degrees.
     * @param deadband Whether to apply deadband (scaleInput()) on the driver inputs.
     * All speed values (x, y, rotation) are from -1 to 1.
     */
    public void mecanumDrive_Cartesian(double x, double y, double rotation, double gyroAngle, boolean deadband) {
        double xIn;
        double yIn;
        if (deadband) {
            xIn = scaleInput(x);
            yIn = scaleInput(y);
            rotation = scaleInput(rotation);
        } else {
            xIn = x;
            yIn = y;
        }

        // Negate y for the joystick.
        yIn = -yIn;
        // Compenstate for gyro angle.
        double rotated[] = rotateVector(xIn, yIn, gyroAngle);
        xIn = rotated[0];
        yIn = rotated[1];

        double wheelSpeeds[] = new double[kMaxNumberOfMotors];
        wheelSpeeds[kFrontLeft_val] = (xIn + yIn + rotation) * weightGains[0];
        wheelSpeeds[kFrontRight_val] = (-xIn + yIn - rotation) * weightGains[1];
        wheelSpeeds[kRearLeft_val] = (-xIn + yIn + rotation) * weightGains[2];
        wheelSpeeds[kRearRight_val] = (xIn + yIn - rotation) * weightGains[3];

        normalize(wheelSpeeds);

        m_frontLeftMotor.set(kMaxRPM * wheelSpeeds[kFrontLeft_val] * m_invertedMotors[kFrontLeft_val] * m_maxOutput);
        m_frontRightMotor.set(kMaxRPM * wheelSpeeds[kFrontRight_val] * m_invertedMotors[kFrontRight_val] * m_maxOutput);
        m_rearLeftMotor.set(kMaxRPM * wheelSpeeds[kRearLeft_val] * m_invertedMotors[kRearLeft_val] * m_maxOutput);
        m_rearRightMotor.set(kMaxRPM * wheelSpeeds[kRearRight_val] * m_invertedMotors[kRearRight_val] * m_maxOutput);

    }

    /**
     * Resets the values of the drive encoders to zero.
     */
    public void resetEncoders() {
        if (speedControl) {
            driveFrontLeft.e.reset();
            driveFrontRight.e.reset();
            driveRearLeft.e.reset();
            driveRearRight.e.reset();
        }
    }

    /**
     * Gets the average distance from the encoders.
     * @return Returns the average distance from the encoders.
     */
    public double getAvgDistance() {
        double avg = 0;
        if (speedControl) {
            avg += driveFrontLeft.e.getDistance();
            avg -= driveFrontRight.e.getDistance();
            avg += driveRearLeft.e.getDistance();
            avg -= driveRearRight.e.getDistance();
        }
        avg /= 4.0;                   // Calcuating the average
        avg *= Math.PI;               // Multiply distance by pi, in preparation for calculating
        // the circumference

        avg /= 10.0;                  // Multiplies by 6, the wheel diameter, then divides by 60
        // seconds a minute

        return avg;
    }

    /**
     * This is a joke method, do not use :P
     * Three joystick drive! Drive the left and right sides like tank drive,
     * plus horizontal strafing from a third input.
     */
    public void tankDrive3(double left, double right, double strafe) {
        if (scaleInput(strafe) == 0) {
            tankDrive(scaleInput(left), scaleInput(right));
        } else {
            mecanumDrive_Cartesian(scaleInput(strafe), 0, 0, 0);
        }
    }

    /**
     * Modify a joystick input to round any super-small values to 0.  Should prevent
     * robot from jittering when the joysticks have a small default value.
     *
     * Though small values are pulled down to 0, inputs higher than the specified
     * threshold will still cover the entire range of outputs, though the rate
     * at which the output grows is slightly steeper.  This change should be small
     * enough to still allow for good manual control.
     *
     * The graph of scaleInput's value (vertical axis) versus original joystick
     * input (horizontal axis) looks like this:
     *
     *                /
     *               /
     *   -1   _ _ _ /  1
     *       /
     *      /
     *     /
     *
     * @param x A joystick value from -1 to 1.
     * @return Close to the original input, but scaled to make small values return
     * 0 while still allowing the full range of outputs, -1 to 1.
     */
    public static double scaleInput(double x) {
        if (Math.abs(x) < minJoystickValue) {
            return 0;
        }

        double scaledSlope = 1 / (1 - minJoystickValue);
        if (x > 0) {
            return (x - minJoystickValue) * scaledSlope;
        }
        return (x + minJoystickValue) * scaledSlope;
    }
}
