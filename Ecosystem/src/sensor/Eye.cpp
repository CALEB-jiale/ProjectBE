#include <cmath>
#include "Ear.h"
#include "../bug/Bug.h"
#include "../bug/BugFactory.h"
#include "../../include/Random.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

double Eye::ANGLE_MIN = 0.2 * M_PI;
double Eye::ANGLE_MAX = 1.8 * M_PI;
double Eye::DISTANCE_MIN = 0.;
double Eye::DISTANCE_MAX = 30.;
double Eye::DETECT_CAPACITY_MIN = 20.;
double Eye::DETECT_CAPACITY_MAX = 100.;

Eye::Eye(Bug* owner) {
    this->owner = owner;
    this->detectCapacity = Random::get(Eye.DETECT_CAPACITY_MIN, Eye.DETECT_CAPACITY_MAX);
    this->distance = Random::get(Eye.DISTANCE_MIN, Eye.DISTANCE_MAX);
    this->angle = Random::get(Eye.ANGLE_MIN, Eye.ANGLE_MAX);
}

void Eye::draw(UImg &support) const {
    T* color = new T[3];
    color[0] = 100;
    color[1] = 100;
    color[2] = 100;
    
    double orientation = this->owner->getOrientation();
    auto position = this->owner->getPosition();
    int x = position.first;
    int y = position.second;
    
    double x1 = x + std::cos(orientation)*BugFactory.SIZE/2.1;
    double y1 = y - std::sin(orientation)*BugFactory.SIZE/2.1;
    
    double x2 = x1 + std::cos(orientation + this->angle / 2) * this->distance;
    double y2 = y1 - std::sin(orientation + this->angle / 2) * this->distance;

    double x3 = x1 + std::cos(orientation - this->angle / 2) * this->distance;
    double y3 = y1 - std::sin(orientation - this->angle / 2) * this->distance;
    
    support.draw_triangle(x1, y1, x2, y2, x3, y3, color, 0.2);
}

