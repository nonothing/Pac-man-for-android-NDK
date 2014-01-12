#ifndef Spirit_H_
#define Spirit_H_

#include "model/Point.h"
#include "model/WorldObjectMove.h"
#include "templates/list.h"
#include "model/Brick.h"
#include "model/World.h"
#include "View/ETexture.h"

class World;
class Spirit: public WorldObjectMove {

public:
	Spirit();
	Spirit(Point* position , int texture ,int width, int height);

	virtual void ai(World* world){};
	virtual int left(){};
	virtual int right(){};
	virtual int down(){};
	virtual int up(){};
	void go(World* world);
	void move(World* world);
	void findDirection(World* world, Point* point, Spirit* spirit);
	int getCountStep();
	void setCountStep(int countStep);
	void setDefence(bool isDefence);


private:
	int countStep;
	bool leftDefence;
	void refresh(World* world);
	void onLoadImageAttack();
	void onLoadImageDead();
	void onLoadImageDefence(bool isWhite);
	void onLoadImage();
protected:
    static const int WALL = 200;
     int **map;
     int step;
     int width;
     int height;
     void changeMap(Spirit* spirit);
     void inverseMap(List<Brick*>* bricks);
     void createMap(int width, int height);
     void potencialMap(Point* point, Spirit* spirit, List<Brick*>* bricks);
     int ** getMap();

};
#endif /* Spirit_H_ */
