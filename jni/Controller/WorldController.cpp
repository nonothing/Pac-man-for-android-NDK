#include "WorldController.h"

WorldController::WorldController(World* _world,WorldRenderer* worldRenderer) {
	this->worldRenderer = worldRenderer;
	this->world = _world;
	this->worldRenderer->setWorld(world);
	direction = LEFT;
}

void WorldController::startGame() {

}

void WorldController::onPause() {

}

void WorldController::onResume() {

}

void WorldController::setSound(bool isSound) {

}

void WorldController::newGame() {

}

void WorldController::actionPerformed() {

	world->tryToPlayerGo(direction);
	worldRenderer->render();
}

void WorldController::setScore(int score) {

}

void WorldController::nextLevel(int level, int record) {

}

void WorldController::onTouch(int ACTION, int x, int y) {
	switch (ACTION) {
	case TOUCH_DOWN:
		touchX = x;
		touchY = y;
		break;
	case TOUCH_MOVE:
		if (touchX > x && abs(x - touchX) > 20 && abs(y - touchY) < 60)
			direction = LEFT;
		if (touchX < x && abs(x - touchX) > 20 && abs(y - touchY) < 60)
			direction = RIGHT;
		if (touchY > y && abs(y - touchY) > 20 && abs(x - touchX) < 60)
			direction = UP;
		if (touchY < y && abs(y - touchY) > 20 && abs(x - touchX) < 60)
			direction = DOWN;
		break;
	case TOUCH_UP:
		if (touchX > x && abs(y - touchY) < 60)
			direction = LEFT;
		if (touchX < x && abs(y - touchY) < 60)
			direction = RIGHT;
		if (touchY > y && abs(x - touchX) < 60)
			direction = UP;
		if (touchY < y && abs(x - touchX) < 60)
			direction = DOWN;
		break;
	}
}
