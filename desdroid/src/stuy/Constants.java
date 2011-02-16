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

    final int WRIST_SERVO                    = 6;

    final int GRABBER_UPPER_ROLLER_PORT      = 4;
    final int GRABBER_LOWER_ROLLER_PORT      = 1;
    
    final int GRABBER_LIMIT_SWITCH_PORT      = 11;

    final int MINIBOT_RELEASE_SERVO          = 4;

    final int LINE_SENSOR_LEFT_CHANNEL       = 12;
    final int LINE_SENSOR_MIDDLE_CHANNEL     = 13;
    final int LINE_SENSOR_RIGHT_CHANNEL      = 14;

    // Analog input for arm potentiometer
    final int ARM_POT_CHANNEL                = 1;
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

    // Arm position control
    final double ARM_P                       = 0;
    final double ARM_I                       = 0;
    final double ARM_D                       = 0;

    //Speed position control
    final double SPEED_P                     = 0;
    final double SPEED_I                     = 0;
    final double SPEED_D                     = 0;


    //Exception led
    final int BROKEN_LIGHT                   = 0;

    //TODO: Numbers need to be set.
    final int OI_LEFT_BOTTOM_BUTTON          = 0;
    final int OI_LEFT_MIDDLE_BUTTON          = 0;
    final int OI_LEFT_TOP_BUTTON             = 0;
    final int OI_MIDDLE_BOTTOM_BUTTON        = 0;
    final int OI_MIDDLE_MIDDLE_BUTTON        = 0;
    final int OI_MIDDLE_TOP_BUTTON           = 0;
    final int OI_RIGHT_BOTTOM_BUTTON         = 0;
    final int OI_RIGHT_MIDDLE_BUTTON         = 0;
    final int OI_RIGHT_TOP_BUTTON            = 0;

    // Line Tracking
    final double DEFAULT_STEERING_GAIN       = 0.3;
    final double FORK_PROFILE[]              = {.5, .5, .5, .5, .5, .2, .2, 0};
    final double STRAIGHT_PROFILE[]          = {.2, .2, .2, .2, .2, .2, .2, 0};

    final int ENCODER_CODES_PER_REV          = 250;
    // "distance" per pulse, to make the Encoder class return getRate() in RPM
    final double ENCODER_RPM_PER_PULSE       = 60.0 / ENCODER_CODES_PER_REV;

    final double PDRIVE                      = 0.48;
    final double IDRIVE                      = 0.00;
    final double DDRIVE                      = 0.05;
}
