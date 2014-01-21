#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>

#include <jni.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "log.h"


#include "model/ActionTouch.h"
#include "model/World.h"
#include "Controller/WorldController.h"
#include "View/Art.h"
#include "model/ReadLevel.h"
#include "Controller/SoundController.h"


#define MAX_ELAPSED_TIME 1000.0f

static double getTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000. + tv.tv_usec/1000.;
}

double lastTime;
double up2Second;
int framesCount;

WorldController* worldController;
SoundController* soundController;
World* world;
ReadLevel* readLevel;

int second=0;
bool leftDefenceSpirit;

extern "C" {

	JNIEXPORT void JNICALL Java_com_pacman_free_PacmanLib_init(JNIEnv* env, jobject obj, jint width, jint height, jobject pngManager, jobject assetManager){
		srand48(time(NULL));
		lastTime = getTime();
		up2Second = 0;
		framesCount = 0;
		readLevel = new ReadLevel(env, assetManager);
		readLevel->loadLevels();
		world = new World(readLevel->level);
		worldController = new WorldController(world,new WorldRenderer(env, width,height, pngManager, assetManager));
		soundController = new SoundController(world, env,assetManager);
	}

bool isCreate;
	JNIEXPORT void JNICALL Java_com_pacman_free_PacmanLib_step(JNIEnv* env, jobject obj){
		double time = getTime();
		double elapsedTime = time - lastTime;
		lastTime = time;
		if(elapsedTime > MAX_ELAPSED_TIME){
			LOGE("Critical elapsed time: %f", elapsedTime);
			elapsedTime = MAX_ELAPSED_TIME;
		}


		worldController->worldRenderer->render();

		up2Second += elapsedTime;
		++framesCount;
		if(up2Second >= 1000){
			LOGI("FPS: %d", framesCount);
			up2Second = 0;
			framesCount = 0;
		}
		isCreate=true;
	}

	bool leftTime;

	JNIEXPORT void JNICALL Java_com_pacman_free_PacmanLib_attackSpirits(JNIEnv* env, jobject obj){
		if(isCreate){
			worldController->actionPerformedSpirit(leftDefenceSpirit);
			if (worldController->world->getPlayer()->getState() == ATTACK) {
			                    leftTime = true;
			                }
		}
	}

	JNIEXPORT void JNICALL Java_com_pacman_free_PacmanLib_pacmanMove(JNIEnv* env, jobject obj){
		if(isCreate){
			worldController->actionPerformed();
			soundController->play();
		}
	}

	JNIEXPORT void JNICALL Java_com_pacman_free_PacmanLib_timeBonus(JNIEnv* env, jobject obj){
		if(isCreate){
			if(worldController->world->leftSpirit > 0)
				worldController->world->leftSpirit--;
			 if (leftTime) {
			                    second++;
			                    if (second >= 8 && second % 2 == 0) {
			                        leftDefenceSpirit = true;
			                    } else {
			                        leftDefenceSpirit = false;
			                    }

			                    if (second >= 12) {
			                        world->attackNPC();
			                        leftDefenceSpirit = false;
			                        second = 0;
			                        leftTime = false;
			                    }
			            }
		}
	}


	JNIEXPORT void JNICALL Java_com_pacman_free_PacmanLib_actionDown(JNIEnv* env, jobject obj, jfloat x, jfloat y) {
		worldController->onTouch(TOUCH_DOWN, x, y);
	}

	JNIEXPORT void JNICALL Java_com_pacman_free_PacmanLib_actionMove(JNIEnv* env, jobject obj, jfloat x, jfloat y) {
		worldController->onTouch(TOUCH_MOVE, x, y);
	}

	JNIEXPORT void JNICALL Java_com_pacman_free_PacmanLib_actionUp(JNIEnv* env, jobject obj, jfloat x, jfloat y) {
		worldController->onTouch(TOUCH_UP, x, y);
	}

	JNIEXPORT jboolean JNICALL Java_com_pacman_free_PacmanLib_free(JNIEnv* env, jobject obj){
		LOGI("native free");
		isCreate=false;
		delete soundController;
		delete worldController;
		LOGI("native free OK");
	}

}

