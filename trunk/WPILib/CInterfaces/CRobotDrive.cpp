#include "CRobotDrive.h"

static RobotDrive *drive = NULL;

void CreateRobotDrive(UINT32 leftMotor, UINT32 rightMotor)
{
	if (drive == NULL)
		drive = new RobotDrive(leftMotor, rightMotor);
}

void Drive(float speed, float curve)
{
	if (drive == NULL)
		wpi_fatal(DriveUninitialized);
	else
		drive->Drive(speed, curve);
}

void TankDrive(UINT32 leftStickPort, UINT32 rightStickPort)
{
	if (drive == NULL)
	{
		wpi_fatal(DriveUninitialized);
	}
	else
	{
		Joystick *leftStick = Joystick::GetStickForPort(leftStickPort);
		Joystick *rightStick = Joystick::GetStickForPort(rightStickPort);
		drive->TankDrive(leftStick, rightStick);
	}
}

void ArcadeDrive(UINT32 stickPort)
{
	if (drive == NULL)
	{
		wpi_fatal(DriveUninitialized);
	}
	else
	{
		Joystick *stick = Joystick::GetStickForPort(stickPort);
		drive->ArcadeDrive(stick);
	}
}

void TankByValue(float leftSpeed, float rightSpeed)
{
	if (drive == NULL)
	{
		wpi_fatal(DriveUninitialized);
	}
	else
	{
		drive->Drive(leftSpeed, rightSpeed);
	}
}
