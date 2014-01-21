#include "Sound/OSLPlayer.h"
#include <math.h>
bool OSLPlayer::isPlaying(){
	return state() == SL_PLAYSTATE_PLAYING;
}
bool OSLPlayer::isPaused(){
	return state() == SL_PLAYSTATE_PAUSED;
}
bool OSLPlayer::isStopped(){
	return state() == SL_PLAYSTATE_STOPPED;
}
OSLPlayer::OSLPlayer(OSLContext * context){
		this->context = context;
		player = NULL;
		fdPlayerVolume = NULL;
		playerObj  = NULL;
		player  = NULL;
	}
void OSLPlayer::clear(){
	// destroy  audio player object, and invalidate all associated interfaces
	if (playerObj != NULL) {
		(*playerObj)->Destroy(playerObj);
		playerObj = NULL;
		player = NULL;
		fdPlayerVolume = NULL;
	}
}
OSLPlayer::~OSLPlayer(){
	clear();
}
SLuint32  OSLPlayer::state(){
	SLresult result;

	// make sure the URI audio player was created
	if (NULL != player) {

		SLuint32 state;

//		LOGD("state()");
		result = (*player)->GetPlayState(player, &state);
		assert(SL_RESULT_SUCCESS == result);

		return state;
	}

	return SL_PLAYSTATE_STOPPED;
}
SLmillibel OSLPlayer::gain_to_attenuation(float gain) {

	SLmillibel volume_mb;
	if (gain >= 3.0f)
		(*fdPlayerVolume)->GetMaxVolumeLevel(fdPlayerVolume, &volume_mb);
	else if (gain <= 0.02f)
		volume_mb = SL_MILLIBEL_MIN;
	else {
		volume_mb = M_LN2 / log(3.0f / (3.0f - gain)) * -1000.0f;
		if (volume_mb > 0)
			volume_mb = SL_MILLIBEL_MIN;
	}
	return volume_mb;
}
float from_attenuation( float gain ){
    return pow(10, gain/ (1000.0f * 20.0f ));
}
void OSLPlayer::setVolume(float volume){
	SLresult result;

	if ( fdPlayerVolume  != NULL) {
		SLmillibel newVolume = gain_to_attenuation(volume);

		result = (*fdPlayerVolume)->SetVolumeLevel(fdPlayerVolume, newVolume);
		assert(SL_RESULT_SUCCESS == result);
	}
}

float OSLPlayer::getVolume(){
	SLresult result;
	SLmillibel millibel;
	result = (*fdPlayerVolume)->GetVolumeLevel(fdPlayerVolume, &millibel);
	return from_attenuation(millibel);

}

void OSLPlayer::clearAssert(){
	fdPlayerSeek = NULL;
	fdPlayerMuteSolo = NULL;
}
void OSLPlayer::initAssert(AAssetManager* _mgr ,char * filename, bool isLoop){
	SLresult result;
	AAsset* asset = AAssetManager_open(_mgr, filename, AASSET_MODE_UNKNOWN);

	// open asset as file descriptor
	off_t start, length;
	int fd = AAsset_openFileDescriptor(asset, &start, &length);
	assert(0 <= fd);
	AAsset_close(asset);

	// configure audio source
	SLDataLocator_AndroidFD loc_fd = {SL_DATALOCATOR_ANDROIDFD, fd, start, length};
	SLDataFormat_MIME format_mime = {SL_DATAFORMAT_MIME, NULL, SL_CONTAINERTYPE_UNSPECIFIED};
	SLDataSource audioSrc = {&loc_fd, &format_mime};
	// configure audio sink
	SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX,  context->getOutputMixObject()};
	SLDataSink audioSnk = {&loc_outmix, NULL};
	// create audio player
	const SLInterfaceID ids[3] = {SL_IID_SEEK, SL_IID_MUTESOLO, SL_IID_VOLUME};
	const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE};
	result = (*context->getEngine())->CreateAudioPlayer(context->getEngine(), &playerObj, &audioSrc, &audioSnk,
			3, ids, req);
	assert(SL_RESULT_SUCCESS == result);
	// realize the player
	result = (*playerObj)->Realize(playerObj, SL_BOOLEAN_FALSE);
	assert(SL_RESULT_SUCCESS == result);

	// get the play interface
	result = (*playerObj)->GetInterface(playerObj, SL_IID_PLAY, &player);
	assert(SL_RESULT_SUCCESS == result);

	// get the seek interface
	result = (*playerObj)->GetInterface(playerObj, SL_IID_SEEK, &fdPlayerSeek);
	assert(SL_RESULT_SUCCESS == result);

	// get the mute/solo interface
	result = (*playerObj)->GetInterface(playerObj, SL_IID_MUTESOLO, &fdPlayerMuteSolo);
	assert(SL_RESULT_SUCCESS == result);

	// get the volume interface
	result = (*playerObj)->GetInterface(playerObj, SL_IID_VOLUME, &fdPlayerVolume);
	assert(SL_RESULT_SUCCESS == result);

	// enable whole file looping
	if(isLoop)	result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, SL_BOOLEAN_TRUE, 0, SL_TIME_UNKNOWN);
	else	    result = (*fdPlayerSeek)->SetLoop(fdPlayerSeek, SL_BOOLEAN_FALSE, 0, SL_TIME_UNKNOWN);
	assert(SL_RESULT_SUCCESS == result);

}

void OSLPlayer::setSoundAssert(AAssetManager* _mgr ,OSLSound * sound, bool isLoop){
	this->sound = sound;
	clear();
	OSLPlayer::clear();
	initAssert(_mgr,sound->filename, isLoop);
}

void OSLPlayer::pauseAssert(){
	if( player == NULL) return;
	SLresult result;

	result=  (*player)->SetPlayState(player, SL_PLAYSTATE_PAUSED);
	assert(SL_RESULT_SUCCESS == result);
}
void OSLPlayer::playAssert(){
	if( player == NULL) return;
	SLresult result;
	result=  (*player)->SetPlayState(player, SL_PLAYSTATE_PLAYING);
	assert(SL_RESULT_SUCCESS == result);
}
void OSLPlayer::stopAssert(){
	if( player == NULL) return;
	SLresult result;
	result=  (*player)->SetPlayState(player, SL_PLAYSTATE_STOPPED);
	assert(SL_RESULT_SUCCESS == result);
}
