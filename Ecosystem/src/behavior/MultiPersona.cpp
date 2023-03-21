#include "MultiPersona.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include "Behavior.h"
#include <iostream>
#include <vector>
#include <map>
#include "../../include/Random.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

MultiPersona::MultiPersona(Milieu* milieu, string name, std::map<string, Behavior*> &behaviors) {
    this->milieu=milieu;
    this->name = name;
    this->time = Random::get(300, 3000);
    for (auto b : behaviors) {
        this->behaviors.push_back(b.second);
    }
    this->numBehavior = this->behaviors.size() - 1;
    int random_number = Random::get(0, numBehavior);
    currentBehavior = this->behaviors[random_number];
}

MultiPersona::~MultiPersona() {
    
}

void MultiPersona::updateBehavior() {
    time = Random::get(300, 3000);
    int random_number = Random::get(0, numBehavior);
    currentBehavior = behaviors[random_number];
}

void MultiPersona::updateParameters(Bug* bug) {
    if(time == 0) {
        updateBehavior();
    } else {
        time--;
    }
    
    this->currentBehavior->updateParameters(bug);
}
