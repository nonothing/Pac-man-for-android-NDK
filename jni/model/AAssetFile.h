#ifndef AAssetFile_H_
#define AAssetFile_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include <android/log.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

class AAssetFile{
private:
	char * fileName;

	AAsset* file;
	AAssetManager *mgr;

	AAssetFile(){}
	public:

	AAsset * getFile();
	AAssetFile(AAssetManager *mgr, char * fileName);

	int read(void* buf, size_t size, size_t count);
	void close(){
//		LOGI("file %s closed", fileName);
		AAsset_close(file);
	}
	~AAssetFile(){ }
	off_t size() { return AAsset_getLength (file); }

};
#endif /* AAssetFile_H_ */
