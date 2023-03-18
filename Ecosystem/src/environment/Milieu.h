#ifndef _MILIEU_H_
#define _MILIEU_H_

#include "UImg.h"
#include <vector>

class Bug;

class Milieu : public UImg
{

private :
    static const T white[];
    int width, length;
    std::vector<Bug> listBugs;
public:
    Milieu(int _width, int _height);
    ~Milieu();
    void step();
    void addBug(Bug& bug);
    void removeBug(Bug& bug);
    std::vector<Bug*> getNeighbors(Bug& bug);
    int getNumNeighbors(Bug& bug);
    int getWidth() const { return width; };
    int getHeight() const { return height; };
    void kill();
};


#endif
