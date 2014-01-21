#ifndef Player_H_
#define Player_H_
#include "WorldObjectMove.h"
#include "View/ETexture.h"
#include "Brick.h"
#include  "templates/list.h"
#include "log.h"
class Player :public WorldObjectMove{
private:
	int life;
	bool isOpen;
public:
Player(Point* position , int texture ,int width, int height);
~Player(){
	LOGI("Player::~Player finished");
};
    bool eatPoint(List<Brick*>* bricks);
    bool eatBonus(List<Brick*>* bricks);

    void animate();
    int getLife();
    void setLife(int life);

};
#endif /* Player_H_ */
