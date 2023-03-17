//
// Created by Franck XU on 16/03/2023.
//

#ifndef PROJECTBE_SOCIAL_H
#define PROJECTBE_SOCIAL_H

#include "Behavior.h"
#include "../Bestiole.h"


class Social : public Behavior {
public:
    Social(const Milieu* milieu);
    ~Social() override;
    void updateParameters(Bestiole* bug) override;
    Social(const Social&) = delete;
    Social& operator=(const Social&) = delete;
};


#endif //PROJECTBE_SOCIAL_H
