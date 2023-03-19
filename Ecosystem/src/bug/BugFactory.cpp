#include "BugFactory.h"
#include "../sensor/SensorFactory.h"
#include "../behavior/BehaviorFactory.h"
#include "../accessory/AccessoryFacade.h"
#include <iostream>

using namespace std;

BugFactory* BugFactory::bugFactory = nullptr;

BugFactory::BugFactory(Milieu* milieu) {
    this->milieu = milieu;
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
    Bug* bug = new Bug(milieu);
    accessoryFacade->attachAccessories(bug);
    sensorFactory->attachSensors(bug);
    Behavior* behavior = behaviorFactory->getSuicideBoomer();
    bug->setBehavior(behavior);
    return bug;
}

Bug* BugFactory::getCareful() {
    Bug* bug = new Bug(milieu);
    accessoryFacade->attachAccessories(bug);
    sensorFactory->attachSensors(bug);
    Behavior* behavior = behaviorFactory->getCareful();
    bug->setBehavior(behavior);
    return bug;
}

Bug* BugFactory::getMultiPersona() {
    Bug* bug = new Bug(milieu);
    accessoryFacade->attachAccessories(bug);
    sensorFactory->attachSensors(bug);
    Behavior* behavior = behaviorFactory->getMultiPersona();
    bug->setBehavior(behavior);
    return bug;
}

Bug* BugFactory::getSocial() {
    Bug* bug = new Bug(milieu);
    accessoryFacade->attachAccessories(bug);
    sensorFactory->attachSensors(bug);
    Behavior* behavior = behaviorFactory->getSocial();
    bug->setBehavior(behavior);
    return bug;
}

Bug* BugFactory::getFearful() {
    Bug* bug = new Bug(milieu);
    accessoryFacade->attachAccessories(bug);
    sensorFactory->attachSensors(bug);
    Behavior* behavior = behaviorFactory->getFearful();
    bug->setBehavior(behavior);
    return bug;
}
