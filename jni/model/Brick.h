#ifndef BRICK_H_
#define BRICK_H_

#include "Rectangle.h"
#include "Point.h"
#include "WorldObject.h"
class Brick :public WorldObject{
public:
	Brick(){};
	Brick(Point* position , int texture ,int width, int height);
    bool tryToEat(Rectangle rectangle);
    bool tryToBonus(Rectangle rectangle);
};


#endif /* BRICK_H_ */
