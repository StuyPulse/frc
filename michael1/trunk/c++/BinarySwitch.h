#include <stdarg.h>
#include <vector>
#include "WPILib.h"

class BinarySwitch {
	
public:
	BinarySwitch(int size, ...);
	int Get();
	int GetBit(int);

	
private:
	int size;
	std::vector< DigitalInput* > inputs;

	
};
