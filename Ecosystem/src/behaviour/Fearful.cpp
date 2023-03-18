//
// Created by Franck XU on 16/03/2023.
//

#include "Fearful.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include "../../include/LogUtil.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

Fearful::Fearful(const Milieu* milieu) {
    this->milieu=milieu;
    LOG_DEBUG("Create fearful behavior operand");
}

Fearful::~Fearful() { LOG_DEBUG("Destroy fearful behavior operand"); }

void Fearful::updateParameters(const Bug *bug) {
    T color[3] = {(T)0, (T)0, (T)255};
    bug->setColor(color);
    
    vector<Bug const *> neighbors = milieu->getNeighbors(*bug);
    int num_neighbor = neighbors.size();
    
    if (num_neighbor > 0) {
        double avg_orientation = 0;
        
        for (auto neighbor : neighbors) {
            auto neighbor_pos = neighbor->getPosition();
            auto bug_pos = bug->getPosition();
            double neighbor_orientation = atan2(neighbor_pos.second - bug_pos.second, neighbor_pos.first - bug_pos.first);
            while (neighbor_orientation < 0) {
                neighbor_orientation += 2 * M_PI;
            }
            while (neighbor_orientation >= 2 * M_PI) {
                neighbor_orientation -= 2 * M_PI;
            }
            avg_orientation += neighbor_orientation;
        }
        avg_orientation /= num_neighbor;
        
        double new_orientation = avg_orientation + M_PI;
        while (new_orientation < 0) {
            new_orientation += 2 * M_PI;
        }
        while (new_orientation >= 2 * M_PI) {
            new_orientation -= 2 * M_PI;
        }
        
        bug->setOrientation(new_orientation);
    }
    
    if (num_neighbor > 2) {
        bug->switchToFastVelocity();
    } else {
        bug->switchToNormalVelocity();
    }
}
