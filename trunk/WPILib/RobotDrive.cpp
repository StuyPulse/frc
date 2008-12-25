/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include "RobotDrive.h"

#include "GenericHID.h"
#include "Joystick.h"
#include "Victor.h"
#include "Utility.h"
#include "WPIStatus.h"
#include <math.h>

/*
 * Driving functions
 * These functions provide an interface to multiple motors that is used for C programming
 * The Drive(speed, direction) function is the main part of the set that makes it easy
 * to set speeds and direction independently in one call.
 */

/** Constructor for RobotDrive with 2 motors specified with channel numbers. 
 * Set up parameters for a two wheel drive system where the
 * left and right motor pwm channels are specified in the call.
 * This call assumes Victors for controlling the motors.
 * @param leftMotorChannel The PWM channel number on the default digital module that drives the left motor.
 * @param rightMotorChannel The PWM channel number on the default digital module that drives the right motor.
 * @param sensitivity Effectively sets the turning sensitivity (or turn radius for a given value).
 */
RobotDrive::RobotDrive(UINT32 leftMotorChannel, UINT32 rightMotorChannel,
		float sensitivity)
{
	m_sensitivity = sensitivity;
	m_frontLeftMotor = NULL;
	m_rearLeftMotor = new Victor(leftMotorChannel);
	m_frontRightMotor = NULL;
	m_rearRightMotor = new Victor(rightMotorChannel);
	for (INT32 i=0; i < kMaxNumberOfMotors; i++)
	{
		m_invertedMotors[i] = 1;
	}
	Drive(0, 0);
	m_deleteSpeedControllers = true;
}

/**
 * Constructor for RobotDrive with 4 motors specified with channel numbers.
 * Set up parameters for a four wheel drive system where all four motor
 * pwm channels are specified in the call.
 * This call assumes Victors for controlling the motors.
 * @param frontLeftMotor Front left motor channel number on the default digital module
 * @param rearLeftMotor Rear Left motor channel number on the default digital module
 * @param frontRightMotor Front right motor channel number on the default digital module
 * @param rearRightMotor Rear Right motor channel number on the default digital module
 * @param sensitivity Effectively sets the turning sensitivity (or turn radius for a given value)
 */
RobotDrive::RobotDrive(UINT32 frontLeftMotor, UINT32 rearLeftMotor,
		UINT32 frontRightMotor, UINT32 rearRightMotor, float sensitivity)
{
	m_sensitivity = sensitivity;
	m_rearLeftMotor = new Victor(rearLeftMotor);
	m_rearRightMotor = new Victor(rearRightMotor);
	m_frontLeftMotor = new Victor(frontLeftMotor);
	m_frontRightMotor = new Victor(frontRightMotor);
	for (INT32 i=0; i < kMaxNumberOfMotors; i++)
	{
		m_invertedMotors[i] = 1;
	}
	Drive(0, 0);
	m_deleteSpeedControllers = true;
}

/**
 * Constructor for RobotDrive with 2 motors specified as SpeedController objects.
 * The SpeedController version of the constructor enables programs to use the RobotDrive classes with
 * subclasses of the SpeedController objects, for example, versions with ramping or reshaping of
 * the curve to suit motor bias or deadband elimination.
 * @param leftMotor The left SpeedController object used to drive the robot.
 * @param rightMotor the right SpeedController object used to drive the robot.
 * @param sensitivity Effectively sets the turning sensitivity (or turn radius for a given value) 
 */
RobotDrive::RobotDrive(SpeedController *leftMotor, SpeedController *rightMotor, float sensitivity)
{
	if (leftMotor == NULL | rightMotor == NULL)
	{
		wpi_fatal(NullParameter);
		m_rearLeftMotor = m_rearRightMotor = NULL;
		return;
	}
	m_frontLeftMotor = NULL;
	m_rearLeftMotor = leftMotor;
	m_frontRightMotor = NULL;
	m_rearRightMotor = rightMotor;
	m_sensitivity = sensitivity;
	for (INT32 i=0; i < kMaxNumberOfMotors; i++)
	{
		m_invertedMotors[i] = 1;
	}
	m_deleteSpeedControllers = false;
}

