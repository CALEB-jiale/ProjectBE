#ifndef _AQUARIUM_H_
#define _AQUARIUM_H_


#include <iostream>
#include <CImg.h>

using namespace std;
using namespace cimg_library;


class Milieu;


class Aquarium : public CImgDisplay
{


private:
    Milieu* mil;
public:
    Aquarium(int width, int length);
    ~Aquarium();
    void birth();
    void kill(int id);
    void clone(int id);
    void setBehavior(int id, string const &  behavior);
    void run();
};


#endif
