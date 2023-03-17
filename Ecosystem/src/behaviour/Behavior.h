//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_BEHAVIOR_H
#define

#include "../bug/Bug.h"
#include "../environment/Milieu.h"


class Behavior {
protected:
    Milieu* milieu;

public:
    virtual ~Behavior(){};
    virtual void updateParameters(Bestiole* bug) = 0;
};


#endif //PROJECTBE_BEHAVIOR_H
