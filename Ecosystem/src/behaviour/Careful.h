//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_CAREFUL_H
#define PROJECTBE_CAREFUL_H

#include "Behavior.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"


class Careful : public Behavior {
public:
    Careful(const Milieu* milieu);
    ~Careful() override;
    void updateParameters(Bug* bug) override;
    Careful(const Careful&) = delete;
    Careful& operator=(const Careful&) = delete;
};


#endif //PROJECTBE_CAREFUL_H
