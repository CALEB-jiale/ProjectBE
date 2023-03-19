#ifndef PROJECTBE_BEHAVIOR_H
#define

#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include <string>


class Behavior {
protected:
    string name;
    Milieu* milieu;

public:
    virtual ~Behavior(){};
    virtual void updateParameters(Bug* bug) = 0;
    string getBehaviorName() { return name; };
};


#endif //PROJECTBE_BEHAVIOR_H
