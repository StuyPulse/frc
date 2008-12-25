#ifndef C_ROBOT_DRIVE_H
#define C_ROBOT_DRIVE_H

#include "WPILib.h"

void CreateRobotDrive(UINT32 leftMotor, UINT32 rightMotor);
void Drive(float speed, float curve);
void TankDrive(UINT32 leftStickPort, UINT32 rightStickPort);
void ArcadeDrive(UINT32 stickPort);
void TankByValue(float leftSpeed, float rightSpeed);

#endif

