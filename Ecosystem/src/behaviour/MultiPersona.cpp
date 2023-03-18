//
// Created by Franck XU on 16/03/2023.
//

#include "MultiPersona.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include "../../include/LogUtil.h"
#include "Behavior.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>
#include <map>

MultiPersona::MultiPersona(const Milieu* milieu, const string name, std::map<string, Behavior*> &behaviors) {
    this->milieu=milieu;
    this->name = name;
    for (auto b : behaviors) {
        this->behaviors.push_back(b.second);
    }
    LOG_DEBUG("Create MultiPersona behavior operand");
}

MultiPersona::~MultiPersona() { LOG_DEBUG("Destroy MultiPersona behavior operand"); }

void MultiPersona::updateParameters(Bug* bug) {
    auto random_number = (rand() % behaviors.size());
    behaviors[random_number]->updateParameters(bug);
}
