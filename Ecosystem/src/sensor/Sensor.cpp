#include "Ear.h"
#include "../bug/Bug.h"
#include "../bug/BugFactory.h"

using namespace std;

void Oreilles::draw(UImg &support) const {
    T* color = new T[3];
    color[0] = 100;
    color[1] = 100;
    color[2] = 100;
    
    float orientation = this->owner->getOrientation();
    auto position = this->owner->getPosition();
    int x = position.first;
    int y = position.second;
    
    float xt = x + cos(orientation)*BugFactory.SIZE/2.1;
    
    support.draw_circle(xt, yt, this->distance_max / 2., couleur, 0.05);
}


Sensor* Sensor::clone() const {
  return new Sensor(this->owner, this->detectCapacity, this->distance);
}

