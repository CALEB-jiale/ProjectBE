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
    static const string carefull = "carefull";
    static const string fearful = "fearful";
    static const string multipersona = "multipersona";
    static const string social = "social";
    static const string suicideboomer = "suicideboomer";

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
