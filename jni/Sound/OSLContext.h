#ifndef _OSLContext_
#define _OSLContext_

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include "Sound/OSLPlayer.h"
#include "Sound/OSLSound.h"
#include "View/Art.h"

#define MAX_BUF_PLAYERS_COUNT 8
#define MAX_ASSET_PLAYERS_COUNT 16
class OSLContext
{
private:
	void initPlayers();

	SLEngineItf engine;
	SLObjectItf engineObj;
    SLObjectItf outputMixObj;
    OSLPlayer * assetPlayers[MAX_ASSET_PLAYERS_COUNT];
public:
    void pause();
    void resume();
    OSLPlayer * getFreePlayer(OSLSound * sound);
	OSLContext (AAssetManager *mgr);
	~OSLContext ();
	AAssetManager *mgr;
	SLObjectItf getOutputMixObject(){
		return outputMixObj;
	}
	SLEngineItf getEngine(){
		return engine;
	}

};

#endif
