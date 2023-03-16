#include "Ear.h"
#include "../bug/Bug.h"

float Ear::DISTANCE_MIN = 0.;
float Ear::DISTANCE_MAX = 30.;
float Ear::DETECT_CAPACITY_MIN = 20.;
float Ear::DETECT_CAPACITY_MIN = 100.;

Ear::Ear(Bug* owner, float detectCapacity, float distance) {
  this->owner = owner;
  this->detectCapacity = detectCapacity;
  this->distance = distance;
}
