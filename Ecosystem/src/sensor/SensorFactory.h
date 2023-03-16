#ifndef _SENSOR_FACTORY_H_
#define _SENSOR_FACTORY_H_

class Eye;
class Ear;

class SensorFactory {
private:
    SensorFactory* factory;
    SensorFactory();

public:
    ~SensorFactory();
    SensorFactory* getSensorFactory();
    Eye* getEye();
    Ear* getEar();
};

#endif
