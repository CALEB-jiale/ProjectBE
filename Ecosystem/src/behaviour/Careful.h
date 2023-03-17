//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_CAREFUL_H
#define PROJECTBE_CAREFUL_H

#include "Behavior.h"
#include "../Bestiole.h"


class Careful : public Behavior {
public:
    Careful(const Milieu* milieu);
    ~Careful() override;
    void updateParameters(Bestiole* bug) override;
    Careful(const Careful&) = delete;
    Careful& operator=(const Careful&) = delete;
};


#endif //PROJECTBE_CAREFUL_H
