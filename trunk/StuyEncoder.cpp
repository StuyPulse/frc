#include "StuyEncoder.h"

StuyEncoder::StuyEncoder(int slot, int port){
	encoder = new Encoder(slot, port);
}

StuyEncoder::StuyEncoder(Encoder* encoder){
	this->encoder = encoder;
}

void StuyEncoder::Start(float updateInterval, int numAveraged){
	this->updateInterval = updateInterval;
	this->numAveraged = numAveraged;
	
	//start updateTask task every updateInterval
	
}

void StuyEncoder::updateTask(){
	
	// push old sample back
	for(int i = 1; i < numAveraged; i++){
		hist->accel[i-1] = hist->accel[i];
	}
	hist->displ[0] = hist->displ[1];
	hist->vel[0] = hist->vel[1];
	
	// calc new sample
	hist->displ[1] = encoder->GetDistance();
	hist->vel[1] = (hist->displ[1] - hist->displ[0]) / (updateInterval);
	hist->accel[numAveraged] = (hist->vel[1] - hist->vel[0]) / (updateInterval);
		
}

double StuyEncoder::GetAccel(){
	//we must use semaphore for hist->accel
	double avg = 0;
	for (int i = 0; i < numAveraged; i++){
		avg += hist->accel[i];
	}
	avg /= numAveraged;
	return avg;
}
