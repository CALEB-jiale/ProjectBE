#include "Ear.h"
#include "../bug/Bug.h"
#include "../bug/BugFactory.h"

using namespace std;


Sensor* Sensor::clone() const {
  return new Sensor(this->owner, this->detectCapacity, this->distance);
}

