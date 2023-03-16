#ifndef _EYE_H_
#define _EYE_H_

#include "Sensor.h"

class Bug;

class Eye : public Sensor {
public:
    static float ANGLE_MIN;
    static float ANGLE_MAX;
    static float DISTANCE_MIN;
    static float DISTANCE_MAX;
    static float DETECT_CAPACITY_MIN;
    static float DETECT_CAPACITY_MAX;
    
    Eye(Bug* owner, float detectCapacity, float distance, float angle);
    virtual ~Eye() override;
};

#endif
