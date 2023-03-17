#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <../../include/HMI/UImg.h>

class Bug;

class Sensor {
protected:
    Bug* owner;
    double detectCapacity;
    double angle;
    double distance;

public:
    virtual ~Sensor() {};
    virtual Sensor* clone() const = 0;
    virtual void draw(UImg& support) const = 0;
    virtual bool isDetected(const Bug& bug) const = 0;
};

#endif
