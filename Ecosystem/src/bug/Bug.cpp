#include "Bug.h"

#include "../../include/LogUtil.h"
#include "../constants.h"
#include "../environment/Milieu.h"
#include "Bug.h"
#include "../sensor/Sensor.h"
#include "../behaviour/Behavior.h"

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

using namespace std;

Bug::Bug(int ID, double normal_velocity, double max_velocity, int age_limit,
              double death_prob, double clone_prob, double orientation) {

    // Initialization
    this->ID = ID;

    this->x = 0;
    this->y = 0;

    this->currentVelocity = normal_velocity;
    this->normalVelocity = normal_velocity;
    this->fastVelocity = max_velocity;

    this->orientation = orientation;

    this->age = 0;
    this-> ageLimit = age_limit;

    this->deathProbability = death_prob;
    this->camouflageCapacity = 0;
    this->cloneProbability = clone_prob;

    cumulX = cumulY = 0.;

    this->behavior = nullptr;

    this-> alive = true;

    LOG_DEBUG("Construire Bug[%d] par default", this->identite);


}

// TODO move construteur
Bug::Bug(const Bug &b) {
  // TODO : update

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

void Bug::initLocation(int x, int y) {
    this->x = x;
    this->y = y;
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


