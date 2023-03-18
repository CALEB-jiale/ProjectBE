//
// Created by Franck XU on 16/03/2023.
//

#include "Social.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include "../../include/LogUtil.h"
#include <cmath>
#include <vector>

using namespace std;

Social::Social(const Milieu *milieu) : Behavior(milieu) {
    this->milieu=milieu;
    LOG_DEBUG("Create Social behavior operand");
}

Social::~Social() { LOG_DEBUG("Destroy Social behavior operand"); }

void Social::updateParameters(Bug *bug) {
    vector<Bug const*> const neighbors = milieu.getNeighbors(*bug);
    double orientation = 0;
    
    for (auto neighbor : neighbors) {
        orientation += neighbor->getOrientation();
    }

    if (neighbors.size() > 0) {
        orientation /= neighbors.size();
    }

    while(orientation < 0) {
        orientation += 2 * M_PI;
    }

    while(orientation >= 2 * M_PI) {
        orientation -= 2 * M_PI;
    }

    bug->setOrientation(orientation);
}
