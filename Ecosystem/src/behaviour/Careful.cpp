//
// Created by Franck XU on 16/03/2023.
//

#include "Careful.h"
#include "../bug/Bug.h"
#include "../environment/Milieu.h"
#include "../../include/LogUtil.h"
#include <cmath>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

Careful::Careful(const Milieu* milieu, const string name) {
    this->milieu = milieu;
    this->name = name;
    LOG_DEBUG("Create Careful behavior operand");
}

Careful::~Careful() { LOG_DEBUG("Destroy Careful behavior operand"); }

void Careful::updateParameters(Bug *bug) {
    auto bug_velocity = bug->getCurrentVelocity();
    auto bug_orientation = bug->getOrientation();
    auto bug_pos = bug->getPosition();
    auto bug_x_esti = bug_pos.first + bug_velocity * cos(bug_orientation);
    auto bug_y_esti = bug_pos.second - bug_velocity * sin(bug_orientation);

    Bug const* closest_neighbor = nullptr;
    double closest_distance = std::numeric_limits<double>::infinity();

    vector<Bug const*> const neighbors = milieu->getNeighbors(bug);
    for (auto neighbor : neighbors) {
        auto velocity = neighbor->getCurrentVelocity();
        auto orientation = neighbor->getOrientation();
        auto neighbor_coord = neighbor->getPosition();

        auto neighbor_x_esti = neighbor_coord.first + velocity * cos(orientation) ;
        auto neighbor_y_esti = neighbor_coord.second - velocity * sin(orientation);

        // Estimer la distance entre les insectes et le risque de collision imminente
        double diff_distance = pow(neighbor_x_esti - bug_x_esti, 2) + pow(neighbor_y_esti - bug_y_esti, 2);
        double distance = sqrt(diff_distance);

        if (diff_distance < closest_distance) {
            closest_distance = diff_distance;
            closest_neighbor = neighbor;
        }
    }

    if (closest_neighbor) {
        // Évitement des collisions et réorientation
        double neighbor_orientation = closest_neighbor->getOrientation();
        double delta_orientation = neighbor_orientation - bug_orientation;
        double perpendicular_orientation = delta_orientation + M_PI_2;
        bug->setOrientation(perpendicular_orientation);
    }
}

