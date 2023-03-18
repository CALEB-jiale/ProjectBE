//
// Created by Franck XU on 17/03/2023.
//

#ifndef PROJECTBE_BEHAVIORFACTORY_H
#define PROJECTBE_BEHAVIORFACTORY_H

#include <map>
#include <string>
#include "../environment/Milieu.h"


class BehaviorFactory {
private:
    static BehaviorFactory* factor = nullptr;
    static const string carefull = "Carefull";
    static const string fearful = "Fearful";
    static const string multipersona = "MultiPersona";
    static const string social = "Social";
    static const string suicideboomer = "SuicideBoomer";

    std::map<string, Behavior*> behaviors;
    BehaviorFactory(Milieu* milieu);

public:
    ~BehaviorFactory();
    static BehaviorFactory* getBehaviorFactory(Milieu* milieu);
    Behavior* getMultiPersona();
    Behavior* getFearful();
    Behavior* getSocial();
    Behavior* getCareful();
    Behavior* getSuicideBoomer();

    BehaviorFactory(const BehaviorFactory&) = delete;
    BehaviorFactory& operator=(const BehaviorFactory&) = delete;
};


#endif //PROJECTBE_BEHAVIORFACTORY_H
