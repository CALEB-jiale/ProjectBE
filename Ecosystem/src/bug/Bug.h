#ifndef _BESTIOLES_H_
#define _BESTIOLES_H_

#include "../../include/HMI/UImg.h"
#include "../accessoire/IAccessoire.h"
#include "../sensor/Sensor.h"

#include <array>
#include <iostream>
#include <memory>
#include <vector>


using namespace std;

using Color = array<T, 3>;


class Bug {
private:
    // position variables
    int id;

    int x;
    int y;

    double currentVelocity;
    double normalVelocity;
    double fastVelocity;

    double orientation;

    int age;
    int ageLimit;

    double camouflageCapacity;
    double cloneProbability;
    double deathProbability;

    // affichage
    double cumulX, cumulY;
    std::vector<unique_ptr<Sensor>> sensors;

    Behavior* behavior;

    Color color;

public: // Forme canonique :
    Bug(int id, double normal_velocity, double max_velocity, int age_limit,
           double death_prob, double clone_prob, double orientation); // Constructeur par defaut
    Bug(const Bestiole &b);  // Constructeur de copies
    Bug(Bestiole &&b);       // Move constructeur

    Bestiole &operator=(Bestiole const &b);

    ~Bestiole();

    void action(Milieu& milieu);

    bool isDetectedBy(Bug& b);

    void initLocation(int x, int y);

    void addSensor(Sensor* sensor);

    void removeSensor(Sensor* sensor);

    void setBehavior(Behavior* behavior);

    double getCamouflageCapacity();

    pair<int, int> getPosition() const;

    double getOrientation();

    void switchToFastVelocity();

    void switchToNormalVelocity();

    void setOrientation(double orientation);

    void updateVelocity(double velocity);

    void updateCamouflageCapacity(double camouflage_capacity);

    void updateDeathProbability(double death_prob);

    void setColor(Color color);

    bool isCollidingWith(Bug const &b);

    void draw(UImg &support);

private:
    void move(int xLim, int yLim);
};

bool operator==(const Bug &b1, const Bug &b2);
bool operator!=(const Bestiole &b1, const Bestiole &b2);

#endif
