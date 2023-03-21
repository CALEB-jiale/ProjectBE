#ifndef _MULTIPERSONA_H_
#define _MULTIPERSONA_H_

#include "Behavior.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include <vector>
#include <string>
#include <map>

class MultiPersona : public Behavior {
private:
    std::vector<Behavior*> behaviors;
    Behavior* currentBehavior;
    int time;
    int numBehavior;
public:
    MultiPersona(Milieu* milieu, string name, std::map<string, Behavior*> &behaviors);
    ~MultiPersona() override;
    void updateParameters(Bug* bug) override;
    void updateBehavior();
    MultiPersona(const MultiPersona&) = delete;
    MultiPersona& operator=(const MultiPersona&) = delete;
    Color getColor() const override { return currentBehavior->getColor(); }
};


#endif //PROJECTBE_MULTIPERSONNA_H
