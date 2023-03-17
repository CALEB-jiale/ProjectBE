//
// Created by Franck XU on 16/03/2023.
//

#include "Careful.h"
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

Careful::Careful(const Milieu *milieu) : Behavior(milieu) {
    LOG_DEBUG("Create Careful behavior operand");
}

Careful::~Careful() { LOG_DEBUG("Destroy Careful behavior operand"); }

void Careful::updateParameters(Bestiole *bug) {
    double distance_min = static_cast<double>(INFINITY);

    auto bug_velocity = bug.getCurrentVelocity();
    auto bug_orientation = bug.getOrientation();
    auto bug_pos = bug.getPosition();
    auto bug_x_esti = bug_pos.first + bug_velocity * cos(bug_orientation);
    auto bug_y_esti = bug_pos.second + bug_velocity * sin(bug_orientation);

    Bestiole const* closest_neighbor = nullptr;
    double distance_min = static_cast<double>(INFINITY);

    vector<Bestiole const*> const neighbors = milieu.getNeighbors(bug);
    for (auto neighbor : neighbors) {
        auto velocity = neighbor.getCurrentVelocity();
        auto orientation = neighbor.getOrientation();
        auto neighbor_coord = neighbor.getPosition();

        auto neighbor_x_esti = neighbor_coord.first + velocity * cos(orientation) ;
        auto neighbor_y_esti = neighbor_coord.second + velocity * sin(orientation);

        double diff_distance = pow(neighbor_x_esti - bug_x_esti, 2) + pow(neighbor_y_esti - bug_y_esti);

        if (diff_distance < distance_min) {
            distance_min = diff_distance;
            closest_neighbor = neighbor;
        }
    }

    if (closest_neighbor) {
        bug.setOrientation(closest_neighbor.getOrientation() + M_PI)
    }
}