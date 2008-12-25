#include "Servo.h"
#include "CServo.h"
#include "CPWM.h"

static SensorBase *CreateServo(UINT32 slot, UINT32 channel)
{
	return new Servo(slot, channel);
}


void SetServo(UINT32 slot, UINT32 channel, float value)
{
	Servo *servo = (Servo *) AllocatePWM(slot, channel, CreateServo);
	servo->Set(value);
}

float GetGetServo(UINT32 slot, UINT32 channel)
{
	Servo *servo = (Servo *) AllocatePWM(slot, channel, CreateServo);
	return servo->Get();
}

void SetServoAngle(UINT32 slot, UINT32 channel, float angle)
{
	Servo *servo = (Servo *) AllocatePWM(slot, channel, CreateServo);
	servo->SetAngle(angle);
}

float GetServoAngle(UINT32 slot, UINT32 channel)
{
	Servo *servo = (Servo *) AllocatePWM(slot, channel, CreateServo);
	return servo->GetAngle();
}

float GetServoMaxAngle(UINT32 slot, UINT32 channel)
{
	Servo *servo = (Servo *) AllocatePWM(slot, channel, CreateServo);
	return servo->GetMaxAngle();
}

float GetServoMinAngle(UINT32 slot, UINT32 channel)
{
	Servo *servo = (Servo *) AllocatePWM(slot, channel, CreateServo);
	return servo->GetMinAngle();
}

void SetServo(UINT32 channel, float value)
{
	Servo *servo = (Servo *) AllocatePWM(channel, CreateServo);
	servo->Set(value);
}

float GetServo(UINT32 channel)
{
	Servo *servo = (Servo *) AllocatePWM(channel, CreateServo);
	return servo->Get();
}

void SetServoAngle(UINT32 channel, float angle)
{
	Servo *servo = (Servo *) AllocatePWM(channel, CreateServo);
	servo->SetAngle(angle);
}

float GetServoAngle(UINT32 channel)
{
	Servo *servo = (Servo *) AllocatePWM(channel, CreateServo);
	return servo->GetAngle();
}

float GetServoMaxAngle(UINT32 channel)
{
	Servo *servo = (Servo *) AllocatePWM(channel, CreateServo);
	return servo->GetMaxAngle();
}

float GetServoMinAngle(UINT32 channel)
{
	Servo *servo = (Servo *) AllocatePWM(channel, CreateServo);
	return servo->GetMinAngle();
}
