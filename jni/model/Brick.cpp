#include "Brick.h"
Brick::Brick(Point* position, int texture, int width, int height) :
		WorldObject(position, texture, width, height) {

}

bool Brick::tryToBonus(Rectangle rectangle){
	return false;
}

bool Brick::tryToEat(Rectangle rectangle){
	return false;
}
