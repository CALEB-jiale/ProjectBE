#ifndef _SENSOR_H_
#define _SENSOR_H_

#include <../../include/HMI/UImg.h>

class Bug;

class Sensor {
protected:
    Bug* owner;
    float detectCapacity;
    float angle;
    float distance;

public:
    virtual Sensor() = 0;
    virtual ~Sensor() = 0;
    virtual void draw(UImg& support) const = 0;
    bool isDetected(const Bug& bug) const;
    Sensor* clone() const override;
};

#endif