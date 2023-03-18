//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_FEARFUL_H
#define PROJECTBE_FEARFUL_H

#include "Behavior.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"

class Fearful : public Behavior {
public:
    FearFul(const Milieu* milieu);
    ~Fearful() override;
    void updateParameters(Bug* bug) override;
    Fearful(const Fearful&) = delete;
    Feaful& operator=(const Feaful&) = delete;
};


#endif //PROJECTBE_FEARFUL_H
