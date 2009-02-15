#include <stdarg.h>
#include <vector>
#include "WPILib.h"

class BinarySwitch {
	
public:
	BinarySwitch(int size, ...);
	int Get();
	int GetBit(int);
	std::vector< DigitalInput* > inputs;

	
private:
	int size;
	
};
