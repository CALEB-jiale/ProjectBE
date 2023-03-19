#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Milieu.h"
#include "../bug/Bug.h"

const T Milieu::white[] = {(T)255, (T)255, (T)255};

Milieu::Milieu(int _width, int _height) : UImg(_width, _height, 1, 3), width(_width), height(_height) {
    cout << "const Milieu" << endl;
    std::srand(time(NULL));
}

Milieu::~Milieu() {
    cout << "Destruct the Milieu" << endl;
}

void Milieu::step() {
    cimg_forXY(*this, x, y) fillC(x, y, 0, white[0], white[1], white[2]);
    for (std::vector<Bug>::iterator it = listBugs.begin(); it != listBugs.end(); ++it){
        if (it->isAlive()) {
            it->action( *this );
            it->draw( *this );
        }
    }
}

void Milieu::addBug(Bug& bug) {
    listBugs.push_back(bug);
    listBugs.back().initCoords(width, height);
}

void Milieu::removeBug(Bug& bug) {
    auto it = std::find(listBugs.begin(), listBugs.end(), bug);

    if (it != listBugs.end()) {
        listBugs.erase(it);
    }
}

int Milieu::getNumNeighbors(Bug& bug) {
    int nb = 0;
    
    for (std::vector<Bug>::iterator it = listBugs.begin(); it != listBugs.end(); ++it)
        if (!(bug == *it) && bug.isDetected(*it)) {
            ++nb;
        }

    return nb;
}

std::vector<Bug*> Milieu::getNeighbors(Bug& bug) {
    std::vector<Bug*> neighbors;

    for (std::vector<Bug>::iterator it = listBugs.begin(); it != listBugs.end(); ++it) {
        if (!(bug == *it) && bug.isDetected(*it)) {
            neighbors.push_back(&(*it));
        }
    }

    return neighbors;
}

void Milieu::kill() {
    for (std::vector<Bug>::iterator it = listBugs.begin(); it != listBugs.end(); ++it){
        if (it->isAlive()) {
            it->kill();
            return;
        }
    }
}