RobotDrive::RobotDrive(SpeedController &leftMotor, SpeedController &rightMotor, float sensitivity)
{
	m_frontLeftMotor = NULL;
	m_rearLeftMotor = &leftMotor;
	m_frontRightMotor = NULL;
	m_rearRightMotor = &rightMotor;
	m_sensitivity = sensitivity;
	for (INT32 i=0; i < kMaxNumberOfMotors; i++)
	{
		m_invertedMotors[i] = 1;
	}
	m_deleteSpeedControllers = false;
}

/**
 * Constructor for RobotDrive with 4 motors specified as SpeedController objects.
 * Speed controller input version of RobotDrive (see previous comments).
 * @param rearLeftMotor The back left SpeedController object used to drive the robot.
 * @param frontLeftMotor The front left SpeedController object used to drive the robot
 * @param rearRightMotor The back right SpeedController object used to drive the robot.
 * @param frontRightMotor The front right SpeedController object used to drive the robot.
 * @param sensitivity Effectively sets the turning sensitivity (or turn radius for a given value) 
 */
RobotDrive::RobotDrive(SpeedController *frontLeftMotor, SpeedController *rearLeftMotor,
						SpeedController *frontRightMotor, SpeedController *rearRightMotor,
						float sensitivity)
{
	if (frontLeftMotor == NULL || rearLeftMotor == NULL || frontRightMotor == NULL || rearRightMotor == NULL)
	{
		wpi_fatal(NullParameter);
		m_frontLeftMotor = m_rearLeftMotor = m_frontRightMotor = m_rearRightMotor = NULL;
		return;
	}
	m_frontLeftMotor = frontLeftMotor;
	m_rearLeftMotor = rearLeftMotor;
	m_frontRightMotor = frontRightMotor;
	m_rearRightMotor = rearRightMotor;
	m_sensitivity = sensitivity;
	for (INT32 i=0; i < kMaxNumberOfMotors; i++)
	{
		m_invertedMotors[i] = 1;
	}
	m_deleteSpeedControllers = false;
}

RobotDrive::RobotDrive(SpeedController &frontLeftMotor, SpeedController &rearLeftMotor,
						SpeedController &frontRightMotor, SpeedController &rearRightMotor,
						float sensitivity)
{
	m_frontLeftMotor = &frontLeftMotor;
	m_rearLeftMotor = &rearLeftMotor;
	m_frontRightMotor = &frontRightMotor;
	m_rearRightMotor = &rearRightMotor;
	m_sensitivity = sensitivity;
	for (INT32 i=0; i < kMaxNumberOfMotors; i++)
	{
		m_invertedMotors[i] = 1;
	}
	m_deleteSpeedControllers = false;
}

/**
 * RobotDrive destructor.
 * Deletes all the motor objects regardless of how they were allocated. Don't continue to use
 * any passed-in PWM objects after this class destructor is run.
 **/
RobotDrive::~RobotDrive(void)
{
	if (m_deleteSpeedControllers)
	{
		delete m_frontLeftMotor;
		delete m_rearLeftMotor;
		delete m_frontRightMotor;
		delete m_rearRightMotor;
	}
}

/**
 * Drive the motors at "speed" and "curve".
 * 
 * The speed and curve are -1.0 to +1.0 values where 0.0 represents stopped and
 * not turning. The algorithm for adding in the direction attempts to provide a constant
 * turn radius for differing speeds.
 * 
 * This function sill most likely be used in an autonomous routine.
 * 
 * @param speed The forward component of the speed to send to the motors.
 * @param curve The rate of turn, constant for different forward speeds.
 */
