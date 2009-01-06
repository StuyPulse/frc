// Extends Object

// has an array or hash of SpeedController objects [Victors and Jaguars extend SpeedController]

// has a real method for setSpeed(float speed, int index) which sets the speed controller at array[index] to speed. This is a one line method. Very simple

// has virtual methods for direct joystick input [possibly using the predefined ArcadeDrive or TankDrive classes] which would be employed in teleop mode
// has vitual methods for things like setArcRadius(float) [full left to full right] which would be employed in auton mode

// BaseDriveTrain isn't that exciting. The only thing it really has in an empty array of SpeedControllers