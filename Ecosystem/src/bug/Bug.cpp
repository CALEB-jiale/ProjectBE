#include "Bug.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

#include "../sensor/Sensor.h"
#include "../behavior/Behavior.h"
#include "../../include/Random.h"
#include "../../include/LogUtil.h"
#include "../environment/Milieu.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;
using namespace std;

const double Bug::MAX_AGE = 250;
const double Bug::MIN_AGE = 50;
const double Bug::MAX_SIGHT = 30.0;
const double Bug::MIN_SIGHT = 10.0;
const double Bug::SIZE = 8.0;
const double Bug::MAX_VELOCITY = 10.0;
const double Bug::MIN_VELOCITY = 2.0;
const double Bug::MAX_CLONE_PROB = 0.2;
const double Bug::MAX_DEATH_PROB = 0.5;
const double Bug::MIN_DEATH_PROB = 0.05;
int Bug::NUM_BUGS = 0;

Bug::Bug(Milieu* milieu) {
    // Initialization
    this->milieu = milieu;
    this->ID = ++NUM_BUGS;

    x = y = 0;
    cumulX = cumulY = 0.;
    orientation = static_cast<double>(rand())/RAND_MAX*2.*M_PI;

    this->normalVelocity = Random::get(MIN_VELOCITY, MAX_VELOCITY * 0.8);
    this->fastVelocity = Random::get(Bug::MAX_VELOCITY * 0.8, Bug::MAX_VELOCITY);
    this->currentVelocity = normalVelocity;

    this->age = 0;
    this->ageLimit = Random::get(Bug::MIN_AGE, Bug::MAX_AGE);
    this-> alive = true;

    this->camouflageCapacity = 0;
    this->cloneProbability = MAX_CLONE_PROB;
    this->deathProbability = Random::get(Bug::MIN_AGE, Bug::MAX_AGE);

    this->behavior = nullptr;
    
    LOG_DEBUG("Construire Bug[%d] par default", this->identite);
}

Bug::Bug(const Bug& bug) {
    LOG_DEBUG("Construire Bug[%d] par copy", b.identite);
    this->ID = ++NUM_BUGS;
    this->milieu = bug.milieu;
    x = bug.x;
    y = bug.y;
    orientation = bug.orientation;
    cumulX = cumulY = 0.;

    this->normalVelocity = bug.normalVelocity;
    this->currentVelocity = bug.currentVelocity;
    this->fastVelocity = bug.fastVelocity;

    // other variables
    this->age = bug.age;
    this->ageLimit = bug.ageLimit;
    this->alive = bug.alive;

    this->deathProbability = bug.deathProbability;

    sensors.clear();
    for (auto const &sensor : bug.sensors) {
        sensors.push_back(sensor->clone());
    } // clone all the capteurs

    if (bug.behavior) {
        behavior = bug.behavior;
    } // clone the behavior
}

Bug::~Bug() {
    LOG_DEBUG("Destruire Bug[%d]", this->identite);
    for (auto& sensor : sensors) {
        delete sensor;
    }
}

void Bug::action() {
    age++;
    if (age > ageLimit) {
        alive = false;
        return;
    }

    const auto neighbors = milieu->getNeighbors(*this);
    
    cout << "Bug neighbor getted" << endl;
    
    for (auto neighbor : neighbors) {
        if (this->isCollidingWith(*neighbor)) {
            if (Random::get<bool>(deathProbability)) {
                alive = false;
                return;
            }
            this->orientation = orientation + M_PI;
        }
    }
    
    cout << "Bug penged" << endl;

    if (behavior) {
        behavior->updateParameters(this);
    }
    
    move();
}

void Bug::draw(UImg &support) {
    double xt = x + cos(orientation) * SIZE / 2.1;
    double yt = y - sin(orientation) * SIZE / 2.1;

    for (auto sensor : sensors) {
        sensor->draw(support);
    }
    
    auto color = behavior->getColor();
    
    support.draw_ellipse(x, y, SIZE, SIZE / 5., -orientation / M_PI * 180., color.data());
    support.draw_circle(xt, yt, SIZE / 2., color.data());
}

bool Bug::isDetected(const Bug& bug) const {
    for (auto const sensor : sensors) {
        if (sensor->isDetected(bug)) {
            return true;
        }
    }
    return false;
}

void Bug::initLocation(int xLim, int yLim) {
    this->x = rand() % xLim;
    this->y = rand() % yLim;
}


void Bug::addSensor(Sensor* sensor) {
    this->sensors.push_back(sensor);
}

void Bug::setBehavior(Behavior* behavior) {
    this->behavior = behavior;
}

double Bug::getCamouflageCapacity() const { return camouflageCapacity; }

double Bug::getOrientation() const { return orientation; }

pair<int, int> Bug::getPosition() const { return {this->x, this->y}; }

void Bug::switchToFastVelocity() { this->currentVelocity = fastVelocity; }

void Bug::switchToNormalVelocity() { this->currentVelocity = normalVelocity; }

double Bug::getCurrentVelocity() const { return currentVelocity; }

void Bug::setOrientation(double orientation) { this->orientation = orientation; }

void Bug::updateVelocity(double velocityFactor) {
    normalVelocity = normalVelocity * velocityFactor;
    fastVelocity = fastVelocity * velocityFactor;
    currentVelocity = normalVelocity;
}

void Bug::updateCamouflageCapacity(double camouflageCapacity) {
    this->camouflageCapacity = camouflageCapacity;
}

void Bug::updateDeathProbability(double deathProbFactor) {
    deathProbability = deathProbability * deathProbFactor;
}

bool Bug::isCollidingWith(const Bug& b) const {
    int dx = x - b.x;
    int dy = y - b.y;
    return dx * dx + dy * dy <= SIZE * SIZE;
}

void Bug::move() {
    int xLim = milieu->getWidth();
    int yLim = milieu->getHeight();
    double nx, ny;
    double dx = cos(orientation) * currentVelocity;
    double dy = -sin(orientation) * currentVelocity;
    int cx, cy;

    cx = static_cast<int>(cumulX);
    cumulX -= cx;
    cy = static_cast<int>(cumulY);
    cumulY -= cy;

    nx = x + dx + cx;
    ny = y + dy + cy;

    if ((nx < 0) || (nx > xLim - 1)) {
        orientation = M_PI - orientation;
        cumulX = 0.;
    } else {
        x = static_cast<int>(nx);
        cumulX += nx - x;
    }

     if ((ny < 0) || (ny > yLim - 1)) {
        orientation = -orientation;
        cumulY = 0.;
    } else {
        y = static_cast<int>(ny);
        cumulY += ny - y;
    }
}

void Bug::clone() {
    if (Random::get<bool>(cloneProbability)) {
        Bug bug(*this);
        milieu->addBug(bug);
    }
}

bool operator!=(const Bug &bug1, const Bug &bug2) { return !(bug1 == bug2); }

bool operator==(const Bug &bug1, const Bug &bug2) {
  return (bug1.ID == bug2.ID);
}
