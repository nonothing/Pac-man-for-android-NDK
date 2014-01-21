#ifndef SOUNDCONTROLLER_H_
#define SOUNDCONTROLLER_H_

#include "model/World.h"
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>
#include "Sound/OSLContext.h"
#include "Sound/OSLSound.h"

class SoundController{
	public:
	SoundController(World* world,JNIEnv* env, jobject javaAssetManager);
	~SoundController();
	void play();
	private:
	World* world;
	AAssetManager* assetManager;
	OSLContext * context;
	OSLSound * eatPoint;
	OSLSound * eatBonus;
	OSLSound * eatSpirit;
	OSLSound * deadPlayer;
	OSLSound * backgroundSound;
};


#endif /* SOUNDCONTROLLER_H_ */
