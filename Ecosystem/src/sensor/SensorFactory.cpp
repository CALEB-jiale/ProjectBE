#include "SensorFactory.h"
#include "Ear.h"
#include "Eye.h"

SensorFactory* SensorFactory::factory = nullptr;

SensorFactory::SensorFactory(){}

SensorFactory::~SensorFactory() {
    factory = nullptr;
}

SensorFactory* SensorFactory::getSensorFactory() {
    if(factory == nullptr) {
        factory = new SensorFactory();
    }
    return factory;
}

Eye* SensorFactory::getEye(Bug* bug) const {
    return new Eye(bug);
}

Ear* SensorFactory::getEar(Bug* bug) const {
    return new Ear(bug);
}
