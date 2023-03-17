//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_SUICIDEBOOMER_H
#define PROJECTBE_SUICIDEBOOMER_H

#include "Behavior.h"
#include "../Bestiole.h"


class SuicideBoomer : public Behaviour {
public:
    SuicideBoomer(const Milieu* milieu);
    ~SuicideBoomer() override;
    void updateParameters(Bestiole* bug) override;
    SuicideBoomer(const SuicideBoomer&) = delete;
    SuicideBoomer& operator=(const SuicideBoomer&) = delete;
};


#endif //PROJECTBE_SUICIDEBOOMER_H
