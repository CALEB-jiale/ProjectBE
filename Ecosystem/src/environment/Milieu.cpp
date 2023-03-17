#include "Milieu.h"
#include "behavior/Prudent.h"
#include "behavior/Craintif.h"
#include "behavior/SuicideBoomber.h"
#include "behavior/Social.h"
#include "behavior/MultiplePersonna.h"
#include <cstdlib>
#include <ctime>

const T    Milieu::white[] = { (T)255, (T)255, (T)255 };

Milieu::Milieu(int w, int l): UImg( w, l, 1, 3 ),width(w),length(l){
   std::srand( time(NULL) );
   cout << "Construct the Environment" << endl;
   for(int i=0; i<INITIAL_NUMBER; i++){
      this->addBug();
   }
   int n_Prudent = int(INITIAL_NUMBER*PERCENTAGE_Prudent/100);
   int n_Craintif = int(INITIAL_NUMBER*PERCENTAGE_Craintif/100);
   int n_Social = int(INITIAL_NUMBER*PERCENTAGE_Social/100);
   int n_kamikaze = int(INITIAL_NUMBER*PERCENTAGE_SUICIDE/100);
   for(int i=0; i<n_Prudent ; i++){
      listBugs[i]->setBehavior(new Careful());
   }
   for(int i=n_Prudent i<n_Prudent+n_Craintif; i++){
      listBugs[i]->setBehavior(new Craintif());
   }
   for(int i=n_Prudent+n_Craintif; i<n_Prudent+n_Craintif+n_gregarious; i++){
      listBugs[i]->setBehavior(new Gregarious());
   }
   for(int i=n_Prudent+n_Craintif+n_gregarious; i<n_Prudent+n_Craintif+n_gregarious+n_kamikaze; i++){
      listBugss[i]->setBehavior(new SuicideBoomber());
   }
   for(int i = n_Prudent+n_Craintif+n_gregarious+n_kamikaze; i<INITIAL_NUMBER; i++){
      listBugs[i]->setBehavior(new MultipleBehavior());
   }



}
Milieu::Milieu~(){
   cout << "Destruct the Milieu" << endl;
}
void Milieu::step(){
   std::vector<std::shared_ptr<Bug>> clonedBugs;
   for ( std::vector<std::shared_ptr<Bug>>::iterator it = listBugs.begin() ; it != listBugs.end() ; ++it ){
      bool col = false;
      
      if ((*it)->getAgeLimit()==0){
         (*it)->dead();
      }
      else{
         (*it)->decrementAge();}
      
      for( std::vector<std::shared_ptr<Critter>>::iterator neighbor= listBugs.begin() ; neighbor !=  listBugs.end() ; ++neighbor ){
         if(it==neighbor){
            continue;
         }

         if((*it)->collision((*neighbor).get())){
            (*it)->behaviorAfterCollision();
            col = true;
         }

      
      }

      
      std::vector<std::shared_ptr<Bug>> listNeighbors = getNeighbors((*it).get());
      if(!col && !(*it)->getIsDead()){
         (*it)->specialBehavior(listNeighbors);
      }
      //
      
   }  



   removeDeadBugs();
   cloning();
   int n = std::rand()%NMAX;
   double pro = static_cast<double>( std::rand() )/RAND_MAX;
   if(pro<P_BIRTH){
      for(int i=0; i<n; i++){
         addBug();
      }
   }

      cimg_forXY( *this, x, y ) fillC( x, y, 0, white[0], white[1], white[2] );
    for ( std::vector<std::shared_ptr<Bug>>::iterator it = listBugs.begin() ; it != listBugs.end() ; ++it ){
        (*it)->draw( *this );
      (*it)->action( *this );
    }
}

void Milieu::cloning(){
   if(listBugs.size()<30){
      int size = listBugs.size();
      for(int i=0; i<size; i++){
         if(listBugs[i]->cloning(P_CLONAGE)){
               addBug(listBugs[i]->clone());
            }
      
      }
   }
}

void Milieu::addBug(){
   Bug* b= new Bug(width, length);
   addBug(b);

}


void Milieu::addBug(Bug* b){
   std::shared_ptr<Bug> Bug;
      Bug.reset(b);
   listBugs.push_back(Bug);
}



std::vector<std::shared_ptr<Bug>> Milieu::getNeighbors(Bug* b){

   std::vector<std::shared_ptr<Bug>> list;
   for ( std::vector<std::shared_ptr<Bug>>::iterator it = listBugs.begin() ; it != listBugs.end() ; ++it ){
      if(c->getIdentity() != (*it)->getIdentity() && b->detection((*it).get())){
         list.push_back((*it));
      }
   }
   return list;
}


int Milieu::getWidth(){
   return width;
}
int Milieu::getLength(){
   return length;
}

void Milieu::removeDeadBugs(){
   std::vector<std::shared_ptr<Bug>>::iterator it = listBugs.begin();
   while(it != listBugs.end()){
      if((*it)->getIsDead()){
         listBugs.erase(it);
      }else{
         it++;
      }
   }   
}

Bug* Milieu::getBugById(int id){
   std::vector<std::shared_ptr<Bug>>::iterator it = listBugs.begin();
    while(it != listBugs.end()){
      if((*it)->getIdentity() == id){
          return (*it).get();

      }
       it++;
   } 
   return nullptr;
}