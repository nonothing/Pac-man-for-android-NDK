#include "World.h"
World::World(List<Brick*>* b){
	player = new Player(new Point(10,9),pacmanUpOpen,30,30);
	player->setDirection(LEFT);
	bricks = b;
}

void World::tryToPlayerGo(int direction){
	player->onMove(direction);
	if(!collidesWithLevel(player->getBounds())){
		player->setDirection(direction);
	}
	player->onMove(player->getDirection());
	if(!collidesWithLevel(player->getBounds())){
		player->setPosition(player->getBounds());
	}
}

Player* World::getPlayer(){
	return player;
}


 bool World::collidesWithLevel(Rectangle* rect) {
	 for(int i=0; i < bricks->size(); i++){
            if (bricks->get(i)->getBounds()->intersects(rect)
            		&& bricks->get(i)->getTexture() !=background
            		&& bricks->get(i)->getTexture() !=point
//                    && brick->getTexture() != bonus
//                    && brick->getTexture() != none
                    ) {
                return true;
            }
        }
        return false;
    }
