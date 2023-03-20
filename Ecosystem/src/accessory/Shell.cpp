#include "Shell.h"
#include "../bug/Bug.h"
#include "../../include/Random.h"

double FACTOR_VELOCITY = 1.5;
double FACTOR_DEATH = 1.5;

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

void Shell::updateParameters(Bug* bug) const {
    double randomFactor = Random::get(1., Shell::FACTOR_VELOCITY);
    bug->updateVelocity(1/randomFactor);
    
    randomFactor = Random::get(1., Shell::FACTOR_DEATH);
    bug->updateDeathProbability(randomFactor);
}
