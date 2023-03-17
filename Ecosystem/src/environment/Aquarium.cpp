#include "Aquarium.h"
#include "Milieu.h"
//#include "behavior/Prudent.h"
//#include "behavior/Craintif.h"
//#include "behavior/SuicideBoomber.h"
//#include "behavior/Social.h"
//#include "behavior/MultiplePersona.h"


Aquarium::Aquarium(int width, int length) : CImgDisplay(){
   int         screenWidth = 1280; //screen_width();
    int         screenHeight = 1024; //screen_height();
   mil = new Milieu(width, length);
   cout << "Construct Aquarium" << endl;
   assign( *mil, "Ecosystem Simulation" );

   move( static_cast<int>((screenWidth-width)/2), static_cast<int>((screenHeight-length)/2) );
}

Aquarium::~Aquarium(){
   cout << "Destruct Aquarium" << endl;
   delete mil;
}

void Aquarium::birth(){
   mil->addBug();
}

void Aquarium::clone(int id){
  Bug* copy = mil->getBugById(id)->clone();
   mil->addBug(copy);
}

void Aquarium::kill(int id){
   mil->getBugrById(id)->dead();
}

/*void Aquarium::setBehavior(int id, string const & behavior){
   //delete mil->getBugById(id)->getBehavior();
   if(behavior.compare("c")==0){
      mil->getBugById(id)->setBehavior(new Prudent());
   }
   else if(behavior.compare("f")==0){
      mil->getBugById(id)->setBehavior(new Craintif());
   }
   else if(behavior.compare("g")==0){
      mil->getBugById(id)->setBehavior(new Social());
   }
   else if(behavior.compare("k")==0){
      mil->getBugById(id)->setBehavior(new SuicideBoomber());
   }
   else{
      mil->getBugById(id)->setBehavior(new MultiplePersona());
   }
   
}
*/
void Aquarium::run(){
   cout << "running Aquarium" << endl;

   while ( ! is_closed() )
   {

      if (is_key(cimg::keyB)){

         birth(); 

      }

      if (is_key(cimg::keyK)){
         int id;
         cout << "which Bug do you want to kill? ?"<<endl;
         cin>>id;
         this->kill(id);
      }

      if (is_key(cimg::keyC)){
         int id;
         cout << "which Bug do you want to clone? ?"<<endl;
         cin>>id;
         this->clone(id);

      }

      if (is_key(cimg::keyS)){
         int id;
         std::string behavior;
         cout << "Which Bug do you want to modify the behavior of?"<<endl;
         cin >> id;
         cout << "What Bug do you want to attribute to it?"<<endl;
         cin >> behavior;
         setBehavior(id,behavior);
      }



      if (is_keyESC()) {
         close();
      }

     
      mil->step();
      display( *mil );

      wait( 300 );

   } 
}