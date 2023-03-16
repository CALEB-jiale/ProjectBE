#ifndef _EAR_H_
#define _EAR_H_

#include "Sensor.h"

class Bug;

class Ear : public Sensor {
public:
    static float DISTANCE_MIN;
    static float DISTANCE_MAX;
    static float DETECT_CAPACITY_MIN;
    static float DETECT_CAPACITY_MAX;
    
    Ear(Bug* owner, float detectCapacity, float distance);
};

#endif
