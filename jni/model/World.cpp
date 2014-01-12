#include "World.h"
#include "model/Spirit/Blinky.h"
#include "model/Spirit/Clyde.h"
#include "model/Spirit/Inky.h"
#include "model/Spirit/Pinky.h"

World::World(Level* level){
	player = new Player(new Point(10,9),pacmanUpOpen,30,30);
	player->setDirection(LEFT);
	spirits = new List<Spirit*>();
	spirits->append(new Blinky(level->pointBlinky));
	spirits->append(new Clyde(level->pointClyde));
	spirits->append(new Inky(level->pointInky));
	spirits->append(new Pinky(level->pointPinky));
	bricks = level->bricks;
	generationPoint();
	score = 0;
	countPoint = 0;
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
	eatPoint();
	eatBonus();


	for(int i=0; i < spirits->size(); i++){
		spirits->get(i)->go(this);
	}
}

Player* World::getPlayer(){
	return player;
}

int World::generationPoint(){
	int result=0;
	for(int i=0; i < bricks->size(); i++){
		if(bricks->get(i)->getTexture() == background){
			bricks->get(i)->setTexture(point);
			result++;
		}
	}
	return result;
}

bool World::eatPoint(){
	  if (player->eatPoint(bricks)) {
		  	  	  countPoint--;
		  	  	  score += 50;
	            return true;
	        }
	        return false;
}

bool World::eatBonus(){
        if (player->eatBonus(bricks)) {
            score += 500;
//            defenceNPC();//TODO
            return true;
        }
        return false;
    }


bool World::eatFruit(){
//        if(fruit->getBounds()->intersects(player->getBounds()) && fruit->getTexture()!= none){
//            fruit->setTexture(Texture->none);
//            score += 500;
//            return true;
//        }
            return false;
    }

 bool World::collidesWithLevel(Rectangle* rect) {
	 for(int i=0; i < bricks->size(); i++){
            if (bricks->get(i)->getBounds()->intersects(rect)
            		&& bricks->get(i)->getTexture() !=background
            		&& bricks->get(i)->getTexture() !=point
                    && bricks->get(i)->getTexture() != bonus
                    && bricks->get(i)->getTexture() != none
                    ) {
                return true;
            }
        }
        return false;
    }

 int World::collidesWithRefresh(Rectangle* rect){
	 return 0;
 }