void RobotDrive::Drive(float speed, float curve)
{
	float leftSpeed, rightSpeed;

	if (curve < 0)
	{
		float value = log(-curve);
		float ratio = (value - m_sensitivity)/(value + m_sensitivity);
		if (ratio == 0) ratio =.0000000001;
		leftSpeed = speed / ratio;
		rightSpeed = speed;
	}
	else if (curve > 0)
	{
		float value = log(curve);
		float ratio = (value - m_sensitivity)/(value + m_sensitivity);
		if (ratio == 0) ratio =.0000000001;
		leftSpeed = speed;	
		rightSpeed = speed / ratio;
	}
	else
	{
		leftSpeed = speed;
		rightSpeed = speed;
	}
	SetLeftRightMotorSpeeds(leftSpeed, rightSpeed);
}

/**
 * Provide tank steering using the stored robot configuration.
 * Drive the robot using two joystick inputs. The Y-axis will be selected from
 * each Joystick object.
 * @param leftStick The joystick to control the left side of the robot.
 * @param rightStick The joystick to control the right side fo the robot.
 */
void RobotDrive::TankDrive(GenericHID *leftStick, GenericHID *rightStick)
{
	if (leftStick == NULL || rightStick == NULL)
	{
		wpi_fatal(NullParameter);
		return;
	}
	TankDrive(leftStick->GetY(), rightStick->GetY());
}

void RobotDrive::TankDrive(GenericHID &leftStick, GenericHID &rightStick)
{
	TankDrive(leftStick.GetY(), rightStick.GetY());
}

/**
 * Provide tank steering using the stored robot configuration.
 * This function lets you pick the axis to be used on each Joystick object for the left
 * and right sides of the robot.
 * @param leftStick The Joystick object to use for the left side of the robot.
 * @param leftAxis The axis to select on the left side Joystick object.
 * @param rightStick The Joystick object to use for the right side of the robot.
 * @param rightAxis The axis to select on the right side Joystick object.
 */
void RobotDrive::TankDrive(GenericHID *leftStick, UINT32 leftAxis,
		GenericHID *rightStick, UINT32 rightAxis)
{
	if (leftStick == NULL || rightStick == NULL)
	{
		wpi_fatal(NullParameter);
		return;
	}
	TankDrive(leftStick->GetRawAxis(leftAxis), rightStick->GetRawAxis(rightAxis));
}

void RobotDrive::TankDrive(GenericHID &leftStick, UINT32 leftAxis,
		GenericHID &rightStick, UINT32 rightAxis)
{
	TankDrive(leftStick.GetRawAxis(leftAxis), rightStick.GetRawAxis(rightAxis));
}


/**
 * Provide tank steering using the stored robot configuration.
 * This function lets you directly provide joystick values from any source.
 * @param leftValue The value of the left stick.
 * @param rightValue The value of the right stick.
 */
void RobotDrive::TankDrive(float leftValue, float rightValue)
{
	// square the inputs (while preserving the sign) to increase fine control while permitting full power
	leftValue = Limit(leftValue);
	rightValue = Limit(rightValue);
	if (leftValue >= 0.0)
	{
		leftValue = (leftValue * leftValue);
	}
	else
	{
		leftValue = -(leftValue * leftValue);
	}
	if (rightValue >= 0.0)
	{
		rightValue = (rightValue * rightValue);
	}
	else
	{
		rightValue = -(rightValue * rightValue);
	}

	SetLeftRightMotorSpeeds(leftValue, rightValue);
}

/**
 * Arcade drive implements single stick driving.
 * Given a single Joystick, the class assumes the Y axis for the move value and the X axis
 * for the rotate value.
 * (Should add more information here regarding the way that arcade drive works.)
 * @param stick The joystick to use for Arcade single-stick driving. The Y-axis will be selected
 * for forwards/backwards and the X-axis will be selected for rotation rate.  Pulling the trigger
 * enables "spin" functionality.
 */
void RobotDrive::ArcadeDrive(GenericHID *stick)
{
	// simply call the full-featured ArcadeDrive with the appropriate values
	ArcadeDrive(stick->GetY(), stick->GetX(), stick->GetTrigger());
}

