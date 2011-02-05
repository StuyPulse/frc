/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package stuy;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.RobotDrive.*;
import edu.wpi.first.wpilibj.can.*;

/**
 *
 * @author Blake
 */
public class DriveTrain extends RobotDrive {

    int kFrontLeft_val = 0;
    int kFrontRight_val = 1;
    int kRearLeft_val = 2;
    int kRearRight_val = 3;
    int kMaxRPM = 600;
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

    public void mecanumDrive_Cartesian(double x, double y, double rotation, double gyroAngle) {
        double xIn = scaleInput(x);
        double yIn = scaleInput(y);
        rotation = scaleInput(rotation);

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
            }
        }

        if (m_safetyHelper != null) {
            m_safetyHelper.feed();
        }
    }

    /**
     * Drive the left and right sides like tank drive, plus horizontal strafing
     * from a third input.
     */
    public void tankDrive3(double left, double right, double strafe) {
        if (scaleInput(strafe) == 0)
            tankDrive(scaleInput(left), scaleInput(right));
        else
            mecanumDrive_Cartesian(scaleInput(strafe), 0, 0, 0);
    }

    public void arcadeDrive(double moveValue, double rotateValue, boolean squaredInputs) {
        // local variables to hold the computed PWM values for the motors
        double leftMotorSpeed;
        double rightMotorSpeed;

        moveValue = limit(moveValue);
        rotateValue = limit(rotateValue);

        if (squaredInputs) {
            // square the inputs (while preserving the sign) to increase fine control while permitting full power
            if (moveValue >= 0.0) {
                moveValue = (moveValue * moveValue);
            } else {
                moveValue = -(moveValue * moveValue);
            }
            if (rotateValue >= 0.0) {
                rotateValue = (rotateValue * rotateValue);
            } else {
                rotateValue = -(rotateValue * rotateValue);
            }
        }

        if (moveValue > 0.0) {
            if (rotateValue > 0.0) {
                leftMotorSpeed = moveValue - rotateValue;
                rightMotorSpeed = Math.max(moveValue, rotateValue);
            } else {
                leftMotorSpeed = Math.max(moveValue, -rotateValue);
                rightMotorSpeed = moveValue + rotateValue;
            }
        } else {
            if (rotateValue > 0.0) {
                leftMotorSpeed = -Math.max(-moveValue, rotateValue);
                rightMotorSpeed = moveValue + rotateValue;
            } else {
                leftMotorSpeed = moveValue - rotateValue;
                rightMotorSpeed = -Math.max(-moveValue, -rotateValue);
            }
        }
         byte syncGroup = (byte) 0x80;

        m_frontLeftMotor.set(kMaxRPM * leftMotorSpeed * m_invertedMotors[kFrontLeft_val] * m_maxOutput, syncGroup);
        m_frontRightMotor.set(kMaxRPM * rightMotorSpeed * m_invertedMotors[kFrontRight_val] * m_maxOutput, syncGroup);
        m_rearLeftMotor.set(kMaxRPM * leftMotorSpeed * m_invertedMotors[kRearLeft_val] * m_maxOutput, syncGroup);
        m_rearRightMotor.set(kMaxRPM * rightMotorSpeed * m_invertedMotors[kRearRight_val] * m_maxOutput, syncGroup);

        //setLeftRightMotorOutputs(leftMotorSpeed * kMaxRPM, rightMotorSpeed * kMaxRPM);
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
