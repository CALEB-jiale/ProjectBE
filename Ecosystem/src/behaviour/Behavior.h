//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_BEHAVIOR_H
#define

#include "../Bestiole.h"


class Behavior {
protected:
    Milieu* milieu;
    Behavior(const Milieu* milieu) { this->milieu = milieu; };

public:
    virtual ~Behavior() = default;

    virtual void updateParameters(Bestiole* bug) = 0;
};


#endif //PROJECTBE_BEHAVIOR_H