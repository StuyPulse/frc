package stuy;

public interface Constants {


    // Robot Hardware Configuration
    final int DRIVE_CAN_DEVICE_FRONT_LEFT    = 7;
    final int DRIVE_CAN_DEVICE_FRONT_RIGHT   = 9;
    final int DRIVE_CAN_DEVICE_REAR_LEFT     = 8;
    final int DRIVE_CAN_DEVICE_REAR_RIGHT    = 10;

    final int ENCODER_CODES_PER_REV          = 250;

    final int ARM_CAN_DEVICE_NUMBER          = 6;

    final int GRABBER_UPPER_ROLLER_PORT      = 1;
    final int GRABBER_LOWER_ROLLER_PORT      = 2;
    final int GRABBER_LIMIT_SWITCH_PORT      = 3;

    final int MINIBOT_RELEASE_SERVO          = 4;
    final int WRIST_SERVO                    = 6;
    final int WING_SERVO                     = 7;

    // Robot digital I/O
    final int HALOGEN_CHANNEL_A              = 4;
    final int HALOGEN_CHANNEL_B              = 5;

    final int LINE_SENSOR_LEFT_CHANNEL       = 12;
    final int LINE_SENSOR_MIDDLE_CHANNEL     = 13;
    final int LINE_SENSOR_RIGHT_CHANNEL      = 14;

    final double LOWER_ARM_POT_LIM           = 0.395;
    final double UPPER_ARM_POT_LIM           = 0.85;

    final int GYRO_CHANNEL                   = 4;

    // User controls
    final int PORT_LEFT_STICK                = 1;
    final int PORT_RIGHT_STICK               = 2;
    final int PORT_ARM_STICK                 = 3;

    // Thumbwheel switch
    final int BIT_1_CHANNEL                  = 1;
    final int BIT_2_CHANNEL                  = 2;
    final int BIT_3_CHANNEL                  = 3;
    final int BIT_4_CHANNEL                  = 4; // Least significant bit

    // Excpetion LED
    final int ERROR_LED                      = 10;

    // OI analog inputs
    final int OI_BUTTON_ANALOG_PORT          = 1;
    final int OI_TRIM_POT_PORT               = 3;

    // OI digital inputs
    final int OI_MINIBOT_SWITCH_PORT         = 2;
    final int OI_WING_SWITCH_PORT            = 4;
    final int OI_EXTRA_BUTTON_PORT           = 6;

    // Height buton light binary pins
    final int LIGHT_BIT_D_CHANNEL            = 11;
    final int LIGHT_BIT_C_CHANNEL            = 10;
    final int LIGHT_BIT_B_CHANNEL            = 9;
    final int LIGHT_BIT_A_CHANNEL            = 8; // Least significant bit
    final int LIGHT_DISABLE_CHANNEL          = 12;
    
    // Line Tracking

    // Array of binary values from 0 to 15
    final String[] DECIMAL_BINARY_TABLE      = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};

    // Height button light decimal outputs
    final int SIDE_UPPER_LIGHT                 = 0;
    final int SIDE_MIDDLE_LIGHT                = 1;
    final int SIDE_LOWER_LIGHT                 = 2;
    final int CENTER_UPPER_LIGHT               = 3;
    final int CENTER_MIDDLE_LIGHT              = 4;
    final int CENTER_LOWER_LIGHT               = 5;
    final int FEEDER_LEVEL_LIGHT               = 6;
    final int GROUND_LEVEL_LIGHT               = 7;

    // Speed position control
    final double SPEED_P                     = 0.48;
    final double SPEED_I                     = 0.005;
    final double SPEED_D                     = 0.05;

    // Line tracking
    final double DEFAULT_STEERING_GAIN  = 0.15;
    final double FORK_PROFILE[]         = {.2, .3, .2, .1, .2, .1, .05, 0};
    final double STRAIGHT_PROFILE[]     = {.2, .3, .4, .3, .05, 0, 0, 0};

    // Gains and setpoint for the target feedback loop.  Not yet tuned.
    final double PVAL                        = .5;
    final double IVAL                        = 0;
    final double DVAL                        = 0;
    final double PID_SETPOINT                = 0;
}
