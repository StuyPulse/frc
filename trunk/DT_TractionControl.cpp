


// Has weight and wheel_cof instance variables


// methods to change wheel_cof and wheel_weight

// Overrides setMotor() so that a speed change request is not just passed through to the SpeedControllers. Instead, this setSpeed method invkes a routine which "fades" the speed controller up to this speed over time based on the max acceleration as determined by the wheel_cof and wheel_weight instance variables.