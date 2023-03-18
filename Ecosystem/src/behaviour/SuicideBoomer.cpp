//
// Created by Franck XU on 16/03/2023.
//

#include "SuicideBoomer.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include "../../include/LogUtil.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

SuicideBoomer::SuicideBoomer(const Milieu *milieu) : Behavior(milieu) {
    this->milieu=milieu;
    LOG_DEBUG("Create SuicideBoomer behavior operand")
}

SuicideBoomer::~SuicideBoomer() {
    LOG_DEBUG("Destroy SuicideBoomer behavior operand")
}

void SuicideBoomer::updateParameters(Bug *bug) {
    double distance_min = static_cast<double>(INFINITY);

    auto bug_pos = bug->getPosition();
    auto bug_x = bug_pos.first;
    auto bug_y = bug_pos.second;

    int closest_neighbor_x;
    int closest_neighbor_y;
    double closest_distance = static_cast<double>(INFINITY);

    vector<Bug const*> const neighbors = milieu.getNeighbors(*bug);
    for (auto neighbor : neighbors) {
        auto neighbor_coord = neighbor->getPosition();
        auto neighbor_x = neighbor_coord.first;
        auto neighbor_y = neighbor_coord.second;

        double diff_distance = pow(neighbor_x - bug_x, 2) + pow(neighbor_y - bug_y, 2);

        if (diff_distance < closest_distance) {
            closest_distance = diff_distance;
            closest_neighbor_x = neighbor_x;
            closest_neighbor_y = neighbor_y;
        }
    }

    if (closest_distance < static_cast<double>(INFINITY)) {
        double orientation = atan2(closest_neighbor_y - bug_y, closest_neighbor_x - bug_x);
        bug->setOrientation(orientation);
    }
}
