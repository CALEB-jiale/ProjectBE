#include "Bug.h"

#include "../../include/LogUtil.h"
#include "../constants.h"
#include "../environment/Milieu.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

#include "Bug.h"
#include "../sensor/Sensor.h"
#include "../behavior/Behavior.h"
#include "../../include/Random.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;
using namespace std;

const double MAX_AGE = 250;
const double MIN_AGE = 50;
const double MAX_SIGHT = 30.0;
const double MIN_SIGHT = 10.0;
const double SIZE = 8.0;
const double MAX_VELOCITY = 10.0;
const double MIN_VELOCITY = 2.0;
const double MAX_CLONE_PROB = 0.2;
const double MAX_DEATH_PROB = 0.5;
const double MIN_DEATH_PROB = 0.05;
int NUM_BUGS = 0;

Bug::Bug() {

    // Initialization
    this->ID = ++NUM_BUGS;

    x = y = 0;
    cumulX = cumulY = 0.;
    orientation = static_cast<double>(rand())/RAND_MAX*2.*M_PI;

    this->normalVelocity = Random::get(Bug.MIN_VELOCITY, Bug.MAX_VELOCITY * 0.8);
    this->fastVelocity = Random::get(Bug.MAX_VELOCITY * 0.8, Bug.MAX_VELOCITY);
    this->currentVelocity = normalVelocity;

    this->age = 0;
    this->ageLimit = Random::get(Bug.MIN_AGE, Bug.MAX_AGE);
    this-> alive = true;

    this->camouflageCapacity = 0;
    this->cloneProbability = clone_prob;
    this->deathProbability = Random::get(Bug.MIN_AGE, Bug.MAX_AGE);

    this->behavior = nullptr;
    this->color = new T[3];
    color[0] = 128;
    color[1] = 128;
    color[2] = 128;
    
    LOG_DEBUG("Construire Bug[%d] par default", this->identite);
}

// move construteur
Bug::Bug(const Bug &b) {
  LOG_DEBUG("Construire Bug[%d] par copy", b.identite);
  *this = b;
}

// Move Constructeur
Bug::Bug(Bug &&b) : ID(b.ID), x(b.x), y(b.y), currentVelocity(b.currentVelocity),
      fastVelocity(b.fastVelocity), normalVelocity(b.normalVelocity) {

    LOG_DEBUG("Creating Bug[%d] using move", this->identite);

    cumulX = cumulY = 0.;

    // other variables
    this->age = b.age;
    this->age_limit = b.age_limit;
    this->deathProbability = b.deathProbability;
    this->cloneProbability = b.cloneProbability;
    this->camouflageCapacity = b.camouflageCapacity;

    //clone all the capteurs
    this->sensors = move(b.sensors);

    this->behavior = b.behavior;

    this->orientation = b.orientation;

    this->alive = true;
}

Bug::~Bug(void) {
  LOG_DEBUG("Destruire Bug[%d]", this->identite);
}

Bug &Bug::operator=(Bug const &b) {
    ID = b.ID;
    x = b.x;
    y = b.y;
    cumulX = cumulY = 0.;

    this->normalVelocity = b.normalVelocity;
    this->currentVelocity = b.currentVelocity;
    this->fastVelocity = b.fastVelocity;

    // other variables
    this->age = b.age;
    this->age_limit = b.age_limit;
    this->deathProbability = b.deathProbability;

    sensors.clear();
    for (auto const &sensor : b.sensors) {
        sensors.push_back(move(sensor->clone()));
    } // clone all the capteurs

    if (b.behavior) {
        behavior = b.behavior;
    } // clone the behavior

    orientation = b.orientation;
    this->alive = b.alive;
    return *this;
}

void Bug::move(int xLim, int yLim) {
    double nx, ny;
    double dx = cos(orientation) * velocity;
    double dy = -sin(orientation) * velocity;
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


void Bug::action(Milieu &milieu) {
    age++;

        // ################# Delete bug when reaches age_limit ? ####################
    if (age > age_limit) {
        alive = false;
        return;
    }

    const auto neighbors = milieu.getNeighbors(*this);
    for (auto neighbor : neighbors) {
        if (this->isCollidingWith(*neighbor)) {
            if (Random::get<bool>(deathProbability)) {
                alive = false;
                return;
            }

            this->orientation = - orientation;
        }
    }

    if (behavior) {
        behavior->updateParameters(this);
    }

    move(monMilieu.getWidth(), monMilieu.getHeight());
}


void Bug::setBehavior(Behavior* behavior) {
    this->behavior = behavior;
}

bool Bug::isDetected(const Bug &b) const {
    for (auto const &capteur : sensors) {
        if (capteur->isDetected(b)) {
            return true;
        }
    }
    return false;
}

void Bug::initLocation(int xLim, int yLim) {
    x = rand() % xLim;
    y = rand() % yLim;
}


void Bug::addSensor(unique_ptr<Sensor> &&sensor) {
    this->sensors.push_back(move(sensor));
}

void Bug::removeSensor(Sensor *sensor) {
    // TODO
}

void Bug::setBehavior(Behavior* behavior) {
    this->behavior = behavior;
}

double Bug::getCamouflageCapacity() { return camouflageCapacity; }

pair<double, double> Bug::getPosition() const { return {x, y}; }

double Bug::getOrientation() const { return orientation; }

void Bug::switchToFastVelocity() { this->currentVelocity = fastVelocity; }

void Bug::switchToNormalVelocity() { this-> currentVelocity = normalVelocity; }

void Bug::setOrientation(double orientation) { this->orientation = orientation; }

void Bug::updateVelocity(double velocity) {
    this->currentVelocity = min(velocity, fastVelocity);
}

void Bug::updateCamouflageCapacity(double camouflage_capacity) {
    this->camouflageCapacity = camouflage_capacity;
}

void Bug::setColor(Color color) {
    this->color = color;
}

bool Bug::isCollidingWith(Bug const &b) const {
    int dx = x - b.x;
    int dy = y - b.y;
    return dx * dx + dy * dy <= AFF_SIZE * AFF_SIZE;
}

void Bug::draw(UImg &support) {

    double xt = x + cos(orientation) * AFF_SIZE / 2.1;
    double yt = y - sin(orientation) * AFF_SIZE / 2.1;

    for (auto const &sensor : sensors) {
        capteur->draw(support, xt, yt, orientation);
    }
    support.draw_ellipse(x, y, AFF_SIZE, AFF_SIZE / 5.,
                       -orientation / M_PI * 180., color.data());
    support.draw_circle(xt, yt, AFF_SIZE / 2., color.data());
}

bool Bug::isAlive() { return alive; }


bool operator==(const Bug &b1, const Bug &b2) {
    return (b1.ID == b2.ID);
}

bool operator!=(const Bug &b1, const Bug &b2) { return !(b1 == b2); }


