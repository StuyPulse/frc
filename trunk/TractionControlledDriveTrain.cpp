// Extends BaseDriveTrain

// Has an encoder and accelerometer? instance variable

// Overrides setSpeed() so that a speed change request is not just passed through to the SpeedControllers. Instead, this setSpeed method invkes a routine which "fades" the speed controller up to this speed over time using the accelerometer and encoders. It can also just use time for now.