void RobotDrive::ArcadeDrive(GenericHID &stick)
{
	// simply call the full-featured ArcadeDrive with the appropriate values
	ArcadeDrive(stick.GetY(), stick.GetX(), stick.GetTrigger());
}

/**
 * Arcade drive implements single stick driving.
 * Given two joystick instances and two axis, compute the values to send to either two
 * or four motors.
 * @param moveStick The Joystick object that represents the forward/backward direction
 * @param moveAxis The axis on the moveStick object to use for fowards/backwards (typically Y_AXIS)
 * @param rotateStick The Joystick object that represents the rotation value
 * @param rotateAxis The axis on the rotation object to use for the rotate right/left (typically X_AXIS)
 * @param spinStick The Joystick with the button to use for enabling "spin" functionality (default is NULL)
 * @param spinButton The button number of the button for enabling "spin" functionality (default is button 1)
 */
void RobotDrive::ArcadeDrive(GenericHID* moveStick, UINT32 moveAxis,
		GenericHID* rotateStick, UINT32 rotateAxis,
		GenericHID* spinStick, UINT32 spinButton)
{
	float moveValue = moveStick->GetRawAxis(moveAxis);
	float rotateValue = rotateStick->GetRawAxis(rotateAxis);
	bool spin = false;
	
	if (spinStick) spin = spinStick->GetRawButton(spinButton);
	
	ArcadeDrive(moveValue, rotateValue, spin);
}

void RobotDrive::ArcadeDrive(GenericHID &moveStick, UINT32 moveAxis,
		GenericHID &rotateStick, UINT32 rotateAxis,
		GenericHID &spinStick, UINT32 spinButton)
{
	float moveValue = moveStick.GetRawAxis(moveAxis);
	float rotateValue = rotateStick.GetRawAxis(rotateAxis);
	bool spin = false;
	
	spin = spinStick.GetRawButton(spinButton);
	
	ArcadeDrive(moveValue, rotateValue, spin);
}

/**
 * Arcade drive implements single stick driving.
 * This function lets you directly provide joystick values from any source.
 * @param moveValue The value to use for fowards/backwards
 * @param rotateValue The value to use for the rotate right/left
 */
void RobotDrive::ArcadeDrive(float moveValue, float rotateValue, bool spin)
{
	// local variables to hold the computed PWM values for the motors; default to 0.0 (off)
	float leftMotorSpeed = 0.0;
	float rightMotorSpeed = 0.0;
	
	moveValue = Limit(moveValue);
	rotateValue = Limit(rotateValue);

	// square the inputs (while preserving the sign) to increase fine control while permitting full power
	if (moveValue >= 0.0)
	{
		moveValue = (moveValue * moveValue);
	}
	else
	{
		moveValue = -(moveValue * moveValue);
	}
	if (rotateValue >= 0.0)
	{
		rotateValue = (rotateValue * rotateValue);
	}
	else
	{
		rotateValue = -(rotateValue * rotateValue);
	}

	// Compute motor values for "normal driving" case.
	// Essentially, set the motor values to the "moveValue" for forwards/backwards, however reduce the
	// value for the "inside wheel" on a turn to encourage the robot to turn in that direction.
	if (rotateValue > 0.0)
	{
		// stick is on the right side; weaken the right wheel
		leftMotorSpeed = moveValue;
		rightMotorSpeed = moveValue * (1-rotateValue);
	}
	else
	{
		// stick is on the left side; weaken the left wheel
		rightMotorSpeed = moveValue;
		leftMotorSpeed = moveValue * (1+rotateValue);
	}

	// Provide for the capability of "spins"
	// When spin is true, instead of "normal operation" as above, spin in place with rotateValue as power
	if (spin)
	{
		leftMotorSpeed = rotateValue;
		rightMotorSpeed = -rotateValue;
	}

	SetLeftRightMotorSpeeds(leftMotorSpeed, rightMotorSpeed);

}

