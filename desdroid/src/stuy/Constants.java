package stuy;

public interface Constants {

    final int DRIVE_CAN_DEVICE_FRONT_LEFT    = 3;
    final int DRIVE_CAN_DEVICE_FRONT_RIGHT   = 4;
    final int DRIVE_CAN_DEVICE_REAR_LEFT     = 2;
    final int DRIVE_CAN_DEVICE_REAR_RIGHT    = 5;

    final int PORT_GAMEPAD                   = 1;
    final int AXIS_GAMEPAD_LEFT              = 2;
    final int AXIS_GAMEPAD_RIGHT             = 4;

    final int DIGITAL_IN_STRAIGHT_LINE       = 1;
    final int DIGITAL_IN_GO_LEFT             = 2;

    final double defaultSteeringGain = 0.65; // the default value for the steering gain

    int BIT_4_CHANNEL = 16; // From Donovan OI box
    int BIT_3_CHANNEL = 14;
    int BIT_2_CHANNEL = 12;
    int BIT_1_CHANNEL = 10;

}
