#ifndef World_H_
#define World_H_

#include "Player.h"
#include "Point.h"
#include "Brick.h"
#include "View/ETexture.h"
#include  "templates/list.h"
#include "log.h"
class World {
    
 private:
	 Player* player;
//  List<Spirit> spirits;

  int  width;
  int  height;
  int countPoint;
  int record;
  int score;

//  Point* pointBlinky;
//  Point* pointInky;
//  Point* pointPinky;
//  Point* pointClyde;
//  Fruit* fruit;

//    public List<Brick> bricks;
//    public List<Brick> oldBricks;


 public:
  World();
  World(List<Brick*>* b);
//  World(Level level, int record);
//     void startPointSpirit(Level level) ;
//     void nextLevel(Level level, int record);
	 List<Brick*>* bricks;
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
     int getWidth();
     int getHeight() ;
//     Iterable<Brick> getBricks();
//     List<Spirit> getSpirits() ;
     Player* getPlayer() ;
     int getRecord();
     void setRecord(int newRecord);
     int getScore();
     void setScore(int score);
//     Point getPointBlinky();
     void setPointBlinky(Point pointBlinky);
//     Point getPointinky();
     void setPointinky(Point pointinky);
//     Point getPointPinky();
     void setPointPinky(Point pointPinky);
//     Point getPointClyde() ;
     void setPointClyde(Point pointClyde);
//     Fruit getFruit();
    
};
#endif /* World_H_ */
