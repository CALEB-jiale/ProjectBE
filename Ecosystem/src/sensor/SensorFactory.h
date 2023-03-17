#ifndef _SENSOR_FACTORY_H_
#define _SENSOR_FACTORY_H_

class Eye;
class Ear;

class SensorFactory {
private:
    static SensorFactory* factory;
    SensorFactory();
    SensorFactory(const SensorFactory& sensorFactory) = delete;
    SensorFactory& operator=(const SensorFactory& sensorFactory) = delete;

public:
    ~SensorFactory();
    static SensorFactory* getSensorFactory();
    Eye* getEye(Bug* bug) const;
    Ear* getEar(Bug* bug) const;
};

#endif
