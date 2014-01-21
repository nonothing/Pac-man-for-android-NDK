#include "Controller/SoundController.h"

SoundController::SoundController(World* world, JNIEnv* env, jobject javaAssetManager){
	this->world = world;
	assetManager = AAssetManager_fromJava(env, javaAssetManager);

	context = new OSLContext(assetManager);
	eatPoint = new OSLSound(context);
	eatPoint->load("sounds/pacman_coinin.wav");

	eatBonus = new OSLSound(context);
	eatBonus->load("sounds/eatfruit.wav");

	eatSpirit = new OSLSound(context);
	eatSpirit->load("sounds/eatspirit.wav");

	deadPlayer = new OSLSound(context);
	deadPlayer->load("sounds/death.wav");

	backgroundSound = new OSLSound(context);
	backgroundSound->load("sounds/sirensound.wav");
	backgroundSound->play(true);
}

SoundController::~SoundController(){
	LOGI("SoundController::~SoundController");
	eatPoint->stop();
	eatBonus->stop();
	backgroundSound->stop();
	delete eatPoint;
	delete eatBonus;
	delete backgroundSound;
	LOGI("SoundController::~SoundController finished");
}

void SoundController::play(){
	if(world->eatPoint())eatPoint->play(false);//TODO bug won't play first sound
	if(world->eatBonus())eatBonus->play(false);
	if(world->deadSpirit())eatSpirit->play(false);
	if(world->deadPlayer())deadPlayer->play(false);
}
