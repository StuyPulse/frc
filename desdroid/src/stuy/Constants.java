package stuy;

public interface Constants {

    // Robot Hardware Configuration
    final int DRIVE_CAN_DEVICE_FRONT_LEFT    = 4;
    final int DRIVE_CAN_DEVICE_FRONT_RIGHT   = 2;
    final int DRIVE_CAN_DEVICE_REAR_LEFT     = 3;
    final int DRIVE_CAN_DEVICE_REAR_RIGHT    = 5;

    final int ENCODER_CODES_PER_REV          = 250;

    final int ARM_CAN_DEVICE_NUMBER          = 6;

    final int GRABBER_UPPER_ROLLER_PORT      = 7;
    final int GRABBER_LOWER_ROLLER_PORT      = 8;

    final int MINIBOT_RELEASE_SERVO          = 4;

    final int LINE_SENSOR_LEFT_CHANNEL       = 1;
    final int LINE_SENSOR_MIDDLE_CHANNEL     = 2;
    final int LINE_SENSOR_RIGHT_CHANNEL      = 3;

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
    final double DEFAULT_STEERING_GAIN  = 0.15;
    final double FORK_PROFILE[]         = {.2, .3, .2, .1, .2, .1, .05, 0};
    final double STRAIGHT_PROFILE[]     = {.2, .3, .4, .3, .05, 0, 0, 0};

    //Speed position control
    final double SPEED_P                     = 0.48;
    final double SPEED_I                     = 0.005;
    final double SPEED_D                     = 0.05;

    //Exception led
    final int BROKEN_LIGHT                   = 10;

    //TODO: Numbers need to be set.
    final int OI_MINIBOT_SWITCH_PORT         = 1;

    final int OI_BUTTON_ANALOG_PORT          = 1;
    final int OI_TRIM_POT_PORT               = 2;

    final int LIGHT_BIT_1_CHANNEL            = 1;
    final int LIGHT_BIT_2_CHANNEL            = 1;
    final int LIGHT_BIT_3_CHANNEL            = 1;
    final int LIGHT_BIT_4_CHANNEL            = 1;
    final int LIGHT_ENABLE_CHANNEL           = 1;

    final String[] DECIMAL_BINARY_TABLE      = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
}
