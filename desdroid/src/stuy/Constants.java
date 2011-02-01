package stuy;

public interface Constants {
    final int DRIVE_CAN_DEVICE_FRONT_LEFT    = 3;
    final int DRIVE_CAN_DEVICE_FRONT_RIGHT   = 4;
    final int DRIVE_CAN_DEVICE_REAR_LEFT     = 2;
    final int DRIVE_CAN_DEVICE_REAR_RIGHT    = 5;

    final int ARM_CAN_DEVICE_NUMBER          = 6;

    final int GRABBER_UPPER_ROLLER_DEVICE    = 7;
    final int GRABBER_LOWER_ROLLER_DEVICE    = 8;

    final int LINE_SENSOR_LEFT_CHANNEL       = 1;
    final int LINE_SENSOR_MIDDLE_CHANNEL     = 2;
    final int LINE_SENSOR_RIGHT_CHANNEL      = 3;

    final int GYRO_CHANNEL                   = 4;

    final int PORT_GAMEPAD                   = 1;
    final int PORT_JOYSTICK                  = 1;
    final int PORT_ARM_STICK                 = 2;

    // Gains and setpoint for the target feedback loop.  Not yet tuned.
    final int PVAL                           = 1;
    final int IVAL                           = 1;
    final int DVAL                           = 1;
    final double PID_SETPOINT                = 50.0;
}
