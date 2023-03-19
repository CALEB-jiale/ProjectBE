//
//  BugFactory.cpp
//  
//
//  Created by Lucas on 17/03/2023.
//

#include "BugFactory.h"
#include "SensorFactory.h"
#include "BehaviorFactory.h"
#include<iostream>

using namespace std;

BugFactory* BugFactory::bugFactory = nullptr;


private :
    static double LIMIT_AGE = ;
    static double LIMIT_SIGHT = ;
    static double SIZE =;
    static int NUM_BUG =;
    static double LIMIT_VELOCITY =;
    static double BIRTH_RATE =;


    BugFactory::BugFactory(milieu *milieu) {
    
        this->behaviorFactory = BehaviorFactory.getBehaviorFactory(Milieu);
        this->sensorFactory = new SensorFactory();
        this->accessoryFacade = new AccessoryFacade();
    
    
    
        LOG_DEBUG("Creating Bug Factory");
    }
   
public :
    BugFactory* BugFactory::getBugFactory(milieu *milieu) {
        if(bugFactory == nullptr) {
            bugFactory = new BugFactory();
        }
        return bugFactory;
    }

 //   Bug* BugFactory::getBug(BehaviorFactory) {
        
   //     return ;
   //     }

    Bug* BugFactory::getSuicideBoomer() {
        return new suicideboomer;
        }
    
    Bug* BugFactory::GetCareful(){
        
        return new careful;
        }

    Bug* BugFactory::getMultiPersona() {
        return new multipersona;
        }

    Bug* BugFactory::getSocial() {
        return new social;
        }

  

    BugFactory::~BugFactory() {
        factory = nullptr;
        LOG_DEBUG("Destroying Bug Factory");
        }






    

