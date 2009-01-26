#include "WPILib.h"



typedef struct {
	double displ[2];	// displacement (cm) since encoder init
	double vel[2];		// velocity between displacements[0] and [1]
	double accel[20];	// calculated encoder acceleration
} EncoderHist;
	
class StuyEncoder {
	
public:
	StuyEncoder(int slot, int port, double dist_per_tick);
	StuyEncoder(Encoder* encoder);
	void Start(float updateInterval, int numAveraged);
	double GetAccel();
	
private:
	float updateInterval;
	int numAveraged;
	EncoderHist *hist;
	Encoder *encoder;
	void updateTask();
};
