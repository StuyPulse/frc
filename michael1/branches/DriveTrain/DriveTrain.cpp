DriveTrain::DriveTrain()
{
	
}

void DriveTrain::setMotor(int index, float speed)
{
	motors.at(index)->Set(speed);
}


void DriveTrain::setMotors(int[] indices, float speed)
{
	for (int i = 0; i < &motors.length; i++){
		setMotor(i, speed);
	}
}