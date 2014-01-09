#include "AAssetFile.h"


AAsset * AAssetFile:: getFile(){
	return file;
}

AAssetFile::AAssetFile(AAssetManager *mgr, char * fileName){
	this->mgr = mgr;
	this->fileName = fileName;

	file = AAssetManager_open(mgr, fileName, AASSET_MODE_UNKNOWN);
//	if(mgr == NULL)
//		LOGE("MyNative", "AAssetManager NULL");

//	if (file == NULL)
//		LOGE("_ASSET_NOT_FOUND_ %s",fileName);

}

int AAssetFile::read(void* buf, size_t size, size_t count){
	return AAsset_read (file,buf,size*count);
}
