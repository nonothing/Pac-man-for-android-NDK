#include "Sound/OSLSound.h"
#include "unistd.h"

OSLSound::~OSLSound(){

}
OSLSound::OSLSound( OSLContext * context){
	this->context = context;
	this->mgr = context->mgr;
	player = NULL;
	volume = 1;
}
OSLSound::OSLSound( OSLContext * context, char * path){
	this->context = context;
	this->mgr = context->mgr;
}

void OSLSound::setVolumePlayer(){
	if(player != NULL)
		if(player->sound != NULL && player->sound == this)
			player->setVolume(volume);

}
void OSLSound::setVolume(float volume){
	this->volume = volume;
	if(player != NULL)
		setVolumePlayer();
}

float OSLSound::getVolume(){
	return this->volume;
}
void OSLSound::pause(){
	if(player == NULL)
			return;
	player->pauseAssert();
}

void OSLSound::play(bool isLoop){
	if(	player != NULL && player->isPaused()){
		setVolumePlayer();
		player->playAssert();
		return;
	}
	player = context->getFreePlayer(this);

	if(	player == NULL){
		return;
	}

	player->setSoundAssert(this->context->mgr, this, isLoop);
	setVolumePlayer();
	if(	player != NULL)
		player->playAssert();
}

void OSLSound::stop(){
	if(player == NULL)
		return;
	player->stopAssert();
	player = 0;
}

SLuint32 OSLSound::state(){
	if(player == NULL)
		return SL_PLAYSTATE_STOPPED;
	return  player->state();
}

bool OSLSound::isActive(){
	int newState = state();
	return !(newState == SL_PLAYSTATE_STOPPED);
}

bool OSLSound::isPlaying(){
	return state() == SL_PLAYSTATE_PLAYING;
}

bool OSLSound::isPaused(){
	return state() == SL_PLAYSTATE_PAUSED;
}

bool OSLSound::isStopped(){
	return state() == SL_PLAYSTATE_STOPPED;
}

AAsset* OSLSound::openFile(char * path){

	char fname[80];
	strcpy(fname, "");
	strcat(fname, path);
	if(mgr == NULL)
		LOGE("AAssetManager null");

	AAsset* asset = AAssetManager_open(mgr, fname, AASSET_MODE_UNKNOWN);
	if (mgr == NULL) {
		LOGE("AAssetManager NULL");
		return NULL;
	}
	if (NULL == asset) {
		LOGE("_ASSET_NOT_FOUND_ %s", fname);
		return NULL;
	}
	return asset;
}
char* OSLSound::readWAVFull(AAssetManager *mgr, BasicWAVEHeader* header){
	char* buffer = 0;
	AAsset * file = openFile(filename);
	if (!file) {
		LOGE("no file %s in readWAV",filename);
		return 0;
	}

	char extra[2];
	int res = AAsset_read (file,header,sizeof(BasicWAVEHeader));
	if(!strstr(header->data, "data")){

		AAsset_read (file,extra,2);
		header->dataSize = AAsset_getLength(file) - sizeof(BasicWAVEHeader)-2;
	}
	if(res){
			buffer = (char*)malloc(header->dataSize);
			if (buffer){
				res = AAsset_read (file,buffer,header->dataSize);
				if(res){
					AAsset_close(file);
					return buffer;
				}
				free(buffer);
			}
	}
	AAsset_close(file);
	return 0;
}

void OSLSound::LogHeaders(){
	LOGI("dataSize = %i ",header.dataSize);
	LOGI("bitsPerSample = %i ",header.bitsPerSample);
	LOGI("bytesPerSec = %i ",header.bytesPerSec);
	LOGI("samplesPerSec = %i ",header.samplesPerSec);
	LOGI("fmtSize = %i ",header.fmtSize);
	LOGI("riffSize = %i ",	header.riffSize);
	LOGI("channels = %i ",	header.channels);
}


void OSLSound::load(char* filename) {
	strcpy(this->filename, filename);
	buf = readWAVFull(mgr, &header);
	dataSize = header.dataSize;
}

char * OSLSound::getBuffer(){
	return buf;
}
long OSLSound::getSize(){
	return dataSize;
}


