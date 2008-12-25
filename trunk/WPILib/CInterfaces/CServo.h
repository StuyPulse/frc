#ifndef C_SERVO_H
#define C_SERVO_H

void SetServo(UINT32 slot, UINT32 channel, float value);
float GetGetServo(UINT32 slot, UINT32 channel);
void SetServoAngle(UINT32 slot, UINT32 channel, float angle);
float GetServoAngle(UINT32 slot, UINT32 channel);
float GetServoMaxAngle(UINT32 slot, UINT32 channel);
float GetServoMinAngle(UINT32 slot, UINT32 channel);
void SetServo(UINT32 channel, float value);
float GetGetServo(UINT32 channel);
void SetServoAngle(UINT32 channel, float angle);
float GetServoAngle(UINT32 channel);
float GetServoMaxAngle(UINT32 channel);
float GetServoMinAngle(UINT32 channel);

#endif

