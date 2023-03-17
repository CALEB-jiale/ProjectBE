#ifndef _MILIEU_H_
#define _MILIEU_H_


#include "UImg.h"
#include "Bestiole.h"

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>


using namespace std;


class Milieu : public UImg
{

private :
      static const T          white[];
      int width, length;
      std::vector<std::shared_ptr<Bug>>   listBugs;
public:
      Milieu(int w, int l);
      ~Milieu();
      void step();
      void cloning();
      void removeDeadBugs();
      void addBug();
      void addBug(Bug* b);
      void addBug(std::vector<std::shared_ptr<Bug>>  clonedBugs);
      std::vector<std::shared_ptr<Bug>> getNeighbors(Bug* b);
      Bug* getBugById(int id);

      // getters 
      int getWidth();
      int getLength();

 

};


#endif
