package stuy;

public interface Constants {

    // Robot Hardware Configuration
    final int DRIVE_CAN_DEVICE_FRONT_LEFT    = 7;
    final int DRIVE_CAN_DEVICE_FRONT_RIGHT   = 9;
    final int DRIVE_CAN_DEVICE_REAR_LEFT     = 8;
    final int DRIVE_CAN_DEVICE_REAR_RIGHT    = 10;

    final int ENCODER_CODES_PER_REV          = 250;

    final int ARM_CAN_DEVICE_NUMBER          = 6;

    final int GRABBER_UPPER_ROLLER_DEVICE    = 7;
    final int GRABBER_LOWER_ROLLER_DEVICE    = 8;

    final int MINIBOT_RELEASE_SERVO          = 4;

    final int LINE_SENSOR_LEFT_CHANNEL       = 12;
    final int LINE_SENSOR_MIDDLE_CHANNEL     = 13;
    final int LINE_SENSOR_RIGHT_CHANNEL      = 14;

    final int LOWER_ARM_POT_LIM              = 100;
    final int UPPER_ARM_POT_LIM              = 200;

    final int GYRO_CHANNEL                   = 4;

    // User Controls
    final int PORT_LEFT_STICK                = 1;
    final int PORT_RIGHT_STICK               = 2;
    final int PORT_ARM_STICK                 = 3;

    // EnhancedIO pins
    final int BIT_4_CHANNEL                  = 16; // From Donovan OI box
    final int BIT_3_CHANNEL                  = 14;
    final int BIT_2_CHANNEL                  = 12;
    final int BIT_1_CHANNEL                  = 10;

    // Line Tracking
    final double DEFAULT_STEERING_GAIN  = 0.3;
    final double FORK_PROFILE[]         = {.4, .3, .1, .1, .1, .3, .1, 0};
    final double STRAIGHT_PROFILE[]     = {.7, .7, .7, .7, .4, 0, 0, 0};

    //Speed position control
    final double SPEED_P                     = 0.48;
    final double SPEED_I                     = 0.005;
    final double SPEED_D                     = 0.05;

    //Exception led
    final int BROKEN_LIGHT                   = 10;

    //TODO: Numbers need to be set.
    final int OI_SIDE_BOTTOM_BUTTON          = 1;
    final int OI_SIDE_MIDDLE_BUTTON          = 2;
    final int OI_SIDE_TOP_BUTTON             = 3;
    final int OI_MIDDLE_BOTTOM_BUTTON        = 4;
    final int OI_MIDDLE_MIDDLE_BUTTON        = 5;
    final int OI_MIDDLE_TOP_BUTTON           = 6;
    final int OI_FEEDER_TUBE_BUTTON          = 7;
}
