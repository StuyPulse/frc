#include "StuyEncoder.h"

StuyEncoder::StuyEncoder(UINT32 pina, UINT32 pinb) : Encoder(pina, pinb)
{
	interval = 0.1;
	invert = false;
}

double StuyEncoder::GetVelocity(){
	return _invert(hist.vel[1]);
}

double StuyEncoder::GetAcceleration(){
	return _invert(hist.accel);
}

double StuyEncoder::_invert(double n){
	if(invert)
		n*=1;
	return n;
}

// Time sensitive. Must be called every this.interval
void StuyEncoder::Update()
{
	// push old sample back
	hist.displ[0] = hist.displ[1];
	hist.vel[0] = hist.vel[1];
	
	// read current displacement
	hist.displ[1] = GetDistance();
	
	// differentiate to get velocity
	hist.vel[1] = (hist.displ[1] - hist.displ[0]) / (interval);
	
	// differentiate to get acceleration
	hist.accel = (hist.vel[1] - hist.vel[0]) / (interval);	
}

