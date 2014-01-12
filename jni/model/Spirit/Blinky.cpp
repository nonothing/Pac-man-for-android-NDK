#include "model/Spirit/Blinky.h"

Blinky::Blinky(Point* point) :
		Spirit(point, blinkyUp, 30, 30) {
	START_POINT = new Point(point->getX(), point->getY());
	DEFENCE_POINT = new Point(21, 1);
}

void Blinky::ai(World* world) {
	switch (getState()) {
	case ATTACK:
		findDirection(world, world->getPlayer()->getPosition(), this);
		break;
	case DEFENCE:
		findDirection(world, DEFENCE_POINT->multiply(getWidth()), this);
		break;
	case DEAD:
		findDirection(world, START_POINT->multiply(getWidth()), this);
		break;
	}

	move(world);
}

int Blinky::left() {
	return blinkyLeft;
}

int Blinky::right() {
	return blinkyRight;
}

int Blinky::down() {
	return blinkyDown;
}

int Blinky::up() {
	return blinkyUp;
}

