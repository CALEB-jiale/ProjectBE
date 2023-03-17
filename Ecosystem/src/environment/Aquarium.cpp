#include "Aquarium.h"
#include "Milieu.h"
#include "../../include/Random.h"

// get base random alias which is auto seeded and has static API and internal state
using Random = effolkronium::random_static;

Aquarium::Aquarium(int width, int height, int _delay) : CImgDisplay(), delay(_delay) {
    int screenWidth = 1280; //screen_width();
    int screenHeight = 1024; //screen_height();
    
    bugFunction = BugFunction.getBugFunction();
    
    cout << "const Aquarium" << endl;

    milieu = new Milieu(width, height);
    assign(*milieu, "Simulation d'ecosysteme");

    move(static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-height)/2));
}

Aquarium::~Aquarium() {
   cout << "Destruct Aquarium" << endl;
   delete milieu;
}

void Aquarium::addBug(int token){
    if(token == 0) {
        token = Random::get(1, 5);
    }
    
    switch(token) {
        case 1:
            milieu->addBug(*(bugFunction->getMultiPersona()))
            break;
        case 2:
            milieu->addBug(*(bugFunction->getFearful()))
            break;
        case 3:
            milieu->addBug(*(bugFunction->getSuicideBoomer()))
            break;
        case 4:
            milieu->addBug(*(bugFunction->getSocial()))
            break;
        case 5:
            milieu->addBug(*(bugFunction->getCareful()))
            break;
    }
}

void Aquarium::run() {
    cout << "running Aquarium" << endl;

    while (!is_closed()) {
        if ( is_key() ) {
            cout << "You have pressed the key " << static_cast<unsigned char>( key() );
            cout << " (" << key() << ")" << endl;
            
            if (is_keyESC()) {
                close();
            } else if (is_keyA()) {
                addBug(0);
            } else if (is_keyM()) {
                addBug(1);
            } else if (is_keyF()) {
                addBug(2);
            } else if (is_keyB()) {
                addBug(3);
            } else if (is_keyS()) {
                addBug(4);
            } else if (is_keyC()) {
                addBug(5);
            } else if (is_keyK()) {
                milieu->kill();
            }
        }

        milieu->step();
        display(*milieu);

        wait(delay);
    }
}
