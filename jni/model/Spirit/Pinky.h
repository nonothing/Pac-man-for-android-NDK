#ifndef Pinky_H_
#define Pinky_H_

#include "model/Spirit/Spirit.h"
#include "model/Point.h"

class Pinky: public Spirit {

private:
	Point* findPathFourStep(World* world);
public:
	Pinky();
	Pinky(Point* point);
	void ai(World* world);
	int left();
	int right();
	int down();
	int up();

};

#endif /* Pinky_H_ */
