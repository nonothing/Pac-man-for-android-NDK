#ifndef Level_H_
#define Level_H_

#include "templates/list.h"
#include "model/Brick.h"

class Level{
public:
	  List<Brick*>* bricks;
	  Point* pointBlinky;
	  Point* pointInky;
	  Point* pointPinky;
	  Point* pointClyde;
	  ~Level(){
		  delete bricks;
		  delete pointBlinky;
		  delete pointInky;
		  delete pointPinky;
		  delete pointClyde;
	  }
};
#endif /* Level_H_ */
