//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_MULTIPERSONNA_H
#define PROJECTBE_MULTIPERSONNA_H

#include "Behavior.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include <vector>


class MultiPersona : public Behaviour {
    std::vector<Behavior*> behaviors;
public:
    MultiPersona(const Milieu* milieu, Behavior** behaviors);
    ~MultiPersona() override;
    void updateParameters(Bestiole* bug) override;
    MultiPersona(const MultiPersona&) = delete;
    MultiPersona& operator=(const MultiPersona&) = delete;
};


#endif //PROJECTBE_MULTIPERSONNA_H
