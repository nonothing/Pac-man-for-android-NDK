#ifndef _OSLPlayer_
#define _OSLPlayer_
#include "log.h"
#include "Sound/OSLContext.h"
#include "assert.h"

class OSLContext;
class OSLSound;
class AAssetManager;
class OSLPlayer{
public:
	//Assert
	void LogAssert();
	void pauseAssert();
	void playAssert();
	void stopAssert();
	void setSoundAssert(AAssetManager* _mgr ,OSLSound * sound, bool isLoop);
	void initAssert(AAssetManager* _mgr ,char * filename, bool isLoop);
	void clearAssert();
	SLSeekItf fdPlayerSeek;
	SLMuteSoloItf fdPlayerMuteSolo;
	//

	OSLPlayer(OSLContext * context);
	virtual ~OSLPlayer();

	float getVolume() ;
	void setVolume(float volume) ;
	 SLuint32 state();
	bool isPlaying();
	bool isPaused();
	bool isStopped();
	OSLSound * sound;
protected:
	void clear();

	OSLContext * context;
	SLmillibel gain_to_attenuation( float gain);

	SLDataSource audioSrc;
	SLDataLocator_OutputMix locatorOutMix;
	SLDataSink audioSnk;
	SLVolumeItf fdPlayerVolume;
	SLObjectItf playerObj;
	SLPlayItf player;
};

#endif
