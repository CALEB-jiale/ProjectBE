#ifndef _BUGFACTORY_H_
#define _BUGFACTORY_H_
#ifndef

#include <iostream>

using namespace std;
class Bug;
class Milieu;


class BugFactory {
private :
    static BugFactory* bugFactory;
    
    BehaviorFactory* behaviorFactory;
    SensorFactory* sensorFactory;
    AccessoryFacade* accessoryFacade;
    
    Milieu* milieu;
    BugFactory(Milieu* milieu);

public:
    ~BugFactory();
    BugFactory* getBugFactory();
    Bug* getSuicideBoomer();
    Bug* getCareful();
    Bug* getSocial();
    Bug* getFearful();
    Bug* getMultiPersona();
    
    BugFactory(const BugFactory&) = delete;
    BugFactory& operator=(const BugFactory&) = delete;
}



#endif /* BugFactory_hpp */

