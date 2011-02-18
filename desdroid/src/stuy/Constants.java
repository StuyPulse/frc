package stuy;

public interface Constants {

    final int CHANNEL_FRONT_LEFT             = 7; // not wired yet, don't know
    final int CHANNEL_FRONT_RIGHT            = 9;
    final int CHANNEL_REAR_LEFT              = 8;
    final int CHANNEL_REAR_RIGHT             = 10;

    final int CHANNEL_FRONT_LEFT_ENC_A       = 1;
    final int CHANNEL_FRONT_LEFT_ENC_B       = 2;
    final int CHANNEL_REAR_LEFT_ENC_A        = 9; // 3 / 4 were bad
    final int CHANNEL_REAR_LEFT_ENC_B        = 10;
    final int CHANNEL_FRONT_RIGHT_ENC_A      = 5;
    final int CHANNEL_FRONT_RIGHT_ENC_B      = 6;
    final int CHANNEL_REAR_RIGHT_ENC_A       = 7;
    final int CHANNEL_REAR_RIGHT_ENC_B       = 8;

    final int ARM_MOTOR_CHANNEL              = 3;

    final int GRABBER_UPPER_ROLLER_PORT      = 4;
    final int GRABBER_LOWER_ROLLER_PORT      = 1;
    final int GRABBER_LIMIT_SWITCH_PORT      = 11;

    // Robot output configuration
    final int ENCODER_CODES_PER_REV          = 250;


    final int MINIBOT_RELEASE_SERVO          = 4;
    final int WRIST_SERVO                    = 5;
    final int WING_SERVO                     = 6;

    // Robot digital I/O
    final int LINE_SENSOR_LEFT_CHANNEL       = 12;
    final int LINE_SENSOR_MIDDLE_CHANNEL     = 13;
    final int LINE_SENSOR_RIGHT_CHANNEL      = 14;
    final int HALOGEN_CHANNEL_A              = 4;
    final int HALOGEN_CHANNEL_B              = 5;

    final double LOWER_ARM_POT_LIM           = 0.46;
    final double UPPER_ARM_POT_LIM           = 2.64;
    final double POT_SIDE_BOTTOM             = 2.18;
    final double POT_SIDE_MIDDLE             = 1.46;
    final double POT_SIDE_TOP                = 0.72;
    final double POT_MIDDLE_BOTTOM           = 1.99;
    final double POT_MIDDLE_MIDDLE           = .8;
    final double POT_MIDDLE_TOP              = 0.21;
    final double MAX_ARM_DELAY               = .4;

    final int GYRO_CHANNEL                   = 4;

    // Analog input for arm potentiometer
    final int ARM_POT_CHANNEL                = 1;

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

    // Line Tracking
    final double DEFAULT_STEERING_GAIN  = 0.2;
    final double FORK_PROFILE[]         = {.4, .3, .1, .1, .1, .3, .1, 0};
    final double STRAIGHT_PROFILE[]     = {.7, .7, .7, .7, .4, 0, 0, 0};

    // Gains and setpoint for the target feedback loop.  Not yet tuned.
    final double PVAL                        = .5;
    final double IVAL                        = 0;
    final double DVAL                        = 0;
    final double PID_SETPOINT                = 0;

    // Arm position control
    final double ARM_P                       = 0;
    final double ARM_I                       = 0;
    final double ARM_D                       = 0;

    //Speed position control
    final double PDRIVE                     = 0.00375;
    final double IDRIVE                     = 0.00;
    final double DDRIVE                     = 0.000004;

    //Exception led

    //TODO: Numbers need to be set.
    final int OI_SIDE_BOTTOM_BUTTON          = 1;
    final int OI_SIDE_MIDDLE_BUTTON          = 2;
    final int OI_SIDE_TOP_BUTTON             = 3;
    final int OI_MIDDLE_BOTTOM_BUTTON        = 4;
    final int OI_MIDDLE_MIDDLE_BUTTON        = 5;
    final int OI_MIDDLE_TOP_BUTTON           = 6;
    final int OI_FEEDER_TUBE_BUTTON          = 7;

    // "distance" per pulse, to make the Encoder class return getRate() in RPM
    final double ENCODER_RPM_PER_PULSE       = 60.0 / ENCODER_CODES_PER_REV;
}
