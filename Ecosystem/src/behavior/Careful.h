#ifndef PROJECTBE_CAREFUL_H
#define PROJECTBE_CAREFUL_H

#include "Behavior.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include <string>

class Careful : public Behavior {
public:
    Careful(Milieu* milieu, string name);
    ~Careful() override;
    void updateParameters(Bug* bug) override;
    Careful(const Careful&) = delete;
    Careful& operator=(const Careful&) = delete;
};


#endif //PROJECTBE_CAREFUL_H
