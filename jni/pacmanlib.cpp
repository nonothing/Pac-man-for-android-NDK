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

#define MAX_ELAPSED_TIME 100.0f

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

extern "C" {

	JNIEXPORT void JNICALL Java_com_pacman_free_PacmanLib_init(JNIEnv* env, jobject obj, jint width, jint height, jobject pngManager, jobject assetManager){
		srand48(time(NULL));
		lastTime = getTime();
		up2Second = 0;
		framesCount = 0;


		worldController = new WorldController(new World(),new WorldRenderer(env, width,height, pngManager, assetManager));
	}


	JNIEXPORT void JNICALL Java_com_pacman_free_PacmanLib_step(JNIEnv* env, jobject obj){
		double time = getTime();
		double elapsedTime = time - lastTime;
		lastTime = time;
		if(elapsedTime > MAX_ELAPSED_TIME){
			LOGE("Critical elapsed time: %f", elapsedTime);
			elapsedTime = MAX_ELAPSED_TIME;
		}

		worldController->actionPerformed();

		up2Second += elapsedTime;
		++framesCount;
		if(up2Second >= 1000){
			LOGI("FPS: %d", framesCount);
			up2Second = 0;
			framesCount = 0;
		}
	}

	JNIEXPORT jboolean JNICALL Java_com_pacman_free_PacmanLib_stop(JNIEnv* env, jobject obj){
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
		delete worldController;
//		Art::freeENV(env);
		LOGI("native free OK");
	}

}

