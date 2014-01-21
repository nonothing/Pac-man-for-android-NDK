#ifndef Clyde_H_
#define Clyde_H_
#include "model/Spirit/Spirit.h"
#include "model/Point.h"

class Clyde: public Spirit {

public:
	Clyde();
	Clyde(Point* point);
	void ai(World* world);
	void AIattack(World* world);
	int left();
	int right();
	int down();
	int up();

};
#endif /* Clyde_H_ */
