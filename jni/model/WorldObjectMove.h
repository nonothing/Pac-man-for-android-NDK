#include "Direction.h"
#include "WorldObject.h"
class WorldObjectMove: public WorldObject {

protected:
	int direction;
	int SPEED;
	int state;

public:
	WorldObjectMove(Point* point, int texture, int width, int height);
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