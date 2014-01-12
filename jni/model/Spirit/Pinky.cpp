#include "Pinky.h"

Pinky::Pinky(Point* point) :
		Spirit(point, pinkyUp, 30, 30) {
	START_POINT = new Point(point->getX(), point->getY());
	DEFENCE_POINT =  new Point(1, 2);
}
   void Pinky::ai(World* world) {
        switch (getState()) {
        case ATTACK:
            findDirection(world, findPathFourStep(world), this);
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

Point* Pinky::findPathFourStep(World* world) {
	potencialMap(world->getPlayer()->getPosition(), this, world->bricks);

	Point* point = new Point(0, 0);
	int** map = getMap();
	int min = 0;
	int max = 999;

	for (int row = 0; row < world->getWidth(); row++) {
		for (int column = 0; column < world->getHeight(); column++) {
			if (map[row][column] == 5) {

				if (world->getPlayer()->getDirection() == LEFT) {
					if (max > row) {
						max = row;
						point = new Point(row, column, getWidth(), getHeight());
					}
				}

				if (world->getPlayer()->getDirection() == RIGHT) {
					if (min < row) {
						min = row;
						point = new Point(row, column, getWidth(), getHeight());
					}
				}

				if (world->getPlayer()->getDirection() == UP) {
					if (max > column) {
						max = column;
						point = new Point(row, column, getWidth(), getHeight());
					}
				}

				if (world->getPlayer()->getDirection() == DOWN) {
					if (min < column) {
						min = column;
						point = new Point(row, column, getWidth(), getHeight());
					}
				}

			}
		}
	}

	return point;
}

    int Pinky::left() {
        return pinkyLeft;
    }

    int Pinky::right() {
        return pinkyRight;
    }

    int Pinky::down() {
        return pinkyDown;
    }

    int Pinky::up() {
        return pinkyUp;
    }

