#include "Point.h"

Point::Point(int x, int y) {
	this->x = x;
	this->y = y;
}

Point::Point(int x, int y, int width, int height) {
	this->x = x * width;
	this->y = y * height;
}

Point::Point(Rectangle* rectangle) {
	this->x = rectangle->getX();
	this->y = rectangle->getY();
}

int Point::getX() {
	return x;
}

int Point::getY() {
	return y;
}

