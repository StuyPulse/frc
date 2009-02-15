#include "BinarySwitch.h"
#include <math.h>


BinarySwitch::BinarySwitch(int size, ...){
	int i;
	DigitalInput bn(1);
	va_list vl;
	va_start(vl,size);
	for (i=0;i<size;i++)
		inputs.push_back( new DigitalInput(va_arg(vl, int)) );
	va_end(vl);
}

int BinarySwitch::Get(){
	int sum = 0;
	for (UINT32 b = 0; b < inputs.size(); b++){
		sum += static_cast<int>(inputs.at(b)->Get() * pow(2, b));
	}
	return sum;
}

int BinarySwitch::GetBit(int b){
	b -= 1;
	if (b < size && b >= 0){
		return inputs.at(b)->Get();
	}
	return -1;
}
