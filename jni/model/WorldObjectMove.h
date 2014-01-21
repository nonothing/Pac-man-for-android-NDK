#ifndef WorldObjectMove_H_
#define WorldObjectMove_H_
#include "Direction.h"
#include "WorldObject.h"
#include "State.h"
class WorldObjectMove: public WorldObject {

protected:
	int direction;
	int SPEED;
	int state;

public:
	WorldObjectMove(Point* point, int texture, int width, int height);
	virtual ~WorldObjectMove(){LOGI("WorldObjectMove::~WorldObjectMove finished");};
	void onMove(int direction);
	int getSpeed();
	int getState();
	int getDirection();
	void setState(int state);
	void setDirection(int direction);
	void setPosition(Rectangle* rect);
	void setNext(int speedX, int speedY);
	int getPointX();
	int getPointY();

};
#endif /* WorldObjectMove_H_ */
