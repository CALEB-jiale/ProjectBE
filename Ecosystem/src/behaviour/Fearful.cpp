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
    vector<Bug const *> &neighbors = milieu.getNeighbors(bug);
    int num_neighbor = neighbors.size();
    if (num_neighbor > 2) {
        b.switchToFastVelocity();
        b.setOrientation(b.getOrientation() + M_PI);
    } else {
        b.switchToNormalVelocity();
    }
}
