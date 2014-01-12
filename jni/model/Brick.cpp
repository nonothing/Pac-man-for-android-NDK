#include "Brick.h"
Brick::Brick(Point* position, int texture, int width, int height) :
		WorldObject(position, texture, width, height) {

}

bool Brick::tryToBonus(Rectangle* rectangle){
	  if (bounds->intersects(rectangle) && getTexture() == bonus) {
	            setTexture(background);
	            return true;
	        }
	        return false;
}

bool Brick::tryToEat(Rectangle* rectangle) {
	if (bounds->intersects(rectangle) && getTexture() == point) {
		setTexture(background);
		return true;
	}
	return false;
}
