#include "Sound/OSLContext.h"
#include "stddef.h"

OSLContext::OSLContext(AAssetManager *mgr){
	LOGD("oslContext");
	this->mgr = mgr;
	SLresult result;
//	pIDs[1] = {SL_IID_ENGINE};
//	pIDsRequired[1]  = {SL_BOOLEAN_TRUE};
//	result = slCreateEngine(
//	    &engineObj, /*��������� �� �������������� ������*/
//	    0, /*���������� ��������� � ������� �������������� �����*/
//	    NULL, /*������ �������������� �����, NULL, ���� ��� ��� �� �����*/
//	    lEngineMixIIDCount, /*���������� ����������, ������� ������ ����� ������������ ����������� ������*/
//	    pIDs, /*������ ID �����������*/
//	pIDsRequired /*������ ������, �����������, ��������� �� ��������������� ���������. ���� ������� SL_TRUE, � ��������� �� ��������������, ����� ���������� ��������, � ����� �������� SL_RESULT_FEATURE_UNSUPPORTED*/
//	);
	const SLuint32 lEngineMixIIDCount = 1;
	const SLInterfaceID lEngineMixIIDs[] = {SL_IID_ENGINE};
	const SLboolean lEngineMixReqs[] = {SL_BOOLEAN_TRUE};
	const SLuint32 lOutputMixIIDCount = 0;
	const SLInterfaceID lOutputMixIIDs[] = {};
	const SLboolean lOutputMixReqs[] = { };

	result = slCreateEngine(&engineObj, 0, NULL, lEngineMixIIDCount,
			lEngineMixIIDs, lEngineMixReqs);

	/*��������� ���������. ���� ����� slCreateEngine ���������� ��������� � ������ �� ���������*/
	if (result != SL_RESULT_SUCCESS ) {
		LOGE("Error after slCreateEngine");
		return;
	}

	result = (*engineObj)->Realize(engineObj, SL_BOOLEAN_FALSE );

	if (result != SL_RESULT_SUCCESS ) {
		LOGE("Error after Realize");
		return;
	}

	result = (*engineObj)->GetInterface(engineObj, SL_IID_ENGINE, &engine);

	if (result != SL_RESULT_SUCCESS ) {
		LOGE("Error after GetInterface");
		return;
	}

	result = (*engine)->CreateOutputMix(engine, &outputMixObj,
			lOutputMixIIDCount, lOutputMixIIDs, lOutputMixReqs);

	if (result != SL_RESULT_SUCCESS ) {
		LOGE("Error after CreateOutputMix");
		return;
	}

	result = (*outputMixObj)->Realize(outputMixObj, SL_BOOLEAN_FALSE );

	if (result != SL_RESULT_SUCCESS ) {
		LOGE("Error after Realize");
		return;
	}


	result = (*engine)->CreateOutputMix(engine, &outputMixObj, lOutputMixIIDCount, lOutputMixIIDs, lOutputMixReqs);

	if(result != SL_RESULT_SUCCESS){
			LOGE("Error after CreateOutputMix");
			return;
	}

	result = (*outputMixObj)->Realize(outputMixObj, SL_BOOLEAN_FALSE);

	if(result != SL_RESULT_SUCCESS){
			LOGE("Error after Realize");
			return;
	}


	initPlayers();

}

OSLContext::~OSLContext(){
	for(int i = 0; i< MAX_ASSET_PLAYERS_COUNT; ++i)
		delete assetPlayers[i];

	// destroy output mix object, and invalidate all associated interfaces
	if (outputMixObj != NULL) {
		(*outputMixObj)->Destroy(outputMixObj);
		outputMixObj = NULL;
	}

	// destroy engine object, and invalidate all associated interfaces
	if (engine != NULL) {
		(*engineObj)->Destroy(engineObj);
		engineObj = NULL;
		engine = NULL;
	}

}
void OSLContext::initPlayers(){
	for(int i = 0; i< MAX_ASSET_PLAYERS_COUNT; ++i){
		assetPlayers[i] = new OSLPlayer(this);
	}

}

void OSLContext::resume(){
	for(int i = 0; i< MAX_ASSET_PLAYERS_COUNT; ++i){
		if(assetPlayers[i]->isPaused()){
			assetPlayers[i]->playAssert();
		}
	}
}

void OSLContext::pause(){
	for(int i = 0; i< MAX_ASSET_PLAYERS_COUNT; ++i){
		if(assetPlayers[i]->isPlaying()){
			assetPlayers[i]->pauseAssert();
		}
	}
}
OSLPlayer * OSLContext::getFreePlayer(OSLSound * sound){
		for(int i = 0; i< MAX_ASSET_PLAYERS_COUNT; ++i){
			if(!assetPlayers[i]->isPlaying()){
				return assetPlayers[i];
			}
		}
		return assetPlayers[0];
}
