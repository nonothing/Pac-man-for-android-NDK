#ifndef WorldController_H_
#define WorldController_H_

#include "View/WorldRenderer.h"
#include "model/ActionTouch.h"
#include "model/World.h"

class WorldController {
private:
	int direction;
//     World world;
//     GameLogic logic;
//     Timer mainTimer;
//     SoundController soundController;
//     MainActivity mainActivity;
	int touchX;
	int touchY;
	void newGame();
public:
	WorldController(World* world, WorldRenderer* worldRenderer);
	WorldRenderer* worldRenderer;
	World* world;
	void startGame();
	void onTouch(int ACTION, int x, int y);
	void onPause();
	void onResume();
	void setSound(bool isSound);
	void actionPerformed();
	void setScore(int score);
	void openNextLevel();
	void nextLevel(int level, int record);
};
#endif /* WorldController_H_ */
