#ifndef _EAR_H_
#define _EAR_H_

#include "Sensor.h"

class Bug;

class Ear : public Sensor {
public:
    static double DISTANCE_MIN;
    static double DISTANCE_MAX;
    static double DETECT_CAPACITY_MIN;
    static double DETECT_CAPACITY_MAX;
    
    Ear(Bug* owner);
    Ear(Bug* owner, double detectCapacity, double distance);
    virtual Sensor* clone() const;
    virtual void draw(UImg& support) const;
    virtual bool isDetected(const Bug& bug) const;
};

#endif
