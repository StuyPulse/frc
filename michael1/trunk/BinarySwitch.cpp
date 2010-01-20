#include "BinarySwitch.h"
#include <math.h>


BinarySwitch::BinarySwitch(int size, ...){
	va_list vl;
	va_start(vl,size);
	for (int i=0;i<size;i++)
		inputs.push_back( new DigitalInput(va_arg(vl, int)) );
	va_end(vl);
}

int BinarySwitch::Get(){
	int sum = 0;
	for (UINT32 b = 0; b < inputs.size(); b++){
		sum += static_cast<int>(GetBit(b) * pow(2, abs(inputs.size()-1-b)));
	}
	return sum;
}

int BinarySwitch::GetBit(int b){
	if (b < size && b >= 0){
		return abs(1-inputs.at(b)->Get());
	}
	return -1;
}
