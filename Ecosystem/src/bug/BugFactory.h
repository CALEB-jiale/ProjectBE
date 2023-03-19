//
//  redd.h
//  
//
//  Created by Lucas on 17/03/2023.
//

#ifndef BugFactory_hpp
#define BugFactory_hpp
#ifndef

#include <iostream>

using namespace std;


class BugFactory {
private :
    
    static BugFactory* = nullptr;
    static BugFactory bugFactory;
    BehaviorFactory* behaviorFactory;
    SensorFactory* sensorFactory;
    AccessoryFacade* accessoryFacade;
    
    
    BugFactory(Milieu* milieu);

    static double LIMIT_AGE = 250 ;
    static double LIMIT_SIGHT = 30.0 ;
    static double SIZE = 2.0;
    static int NUM_BUGS = 0;
    static double LIMIT_VELOCITY = 10.0;
    static double BIRTH_RATE = 0.4;

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

