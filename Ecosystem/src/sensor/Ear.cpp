#include <random>
#include "Ear.h"
#include "../bug/Bug.h"

float Ear::DISTANCE_MIN = 0.;
float Ear::DISTANCE_MAX = 30.;
float Ear::DETECT_CAPACITY_MIN = 20.;
float Ear::DETECT_CAPACITY_MIN = 100.;

Ear::Ear(Bug* owner, float detectCapacity, float distance) {
    this->owner = owner;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    float random_num = dis(gen);
    
    this->detectCapacity = detectCapacity;
    this->distance = distance;
}

void Ear::draw(UImg &support) const {
    T* color = new T[3];
    color[0] = 100;
    color[1] = 100;
    color[2] = 100;
    
    auto position = this->owner->getPosition();
    int x = position.first;
    int y = position.second;
    
    support.draw_circle(x, y, this->distance/2., color, 0.05);
}
