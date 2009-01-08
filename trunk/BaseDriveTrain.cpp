BaseDriveTrain::BaseDriveTrain()
{
	
}

void BaseDriveTrain::setMotor(int index, float speed)
{
	motors.at(index)->Set(speed);
}


void BaseDriveTrain::setMotors(int[] indices, float speed)
{
	for (int i = 0; i < &motors.length; i++){
		setMotor(i, speed);
	}
}