package stuy;

public interface Constants {


    final int DRIVE_CAN_DEVICE_FRONT_LEFT    = 6;
    final int DRIVE_CAN_DEVICE_FRONT_RIGHT   = 8;
    final int DRIVE_CAN_DEVICE_REAR_LEFT     = 7;
    final int DRIVE_CAN_DEVICE_REAR_RIGHT    = 5;

    final int ARM_CAN_DEVICE_NUMBER          = 6;

    final int GRABBER_UPPER_ROLLER_DEVICE    = 7;
    final int GRABBER_LOWER_ROLLER_DEVICE    = 8;

    /*** DIGITAL I/O ***/
    final int LINE_SENSOR_LEFT_CHANNEL       = 1;
    final int LINE_SENSOR_MIDDLE_CHANNEL     = 2;
    final int LINE_SENSOR_RIGHT_CHANNEL      = 3;
    final int HALOGEN_CHANNEL_A              = 4;
    final int HALOGEN_CHANNEL_B              = 5;

    final int GYRO_CHANNEL                   = 4;

    final int PORT_GAMEPAD                   = 1;
    final int PORT_JOYSTICK                  = 1;
    final int PORT_ARM_STICK                 = 2;

    // Gains and setpoint for the target feedback loop.  Not yet tuned.
    final double PVAL                        = .5;
    final double IVAL                        = 0;
    final double DVAL                        = 0;
    final double PID_SETPOINT                = 0;

    final int ENCODER_CODES_PER_REV          = 250;

    final double PDRIVE                      = 0.5;
    final double IDRIVE                      = 0;
    final double DDRIVE                      = 0;
}
