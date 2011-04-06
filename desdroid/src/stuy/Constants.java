package stuy;

public interface Constants {

    // Robot output configuration channels

    final int SECOND_SIDECAR_SLOT            = 6;
    final int CHANNEL_FRONT_LEFT             = 7;
    final int CHANNEL_FRONT_RIGHT            = 9;
    final int CHANNEL_REAR_LEFT              = 8;
    final int CHANNEL_REAR_RIGHT             = 10;

    // Drive encoder channels
    final int CHANNEL_FRONT_LEFT_ENC_A       = 1;
    final int CHANNEL_FRONT_LEFT_ENC_B       = 2;
    final int CHANNEL_REAR_LEFT_ENC_A        = 9; // 3 / 4 were bad
    final int CHANNEL_REAR_LEFT_ENC_B        = 10;
    final int CHANNEL_FRONT_RIGHT_ENC_A      = 5;
    final int CHANNEL_FRONT_RIGHT_ENC_B      = 6;
    final int CHANNEL_REAR_RIGHT_ENC_A       = 7;
    final int CHANNEL_REAR_RIGHT_ENC_B       = 8;

    // Arm outputs
    final int ARM_MOTOR_CHANNEL              = 3;
    final int WRIST_SERVO                    = 5;

    // Grabber I/O
    final int GRABBER_UPPER_ROLLER_PORT      = 4;
    final int GRABBER_LOWER_ROLLER_PORT      = 1;
    final int GRABBER_LIMIT_SWITCH_PORT      = 11;

    // Light on top of robot; lights up when tube is in grabber
    final int TUBE_ACQUIRED_LIGHT            = 1;

    // Minibot deployment
    final int DRAWBRIDGE_SERVO               = 6;
    final int DRAWBRIDGE_LIMIT_SWITCH_PORT   = 13;
    final int TRAY_RELEASE_MOTOR_PORT        = 10;
    final int TRAY_LIMIT_SWITCH_PORT         = 14;
    final int MINIBOT_RELEASE_SERVO          = 2;
    final int MOTOR_TOGGLE_SERVO             = 1;
    final int POLE_CONTACT_SWITCH_PORT       = 3;

    final double MINIBOT_MODE_SPEED          = 0.3125;

    // Robot digital I/O
    final int LINE_SENSOR_LEFT_CHANNEL       = 12;
    final int LINE_SENSOR_MIDDLE_CHANNEL     = 13;
    final int LINE_SENSOR_RIGHT_CHANNEL      = 14;

    // Analog input for arm potentiometer
    final int ARM_POT_CHANNEL                = 1;

    //Pulse width modulation multiplier for arm position controller.
    final double ARM_PWM_MULT                = .3;

    // User controls
    final int PORT_LEFT_STICK                = 1;
    final int PORT_RIGHT_STICK               = 2;
    final int PORT_ARM_STICK                 = 3;

    // Thumbwheel switch
    final int BIT_1_CHANNEL                  = 1;
    final int BIT_2_CHANNEL                  = 2;
    final int BIT_3_CHANNEL                  = 3;
    final int BIT_4_CHANNEL                  = 4; // Least significant bit

    // Exception LED
    final int ERROR_LED                      = 13;

    // OI analog inputs
    final int OI_BUTTON_ANALOG_PORT          = 1;
    final int OI_TRIM_POT_PORT               = 3;

    // OI digital inputs
    final int OI_MINIBOT_SWITCH_PORT         = 6;
    final int OI_DRAWBRIDGE_SWITCH_PORT      = 5;
    final int OI_EXTRA_BUTTON_PORT           = 7;

    // Height button light binary pins
    final int LIGHT_BIT_D_CHANNEL            = 11;
    final int LIGHT_BIT_C_CHANNEL            = 10;
    final int LIGHT_BIT_B_CHANNEL            = 9;
    final int LIGHT_BIT_A_CHANNEL            = 8; // Least significant bit
    final int LIGHT_DISABLE_CHANNEL          = 12;

    // Analog input straight from 3.3v. Max voltage is calculated using this pin.
    final int OI_MAX_VOLTAGE_INPUT           = 8;

    // Array of binary values from 0 to 15
    final String[] DECIMAL_BINARY_TABLE      = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};

    // Height buttons
    final int SIDE_UPPER_BUTTON                = 7;
    final int SIDE_MIDDLE_BUTTON               = 5;
    final int SIDE_LOWER_BUTTON                = 3;
    final int CENTER_UPPER_BUTTON              = 8;
    final int CENTER_MIDDLE_BUTTON             = 6;
    final int CENTER_LOWER_BUTTON              = 4;
    final int FEEDER_LEVEL_BUTTON              = 1;
    final int GROUND_LEVEL_BUTTON              = 2;

    // Height button light decimal outputs
    final int SIDE_UPPER_LIGHT                 = 1;
    final int SIDE_MIDDLE_LIGHT                = 3;
    final int SIDE_LOWER_LIGHT                 = 5;
    final int CENTER_UPPER_LIGHT               = 0;
    final int CENTER_MIDDLE_LIGHT              = 2;
    final int CENTER_LOWER_LIGHT               = 4;
    final int FEEDER_LEVEL_LIGHT               = 7;
    final int GROUND_LEVEL_LIGHT               = 6;
    final int EXTRA_BUTTON_LIGHT               = 8;

    // Speed control
    final double SPEED_P                       = 0.00365;
    final double SPEED_I                       = 0.00;
    final double SPEED_D                       = 0.000012;

    // Line Tracking
    final double DEFAULT_STEERING_GAIN  = 0.2;
    final double FORK_PROFILE[]         = {.4, .3, .1, .1, .1, .3, .1, 0};
    final double STRAIGHT_PROFILE[]     = {.3, .3, .2, .2};

    // Encoder constants
    final double ENCODER_CODES_PER_REV          = 250.0;
    final double ENCODER_RPM_PER_PULSE       = 60 / ENCODER_CODES_PER_REV;
    // "distance" per pulse, to make the Encoder class return getRate() in RPM
}