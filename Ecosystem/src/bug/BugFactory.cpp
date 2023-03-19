#include "BugFactory.h"
#include "../sensor/SensorFactory.h"
#include "../behavior/BehaviorFactory.h"
#include "../accessory/AccessoryFacade.h"
#include <iostream>

using namespace std;

BugFactory* BugFactory::bugFactory = nullptr;

BugFactory::BugFactory(Milieu* milieu) {
    this->behaviorFactory = BehaviorFactory.getBehaviorFactory(milieu);
    this->sensorFactory = SensorFactory.getSensorFactory();
    this->accessoryFacade = new AccessoryFacade();
    LOG_DEBUG("Creating Bug Factory");
}

BugFactory* BugFactory::getBugFactory(Milieu *milieu) {
    if(bugFactory == nullptr) {
        bugFactory = new BugFactory(milieu);
    }
    return bugFactory;
}

BugFactory::~BugFactory() {
    delete behaviorFactory;
    delete SensorFactory;
    delete AccessoryFacade;
    factory = nullptr;
    LOG_DEBUG("Destroying Bug Factory");
}

Bug* BugFactory::getSuicideBoomer() {
    return new suicideboomer;
}

Bug* BugFactory::getCareful() {
    return new careful;
}

Bug* BugFactory::getMultiPersona() {
    return new multipersona;
}

Bug* BugFactory::getSocial() {
    return new social;
}

Bug* BugFactory::getFearful() {
    return new social;
}