/**
 * Holonomic Drive class for Mecanum wheeled robots.
 * 
 * Experimental class for driving with Mecanum wheeled robots. There are 4 wheels
 * on the robot, arranged so that the front and back wheels are toed in 45 degrees.
 * 
 * @param magnitude The speed that the robot should drive in a given direction.
 * @param direction The direction the robot should drive. The direction and maginitute are
 * independent of the rotation rate.
 * @param rotation The rate of rotation for the robot that is completely independent of
 * the magnitute or direction.
 */
void RobotDrive::HolonomicDrive(float magnitude, float direction, float rotation)
{
	float frontLeftSpeed, rearLeftSpeed, frontRightSpeed, rearRightSpeed;
	magnitude = Limit(magnitude);
	float cosD = cos((float)(direction + 45.0) * 3.14159 / 180.0);
	float sinD = cos((float)(direction - 45.0) * 3.14159 / 180.0);
	frontLeftSpeed = Limit((float)(sinD * (float)magnitude + rotation));
	rearLeftSpeed = Limit((float)(cosD * (float)magnitude + rotation));
	frontRightSpeed = Limit((float)(cosD * (float)magnitude - rotation));
	rearRightSpeed = Limit((float)(sinD * (float)magnitude - rotation));

	m_frontLeftMotor->Set(frontLeftSpeed * m_invertedMotors[kFrontLeftMotor]);
	m_frontRightMotor->Set(frontRightSpeed * m_invertedMotors[kFrontRightMotor]);
	m_rearLeftMotor->Set(rearLeftSpeed * m_invertedMotors[kRearLeftMotor]);
	m_rearRightMotor->Set(rearRightSpeed * m_invertedMotors[kRearRightMotor]);
}

/** Set the speed of the right and left motors.
 * This is used once an appropriate drive setup function is called such as
 * TwoWheelDrive(). The motors are set to "leftSpeed" and "rightSpeed"
 * and includes flipping the direction of one side for opposing motors.
 * @param leftSpeed The speed to send to the left side of the robot.
 * @param rightSpeed The speed to send to the right side of the robot.
 */
void RobotDrive::SetLeftRightMotorSpeeds(float leftSpeed, float rightSpeed)
{
	wpi_assert(m_rearLeftMotor != NULL && m_rearRightMotor != NULL);
	
	leftSpeed = Limit(leftSpeed);
	rightSpeed = Limit(rightSpeed);

	if (m_frontLeftMotor != NULL)
		m_frontLeftMotor->Set(Limit(leftSpeed) * m_invertedMotors[kFrontLeftMotor]);
	m_rearLeftMotor->Set(Limit(leftSpeed) * m_invertedMotors[kRearLeftMotor]);

	if (m_frontRightMotor != NULL)
		m_frontRightMotor->Set(-Limit(rightSpeed) * m_invertedMotors[kFrontRightMotor]);
	m_rearRightMotor->Set(-Limit(rightSpeed) * m_invertedMotors[kRearRightMotor]);
}

/**
 * Limit motor values to the -1.0 to +1.0 range.
 */
float RobotDrive::Limit(float num)
{
	if (num > 1.0)
	{
		return 1.0;
	}
	if (num < -1.0)
	{
		return -1.0;
	}
	return num;
}

/*
 * Invert a motor direction.
 * This is used when a motor should run in the opposite direction as the drive
 * code would normally run it. Motors that are direct drive would be inverted, the
 * Drive code assumes that the motors are geared with one reversal.
 * @param motor The motor index to invert.
 * @param isInverted True if the motor should be inverted when operated.
 */
void RobotDrive::SetInvertedMotor(MotorType motor, bool isInverted)
{
	if (motor < 0 || motor > 3)
	{
		wpi_fatal(InvalidMotorIndex);
		return;
	}
	m_invertedMotors[motor] = isInverted ? -1 : 1;
}


