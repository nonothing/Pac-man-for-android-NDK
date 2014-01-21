#ifndef Blinky_H_
#define Blinky_H_

#include "model/Spirit/Spirit.h"
#include "model/Point.h"

class Blinky: public Spirit {

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
