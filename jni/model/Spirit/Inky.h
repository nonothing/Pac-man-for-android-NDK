#ifndef Inky_H_
#define Inky_H_

#include "model/Spirit/Spirit.h"
#include "model/Point.h"

class Inky: public Spirit {

private:
	Point* START_POINT;
	Point* DEFENCE_POINT;
	 static const  int Y = 1;
	 static const int X = 0;
	 Point* doubleVectorBetweenTwoPoints(Point* point1, Point* point2);
	 Point* findPathTwoStep(World* world);

public:
	Inky();
	Inky(Point* point);
	void ai(World* world);
	int left();
	int right();
	int down();
	int up();

};

#endif /* Inky_H_ */
