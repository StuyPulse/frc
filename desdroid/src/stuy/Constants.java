package stuy;

public interface Constants {

    // Robot Hardware Configuration
    final int DRIVE_CAN_DEVICE_FRONT_LEFT    = 3;
    final int DRIVE_CAN_DEVICE_REAR_LEFT     = 2;
    final int DRIVE_CAN_DEVICE_FRONT_RIGHT   = 4;
    final int DRIVE_CAN_DEVICE_REAR_RIGHT    = 5;

    final int ARM_CAN_DEVICE_NUMBER          = 6;

    final int GRABBER_UPPER_ROLLER_DEVICE    = 7;
    final int GRABBER_LOWER_ROLLER_DEVICE    = 8;

    final int TRAY_MOTORS_CHANNEL            = 4;

    final int LINE_SENSOR_LEFT_CHANNEL       = 1;
    final int LINE_SENSOR_MIDDLE_CHANNEL     = 2;
    final int LINE_SENSOR_RIGHT_CHANNEL      = 3;

    final int LOWER_ARM_POT_LIM              = 100;
    final int UPPER_ARM_POT_LIM              = 200;

    final int GYRO_CHANNEL                   = 4;

    final int CAGE_LATCH_SERVO_CHANNEL       = 1;

    // User Controls
    final int PORT_LEFT_STICK                = 1;
    final int PORT_RIGHT_STICK               = 2;
    final int PORT_ARM_STICK                 = 3;

    // EnhancedIO pins
    final int BIT_4_CHANNEL                  = 16; // From Donovan OI box
    final int BIT_3_CHANNEL                  = 14;
    final int BIT_2_CHANNEL                  = 12;
    final int BIT_1_CHANNEL                  = 10;

    // Arm position control
    final double ARM_P                       = 0;
    final double ARM_I                       = 0;
    final double ARM_D                       = 0;

    //Speed position control
    final double SPEED_P                     = 0;
    final double SPEED_I                     = 0;
    final double SPEED_D                     = 0;


    //Exception led
    final int BROKEN_LIGHT = 0;

    //TODO: Numbers need to be set.
    final int OI_LEFT_BOTTOM_BUTTON = 0;
    final int OI_LEFT_MIDDLE_BUTTON = 0;
    final int OI_LEFT_TOP_BUTTON = 0;
    final int OI_MIDDLE_BOTTOM_BUTTON = 0;
    final int OI_MIDDLE_MIDDLE_BUTTON = 0;
    final int OI_MIDDLE_TOP_BUTTON = 0;
    final int OI_RIGHT_BOTTOM_BUTTON = 0;
    final int OI_RIGHT_MIDDLE_BUTTON = 0;
    final int OI_RIGHT_TOP_BUTTON = 0;



    // Line Tracking
    final double DEFAULT_STEERING_GAIN       = 0.3;
    final double FORK_PROFILE[]              = {.7, .7, .55, .6, .6, .5, .4, 0};
    final double STRAIGHT_PROFILE[]          = {.8, .9, 1, 1, .7, .7, .6, 0};

    //
}
