//
// Created by Franck XU on 17/03/2023.
//

#include "BehaviorFactory.h"
#include <map>
#include <string>
#include "../environment/Milieu.h"
#include "Behavior.h"
#include "Careful.h"
#include "Fearful.h"
#include "Social.h"
#include "MultiPersona.h"
#include "SuicideBoomer.h"

using namespace std;

BehaviorFactory::BehaviorFactory(milieu *milieu) {
    behaviors[carefull] = new Careful(milieu);
    behaviors[fearful] = new Fearful(milieu);
    behaviors[multipersona] = new MultiPersona(milieu);
    behaviors[social] = new Social(milieu);
    behaviors[suicideboomer] = new SuicideBoomer(milieu);
    LOG_DEBUG("Create Behavior Factory");
}

BehaviorFactory* BehaviorFactory::getBehaviorFactory(Milieu *milieu) {
    if (factory) {
        factory = new BehaviorFactory(milieu);
    }
    return factory;
}

Behavior* BehaviorFactory::getCareful() {
    return behaviors[carefull];
}

Behavior* BehaviorFactory::getFearful() {
    return behaviors[fearful];
}

Behavior* BehaviorFactory::getMultiPersona() {
    return behaviors[multipersona];
}

Behavior* BehaviorFactory::getSocial() {
    return behaviors[social];
}

Behavior* BehaviorFactory::getSuicideBoomer() {
    return behaviors[suicideboomer];
}

BehaviorFactory::~BehaviorFactory() {
    for (auto& entry : behaviors) {
        delete entry.second;
    }

    factory = nullptr;
    behaviors.clear();
    LOG_DEBUG("Destroy Behavior Factory");
}