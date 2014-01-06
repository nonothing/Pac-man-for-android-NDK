#include "World.h"
World::World(){
	player = new Player(new Point(10,10),6,30,30);
}

void World::tryToPlayerGo(){
	player->onMove(player->getDirection());
	player->setPosition(player->getBounds());
}

Player* World::getPlayer(){
	return player;
}
