#ifndef _Bug_H_
#define _Bug_H_

#include <array>
#include <iostream>
#include <memory>
#include <vector>

#include "../../include/HMI/UImg.h"
#include "../sensor/Sensor.h"

using namespace std;

using Color = array<T, 3>;


class Bug {
private:
    // position variables
    int ID;
    Milieu* milieu;

    int x;
    int y;
    double orientation;
    // affichage
    double cumulX, cumulY;

    double currentVelocity;
    double normalVelocity;
    double fastVelocity;

    int age;
    int ageLimit;
    bool alive;

    double camouflageCapacity;
    double cloneProbability;
    double deathProbability;
    
    std::vector<unique_ptr<Sensor>> sensors;
    Behavior* behavior;
    T* color;

public: // Forme canonique :
    static const double LIMIT_AGE;
    static const double LIMIT_SIGHT;
    static const double SIZE;
    static const double LIMIT_VELOCITY;
    static const double LIMIT_CLONE_RATE;
    static int NUM_BUGS;
    
    Bug(); // Constructeur par defaut
    Bug(const Bug &b); // Constructeur de copies
    Bug(Bug &&b); // Move constructeur

    Bug &operator=(Bug const &b);

    ~Bug();

    void action(Milieu& milieu);
    void draw(UImg &support);
    bool isDetected(Bug& bug);
    void initLocation(int xLim, int yLim);
    void addSensor(Sensor* sensor);
    void removeSensor(Sensor* sensor);
    void setBehavior(Behavior* behavior);
    double getCamouflageCapacity() const { return camouflageCapacity; }
    double getOrientation() const { return orientation; }
    pair<int, int> getPosition() const;
    void switchToFastVelocity() { currentVelocity = fastVelocity; }
    void switchToNormalVelocity() { currentVelocity = normalVelocity; }
    void setOrientation(double orientation);
    void updateVelocity(double velocityFactor);
    void updateCamouflageCapacity(double camouflageCapacity);
    void updateDeathProbability(double deathProbFactor);
    void setColor(int r, int g, int b);

    bool isCollidingWith(Bug const &b);

    bool isAlive() const { return alive; }
    void kill() { alive = false; }

private:
    void move(int xLim, int yLim);
    void clone();
};

bool operator==(const Bug &b1, const Bug &b2);
bool operator!=(const Bug &b1, const Bug &b2);

#endif
