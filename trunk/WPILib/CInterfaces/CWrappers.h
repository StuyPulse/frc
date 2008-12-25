#ifndef C_WRAPPERS_H
#define C_WRAPPERS_H

class SensorBase;
typedef SensorBase *(*SensorCreator)(UINT32 slot, UINT32 channel);

#endif

