#include <cmath>
#include "Ear.h"
#include "../bug/Bug.h"
#include "../../include/Random.h"
#include "../../include/HMI/UImg.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

double Ear::DISTANCE_MIN = 0.;
double Ear::DISTANCE_MAX = 30.;
double Ear::DETECT_CAPACITY_MIN = 20.;
double Ear::DETECT_CAPACITY_MAX = 100.;

Ear::Ear(Bug* owner) {
    this->owner = owner;
    this->detectCapacity = Random::get(Ear::DETECT_CAPACITY_MIN, Ear::DETECT_CAPACITY_MAX);
    this->distance = Random::get(Ear::DISTANCE_MIN, Ear::DISTANCE_MAX);
    this->angle = 2 * M_PI;
}

Ear::Ear(Bug* owner, double detectCapacity, double distance) {
    this->owner = owner;
    this->detectCapacity = detectCapacity;
    this->distance = distance;
    this->angle = 2 * M_PI;
}

Sensor* Ear::clone() const {
    return dynamic_cast<Sensor *>(new Ear(this->owner, this->detectCapacity, this->distance));
}

void Ear::draw(UImg &support) const {
    T* color = new T[3];
    color[0] = 200;
    color[1] = 200;
    color[2] = 200;
    
    double orientation = this->owner->getOrientation(); // rad
    auto position = this->owner->getPosition();
    int x = position.first;
    int y = position.second;
    
    double x1 = x + std::cos(orientation)*Bug::SIZE/2.1;
    double y1 = y - std::sin(orientation)*Bug::SIZE/2.1;
    
    support.draw_circle(x1, y1, this->distance/2., color, 0.05);
}

bool Ear::isDetected(const Bug& bug) const {
    if (this->detectCapacity <= bug.getCamouflageCapacity()) {
        return false;
    }
    
    auto position1 = this->owner->getPosition();
    int x1 = position1.first;
    int y1 = position1.second;
    
    auto position2 = bug.getPosition();
    int x2 = position2.first;
    int y2 = position2.second;
    
    double myDistance = std::sqrt( (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2) );
    
    if (myDistance >= this->distance) {
        return false;
    }
    
    return true;
}
