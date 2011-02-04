/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package stuy;

import edu.wpi.first.wpilibj.*;
import edu.wpi.first.wpilibj.RobotDrive.*;
import edu.wpi.first.wpilibj.can.*;
import java.lang.Math;

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

    public DriveTrain(SpeedController frontLeftMotor, SpeedController rearLeftMotor,
            SpeedController frontRightMotor, SpeedController rearRightMotor) {
        super(frontLeftMotor, rearLeftMotor, frontRightMotor, rearRightMotor);
    }

    public void mecanumDrive_Cartesian(double x, double y, double rotation, double gyroAngle)
    {
        double xIn = x * Math.abs(x);
        double yIn = y * Math.abs(y);
        
        // Negate y for the joystick.
        yIn = -yIn;
        // Compenstate for gyro angle.
        double rotated[] = rotateVector(xIn, yIn, gyroAngle);
        xIn = rotated[0];
        yIn = rotated[1];

        double wheelSpeeds[] = new double[kMaxNumberOfMotors];
        wheelSpeeds[kFrontLeft_val] = xIn + yIn + rotation;
        wheelSpeeds[kFrontRight_val] = -xIn + yIn - rotation;
        wheelSpeeds[kRearLeft_val] = -xIn + yIn + rotation;
        wheelSpeeds[kRearRight_val] = xIn + yIn - rotation;

        normalize(wheelSpeeds);

        byte syncGroup = (byte)0x80;

        m_frontLeftMotor.set(kMaxRPM * wheelSpeeds[kFrontLeft_val] * m_invertedMotors[kFrontLeft_val] * m_maxOutput, syncGroup);
        m_frontRightMotor.set(kMaxRPM * wheelSpeeds[kFrontRight_val] * m_invertedMotors[kFrontRight_val] * m_maxOutput, syncGroup);
        m_rearLeftMotor.set(kMaxRPM * wheelSpeeds[kRearLeft_val] * m_invertedMotors[kRearLeft_val] * m_maxOutput, syncGroup);
        m_rearRightMotor.set(kMaxRPM * wheelSpeeds[kRearRight_val] * m_invertedMotors[kRearRight_val] * m_maxOutput, syncGroup);

        if (m_isCANInitialized) {
            try {
                CANJaguar.updateSyncGroup(syncGroup);
            } catch (CANNotInitializedException e) {
                m_isCANInitialized = false;
            } catch (CANTimeoutException e) {}
        }

        if (m_safetyHelper != null) m_safetyHelper.feed();
    }
}
