//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_SOCIAL_H
#define PROJECTBE_SOCIAL_H

#include "Behavior.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include <string>


class Social : public Behavior {
public:
    Social(const Milieu* milieu, const string name);
    ~Social() override;
    void updateParameters(Bug* bug) override;
    Social(const Social&) = delete;
    Social& operator=(const Social&) = delete;
};


#endif //PROJECTBE_SOCIAL_H
