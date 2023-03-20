//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_MULTIPERSONNA_H
#define PROJECTBE_MULTIPERSONNA_H

#include "Behavior.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include <vector>
#include <string>
#include <map>

class MultiPersona : public Behavior {
    std::vector<Behavior*> behaviors;
public:
    MultiPersona(Milieu* milieu, string name, std::map<string, Behavior*> &behaviors);
    ~MultiPersona() override;
    void updateParameters(Bug* bug) override;
    MultiPersona(const MultiPersona&) = delete;
    MultiPersona& operator=(const MultiPersona&) = delete;
};


#endif //PROJECTBE_MULTIPERSONNA_H
