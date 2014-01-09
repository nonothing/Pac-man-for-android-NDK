#ifndef ART_H_
#define ART_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <jni.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

#include "log.h"
#include "templates/list.h"

#include "View/Texture.h"
#include "View/Variables.h"
#include "View/ETexture.h"
#include "model/AAssetFile.h"
#include "model/Brick.h"

class Art {

public:
	Art();
	void init(JNIEnv* env, jint screenWidth, jint screenHeight, jobject _pngManager, jobject javaAssetManager);
	GLuint getTexture(int id);
	void freeENV(JNIEnv* env);
	bool setupGraphics(int width, int height);
	GLuint shiftProgram;
	GLuint stableProgram;
	float width;
	float height;
	List<Brick*>* bricks;
private:

	const char* PATH_LEVELS;
	const char* texturesPath;
//	void loadLevels();
	JNIEnv* pmEnv;
	AAssetManager* assetManager;
	jobject pngManager;
	jclass pmClass;
	jmethodID pmOpenId;
	jmethodID pmCloseId;
	jmethodID pmGetWidthId;
	jmethodID pmGetHeightId;
	jmethodID pmGetPixelsId;

	GLfloat screenWidth;
	GLfloat screenHeight;

	GLfloat* MVPMatrix;
	Texture** texturesSources;
	GLuint* textures;

	char** shadersSources;
	GLuint* shaderPrograms;

	int levelsCount;
	GLfloat** levelsTexCoords;

	GLfloat* getMVPMatrix();
	GLfloat* getLevelTexCoords(int number);
	GLuint compileShader(GLenum shaderType, const char* pSource);
	GLuint createProgram(const char* pVertexSource,	const char* pFragmentSource);

	char* getShaderSource(int id);
	GLuint getShaderProgram(int id);
	GLuint vertexHandle;
	GLuint textureHandle;
	GLuint matrixHandle;
	GLuint mapHandle;
	GLuint shiftMapHandle;
	GLuint shiftMatrixHandle;

	void initOpenGL();

	void loadTextures();
	void generateTextures();
	Texture* loadPng(const char* filename);
	void compilePrograms();
	List<char*> loadFilesList(const char* path);
	char* loadTextFile(const char* filename);
	char* argb2rgba(unsigned int* src, int width, int weight);
	GLuint generateBrushesTexture();
	GLuint createTexture(Texture* texture);
	GLfloat* generateMVPMatrix(int width, int height);
};

#endif /* ART_H_ */
