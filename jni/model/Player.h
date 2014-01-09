#ifndef Player_H_
#define Player_H_
#include "WorldObjectMove.h"
#include "View/ETexture.h"

class Player :public WorldObjectMove{
private:
	int life;
	bool isOpen;
public:
Player(Point* position , int texture ,int width, int height);

//    bool eatPoint(Iterable<Brick> bricks) {
//        for (Brick brick : bricks) {
//            if(brick.tryToEat(bounds))
//                return true;
//        }
//        return false;
//    }

//     bool eatBonus(Iterable<Brick> bricks) {
//        for (Brick brick : bricks) {
//            if(brick.tryToBonus(bounds)){
//                state = State.ATTACK;
//                return true;
//                }
//        }
//        return false;
//    }

    void animate();
    int getLife();
    void setLife(int life);

};
#endif /* Player_H_ */
