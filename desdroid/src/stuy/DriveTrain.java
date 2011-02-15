package stuy;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.RobotDrive.*;
import edu.wpi.first.wpilibj.can.*;
import java.lang.Math;

public class DriveTrain extends RobotDrive {

    int kFrontLeft_val = 0;
    int kFrontRight_val = 1;
    int kRearLeft_val = 2;
    int kRearRight_val = 3;
    static int kMaxRPM = 600;
    /**
     * Ignore joystick inputs that are less than this number in absolute value.
     * Scale the rest of the inputs to still allow for the full output range (-1 to 1)
     */
    static double minJoystickValue = 0.1;

    public DriveTrain(SpeedController frontLeftMotor, SpeedController rearLeftMotor,
            SpeedController frontRightMotor, SpeedController rearRightMotor) {
        super(frontLeftMotor, rearLeftMotor, frontRightMotor, rearRightMotor);
        setInvertedMotor(MotorType.kFrontRight, m_isCANInitialized);
        setInvertedMotor(MotorType.kRearRight, m_isCANInitialized);
    }



    public void mecanumDrive_Cartesian(double x, double y, double rotation, double gyroAngle, boolean deadband) {
        double xIn;
        double yIn;
        if (deadband) {
            xIn = scaleInput(x);
            yIn = scaleInput(y);
            rotation = scaleInput(rotation);
        }
        else {
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
        wheelSpeeds[kFrontLeft_val] = (xIn + yIn + rotation) * 1.1;
        wheelSpeeds[kFrontRight_val] = (-xIn + yIn - rotation) * 1.1;
        wheelSpeeds[kRearLeft_val] = (-xIn + yIn + rotation) * 1;
        wheelSpeeds[kRearRight_val] = (xIn + yIn - rotation) * 1;

        normalize(wheelSpeeds);

        byte syncGroup = (byte) 0x80;

        m_frontLeftMotor.set(kMaxRPM * wheelSpeeds[kFrontLeft_val] * m_invertedMotors[kFrontLeft_val] * m_maxOutput, syncGroup);
        m_frontRightMotor.set(kMaxRPM * wheelSpeeds[kFrontRight_val] * m_invertedMotors[kFrontRight_val] * m_maxOutput, syncGroup);
        m_rearLeftMotor.set(kMaxRPM * wheelSpeeds[kRearLeft_val] * m_invertedMotors[kRearLeft_val] * m_maxOutput, syncGroup);
        m_rearRightMotor.set(kMaxRPM * wheelSpeeds[kRearRight_val] * m_invertedMotors[kRearRight_val] * m_maxOutput, syncGroup);

        if (m_isCANInitialized) {
            try {
                CANJaguar.updateSyncGroup(syncGroup);
            } catch (CANNotInitializedException e) {
                m_isCANInitialized = false;
            } catch (CANTimeoutException e) {

            } catch (Exception e) {
            System.out.println(e);
            }


        }

        if (m_safetyHelper != null) {
            m_safetyHelper.feed();
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
    private static double scaleInput(double x) {
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
