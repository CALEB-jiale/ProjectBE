#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_

#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;


class Milieu;


class Aquarium : public CImgDisplay {
private:
    Milieu* milieu;
    BugFactory* bugFactory;
public:
    Aquarium(int width, int length, int delay);
    ~Aquarium();
    Milieu* getMilieu() { return milieu; }
    void run();
    void addBug(int token);
};

#endif
