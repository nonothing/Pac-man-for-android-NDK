#include "Inky.h"

Inky::Inky(Point* point) :
		Spirit(point, inkyUp, 30, 30) {
	START_POINT = new Point(point->getX(), point->getY());
	DEFENCE_POINT = new Point(21, 13);
}
   void Inky::ai(World* world) {
        switch (getState()) {
        case ATTACK:
            findDirection(world, doubleVectorBetweenTwoPoints(findPathTwoStep(world), world->spirits->get(0)->getPosition() ), this);
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

     Point* Inky::doubleVectorBetweenTwoPoints(Point* point1, Point* point2) {

        int aMatrix[] = { point2->getX() / getWidth(), point2->getY() / getHeight(), 1 };
        int bMatrix[3][3] = { { -1, 0, 0 }, { 0, -1, 0 },
                { 2 * (point1->getX() / getWidth()), 2 * (point1->getY() / getHeight()), 1 } };

        int point [3];

        for (int column = 0; column < 3; column++) {
            for (int inner = 0; inner < 3; inner++) {
                point[column] += aMatrix[inner] * bMatrix[inner][column];
            }

        }

        if (point[X] >= 25) {
            point[X] = 24;
        }
        if (point[X] < 1) {
            point[X] = 1;
        }
        if (point[Y] >= 14) {
            point[Y] = 13;
        }
        if (point[Y] < 1) {
            point[Y] = 1;
        }

        return new Point(point[X], point[Y],getWidth(), getHeight());
    }


     Point* Inky::findPathTwoStep(World* world) {
        potencialMap(world->getPlayer()->getPosition(), this, world->bricks);

        int** map = getMap();
        int min = 0;
        int max = 999;

        Point* point = new Point(0,0);
        for (int row = 0; row < world->getWidth(); row++) {
            for (int column = 0; column < world->getHeight(); column++) {
                if (map[row][column] == 3) {

                    if (world->getPlayer()->getDirection() == LEFT) {
                        if (max > row) {
                            max = row;
                            point = new Point(row, column,getWidth(), getHeight());
                        }
                    }

                    if (world->getPlayer()->getDirection() == RIGHT) {
                        if (min < row) {
                            min = row;
                            point = new Point(row, column,getWidth(), getHeight());
                        }
                    }

                    if (world->getPlayer()->getDirection() == UP) {
                        if (max > column) {
                            max = column;
                            point = new Point(row, column,getWidth(), getHeight());
                        }
                    }

                    if (world->getPlayer()->getDirection() == DOWN) {
                        if (min < column) {
                            min = column;
                            point = new Point(row, column,getWidth(), getHeight());
                        }
                    }

                }
            }
        }

        return point;
    }

     int Inky::left() {
        return inkyLeft;
    }

     int Inky::right() {
        return inkyRight;
    }

     int Inky::down() {
        return inkyDown;
    }

     int  Inky::up() {
        return inkyUp;
    }

