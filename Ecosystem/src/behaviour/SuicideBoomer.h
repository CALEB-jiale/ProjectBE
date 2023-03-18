//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_SUICIDEBOOMER_H
#define PROJECTBE_SUICIDEBOOMER_H

#include "Behavior.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include <string>


class SuicideBoomer : public Behavior {
public:
    SuicideBoomer(const Milieu* milieu, const string name);
    ~SuicideBoomer() override;
    void updateParameters(Bug* bug) override;
    SuicideBoomer(const SuicideBoomer&) = delete;
    SuicideBoomer& operator=(const SuicideBoomer&) = delete;
};


#endif //PROJECTBE_SUICIDEBOOMER_H
