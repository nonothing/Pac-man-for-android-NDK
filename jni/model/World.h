#ifndef World_H_
#define World_H_

#include "Player.h"
#include "Point.h"
#include "Brick.h"
#include  "templates/list.h"
#include "View/ETexture.h"
#include "log.h"
#include "model/Spirit/Spirit.h"
#include "Level.h"

class Spirit;
class World {
    
 private:
	 Player* player;

  int  width;
  int  height;
  int countPoint;
  int record;
  int score;

//  Fruit* fruit;

 public:
  World();
  World(Level* level);
//     void startPointSpirit(Level level) ;
//     void nextLevel(Level level, int record);
	 List<Brick*>* bricks;
	 List<Spirit*>* spirits;
     void startPointPlayer();
     void createSpirit() ;
     void generateFruit();
     bool collidesWithLevel(Rectangle* rect) ;
     int collidesWithRefresh(Rectangle* rect);
     int generationPoint();
     void newGame();
     bool eatFruit();
     bool eatPoint();
     bool eatBonus();
     void tryToPlayerGo(int direction);
     void defenceNPC();
     void attackNPC() ;
     bool deadPlayer ();
     bool deadSpirit();
     bool isVictory();
     bool isGameOver();
     int getWidth(){return 25;};
     int getHeight(){return 15;} ;
     Player* getPlayer() ;
     int getRecord();
     void setRecord(int newRecord);
     int getScore();
     void setScore(int score);
//     Fruit getFruit();
    
};
#endif /* World_H_ */
