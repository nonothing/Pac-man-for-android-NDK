#ifndef Blinky_H_
#define Blinky_H_

#include "model/Spirit/Spirit.h"
#include "model/Point.h"

class Blinky: public Spirit {

private:
	Point* START_POINT;
	Point* DEFENCE_POINT;

public:
	Blinky();
	Blinky(Point* point);
	void ai(World* world);
	int left();
	int right();
	int down();
	int up();

};

#endif /* Blinky_H_ */
