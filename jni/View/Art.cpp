#include "Art.h"


Art::Art(){
	PATH_LEVELS = "levels";
	screenWidth = 0;
	screenHeight = 0;
	MVPMatrix = NULL;

	texturesSources = NULL;
	shadersSources = NULL;
	shaderPrograms = NULL;
	textures = NULL;


	levelsTexCoords = NULL;
	levelsCount = 0;
}

//Default textures are small

void Art::init(JNIEnv* env, jint _screenWidth, jint _screenHeight, jobject _pngManager, jobject javaAssetManager){
	LOGI("Art::init");
	freeENV(env);

	pngManager = env->NewGlobalRef(_pngManager);
	pmEnv = env;

	pmClass = env->GetObjectClass(pngManager);
	pmOpenId = env->GetMethodID(pmClass, "open", "(Ljava/lang/String;)Landroid/graphics/Bitmap;");
	pmCloseId = env->GetMethodID(pmClass, "close", "(Landroid/graphics/Bitmap;)V");
	pmGetWidthId = env->GetMethodID(pmClass, "getWidth", "(Landroid/graphics/Bitmap;)I");
	pmGetHeightId = env->GetMethodID(pmClass, "getHeight", "(Landroid/graphics/Bitmap;)I");
	pmGetPixelsId = env->GetMethodID(pmClass, "getPixels", "(Landroid/graphics/Bitmap;[I)V");

	assetManager = AAssetManager_fromJava(env, javaAssetManager);

	screenWidth = _screenWidth;
	screenHeight = _screenHeight;


//	loadLevels();
	loadTextures();

	shadersSources = new char*[SHADERS_COUNT];
	shadersSources[SHADER_VERTEX_0] = loadTextFile("shaders/shader.vrt");
	shadersSources[SHADER_FRAGMENT_0] = loadTextFile("shaders/shader.frg");
	shadersSources[SHADER_VERTEX_SHIFT] = loadTextFile("shaders/shiftShader.vrt");
	shadersSources[SHADER_VERTEX_BRUSHES] = loadTextFile("shaders/brushes.vrt");
	shadersSources[SHADER_FRAGMENT_BRUSHES] = loadTextFile("shaders/brushes.frg");
	shadersSources[SHADER_VERTEX_MASK_OVERLAY] = loadTextFile("shaders/maskOverlay.vrt");
	shadersSources[SHADER_FRAGMENT_MASK_OVERLAY] = loadTextFile("shaders/maskOverlay.frg");

	MVPMatrix = generateMVPMatrix(_screenWidth, _screenHeight);
}

void Art::initOpenGL(){
	compilePrograms();
	generateTextures();
}

GLfloat* Art::getMVPMatrix(){
	return MVPMatrix;
}

GLuint Art::getTexture(int id){
	return (0 <= id && id < TEXTURES_COUNT && textures) ? textures[id] : TEXTURE_NONE;
}

char* Art::getShaderSource(int id){
	return (0 <= id && id < SHADERS_COUNT) ? shadersSources[id] : NULL;
}

GLuint Art::getShaderProgram(int id){
	return (0 <= id && id < SHADER_PROGRAMS_COUNT) ? shaderPrograms[id] : SHADER_PROGRAM_NONE;
}


GLfloat* Art::getLevelTexCoords(int number){
	return (number >= 0 && number < levelsCount) ? levelsTexCoords[number] : NULL;
}

void Art::freeENV(JNIEnv* env){
	LOGI("Art::free");

	if(pngManager){
		env->DeleteGlobalRef(pngManager);
		pngManager = NULL;
	}

	if(MVPMatrix){
		delete[] MVPMatrix;
		MVPMatrix = NULL;
	}

	if(textures){
		glDeleteTextures(TEXTURES_COUNT, textures);
		delete[] textures;
		textures = NULL;
	}

	if(texturesSources){
		for(int i = 0; i < TEXTURES_COUNT; ++i){
			if(texturesSources[i]){
				delete texturesSources[i];
			}
		}
		delete[] texturesSources;
		texturesSources = NULL;
	}

	if(shadersSources){
		for(int i = 0; i < SHADERS_COUNT; ++i){
			if(shadersSources[i]){
				delete[] shadersSources[i];
			}
		}
		delete[] shadersSources;
		shadersSources = NULL;
	}

	if(shaderPrograms){
		for(int i = 0; i < SHADER_PROGRAMS_COUNT; ++i){
			glDeleteProgram(shaderPrograms[i]);
		}
		delete[] shaderPrograms;
		shaderPrograms = NULL;
	}


	if(levelsTexCoords){
		for(int i = 0; i < levelsCount; ++i){
			if(levelsTexCoords[i]){
				delete levelsTexCoords[i];
			}
		}
		delete[] levelsTexCoords;
		levelsTexCoords = NULL;
	}

}

Texture* Art::loadPng(const char* filename){
	LOGI("Art::loadPng(%s)", filename);

	Texture* result = new Texture();

	jstring name = pmEnv->NewStringUTF(filename);
	jobject png = pmEnv->CallObjectMethod(pngManager, pmOpenId, name);
	pmEnv->DeleteLocalRef(name);
	pmEnv->NewGlobalRef(png);

	jint width = pmEnv->CallIntMethod(pngManager, pmGetWidthId, png);
	jint height = pmEnv->CallIntMethod(pngManager, pmGetHeightId, png);

	jintArray array = pmEnv->NewIntArray(width * height);
	pmEnv->NewGlobalRef(array);
	pmEnv->CallVoidMethod(pngManager, pmGetPixelsId, png, array);

	jint *pixels = pmEnv->GetIntArrayElements(array, 0);

	result->pixels = argb2rgba((unsigned int*)pixels, width, height);
	result->width = width;
	result->height = height;

	pmEnv->ReleaseIntArrayElements(array, pixels, 0);
	pmEnv->CallVoidMethod(pngManager, pmCloseId, png);

	return result;
}

void Art::compilePrograms(){
	shaderPrograms = new GLuint[SHADER_PROGRAMS_COUNT];
	shaderPrograms[SHADER_PROGRAM_0] = Art::createProgram(shadersSources[SHADER_VERTEX_0], shadersSources[SHADER_FRAGMENT_0]);
	shaderPrograms[SHADER_PROGRAM_SHIFT] = Art::createProgram(
			shadersSources[SHADER_VERTEX_SHIFT],
			shadersSources[SHADER_FRAGMENT_0]
	);
	shaderPrograms[SHADER_PROGRAM_MASK_OVERLAY] = Art::createProgram(
			shadersSources[SHADER_VERTEX_MASK_OVERLAY],
			shadersSources[SHADER_FRAGMENT_MASK_OVERLAY]
	);
}

void Art::generateTextures(){
	LOGI("Art::generateTextures");

	textures = new GLuint[TEXTURES_COUNT];
	LOGI("Art::new textures");
	for(int i = 0; i < TEXTURES_COUNT; ++i){
		LOGI("Art::for");
		textures[i] = texturesSources[i] ? createTexture(texturesSources[i]) : TEXTURE_NONE;
	}
	LOGI("Art::forend");
	textures[TEXTURE_BRUSHES] = generateBrushesTexture();
	LOGI("Art::end");
}

GLuint Art::createTexture(Texture* texture){
	LOGI("Art::createTexture");
	GLuint textureId;
	LOGI("Art::textureId");
	glGenTextures(1, &textureId);
	LOGI("Art::glGenTextures");
	glBindTexture(GL_TEXTURE_2D, textureId);
	LOGI("Art::glBindTexture");
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	LOGI("Art::glTexParameterf");
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	LOGI("Art::glTexParameteri");
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->pixels);
	LOGI("Art::glTexImage2D");
	return textureId;
}

GLuint Art::generateBrushesTexture(){
	GLuint textureId;
	GLuint program = Art::createProgram(Art::getShaderSource(SHADER_VERTEX_BRUSHES), Art::getShaderSource(SHADER_FRAGMENT_BRUSHES));
	if(!program){
		return 0;
	}

	glUseProgram(program);

	GLuint positionHandle = glGetAttribLocation(program, "aPosition");
	checkGlError("getAttribLocation0");

	glViewport(0, 0, 1024, 1024);

	GLint oldFrameBufferId;

	glGetIntegerv(GL_FRAMEBUFFER_BINDING, &oldFrameBufferId);

	GLuint frameBufferId;
	glGenFramebuffers(1, &frameBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBufferId);

	glGenTextures(1, &textureId);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1024, 1024, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureId, 0);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat quad[] = {
		-1.0, -1.0, 1.0, -1.0, 1.0, 1.0,
		1.0, 1.0, -1.0, 1.0, -1.0, -1.0
	};

	glVertexAttribPointer(positionHandle, 2, GL_FLOAT, GL_FALSE, 0, quad);
	checkGlError("glVertexAttribPointer1");
	glEnableVertexAttribArray(positionHandle);
	checkGlError("glEnableVertexAttribArray2");

	glDrawArrays(GL_TRIANGLES, 0, 6);
	checkGlError("glDrawArrays3");

	glDisableVertexAttribArray(positionHandle);

	glBindFramebuffer(GL_FRAMEBUFFER, oldFrameBufferId);
	glDeleteFramebuffers(1, &frameBufferId);

	glDeleteProgram(program);
	glViewport(0, 0, screenWidth, screenHeight);

	return textureId;
}

GLfloat* Art::generateMVPMatrix(int w, int h){
	float near = 1.0, far = -1.0;
	float left = 0.0, right = w, bottom =h, top = 0.0;
	GLfloat* matrix = new GLfloat[16];

	// First Column
	matrix[0] = 2.0 / (right - left);
	matrix[1] = 0.0;
	matrix[2] = 0.0;
	matrix[3] = 0.0;

	// Second Column
	matrix[4] = 0.0;
	matrix[5] = 2.0 / (top - bottom);
	matrix[6] = 0.0;
	matrix[7] = 0.0;

	// Third Column
	matrix[8] = 0.0;
	matrix[9] = 0.0;
	matrix[10] = -2.0 / (far - near);
	matrix[11] = 0.0;

	// Fourth Column
	matrix[12] = -(right + left) / (right - left);
	matrix[13] = -(top + bottom) / (top - bottom);
	matrix[14] = -(far + near) / (far - near);
	matrix[15] = 1;

	return matrix;
}

char* Art::loadTextFile(const char* filename){
	LOGI("Art::loadTextFile(%s)", filename);

	AAsset* asset = AAssetManager_open(assetManager, filename, AASSET_MODE_BUFFER);
	long length = AAsset_getLength(asset);

	char* buffer = new char[length];
	long offset = 0;
	long readed = 0;
	while((readed = AAsset_read(asset, buffer + offset, length - offset)) > 0){
		offset += readed;
	}

	AAsset_close(asset);

	buffer[length - 1] = '\0';

	return buffer;
}

char* Art::argb2rgba(unsigned int* pixels, int w, int h){
	char* result = new char[w*h*4];

	unsigned int pixel;
	int i, j, offset;

	for(i = 0; i < h; ++i){
		offset = i*w*4;
		for(j = 0; j < w*4; j += 4){
			pixel = pixels[i*w + j / 4];
			result[offset + j] 		= (pixel >> 16) & 0xff;
			result[offset + j + 1]  = (pixel >> 8) & 0xff;
			result[offset + j + 2]  = pixel & 0xff;
			result[offset + j + 3]  = (pixel >> 24) & 0xff;
		}
	}
	return result;
}


void Art::loadTextures(){
	LOGI("Art:loadTextures");
	char buffer[MAX_PATH];
	texturesSources = new Texture*[TEXTURES_COUNT];
	LOGI("create texture count");
	texturesSources[blinkyUp] = loadPng("textures/blinky_1.png");
	texturesSources[blinkyDown] = loadPng("textures/blinky_2.png");
	texturesSources[blinkyLeft] = loadPng("textures/blinky_3.png");
	texturesSources[blinkyRight] = loadPng("textures/blinky_4.png");

	LOGI("create texture blinky");
	texturesSources[pacmanDownClose] = loadPng("textures/pman_2.png");
	texturesSources[pacmanDownOpen] = loadPng("textures/pman_2_2.png");
	texturesSources[pacmanUpClose] = loadPng("textures/pman_1.png");
	texturesSources[pacmanUpOpen] = loadPng("textures/pman_1_2.png");
	texturesSources[pacmanLeftClose] = loadPng("textures/pman_3.png");
	texturesSources[pacmanLeftOpen] = loadPng("textures/pman_3_2.png");
	texturesSources[pacmanRightClose] = loadPng("textures/pman_4.png");
	texturesSources[pacmanRightOpen] = loadPng("textures/pman_4_2.png");
	LOGI("create texture pacman");
	//texrute map
	texturesSources[angle_ld] = loadPng("textures/angle_ld.png");
	texturesSources[angle_lv] = loadPng("textures/angle_lv.png");
	texturesSources[angle_rd] = loadPng("textures/angle_rd.png");
	texturesSources[angle_rv] = loadPng("textures/angle_rv.png");
	texturesSources[arc_down] = loadPng("textures/arc_down.png");
	texturesSources[arc_left] = loadPng("textures/arc_left.png");
	texturesSources[arc_right] = loadPng("textures/arc_right.png");
	texturesSources[arc_up] = loadPng("textures/arc_up.png");
	texturesSources[arc2_down] = loadPng("textures/arc2_down.png");
	texturesSources[arc2_left] = loadPng("textures/arc2_left.png");
	texturesSources[arc2_right] = loadPng("textures/arc2_right.png");
	texturesSources[arc2_up] = loadPng("textures/arc2_up.png");
	texturesSources[vertical] = loadPng("textures/vertical.png");
	texturesSources[horizontal] = loadPng("textures/horizontal.png");
	texturesSources[background] = loadPng("textures/background.png");
	texturesSources[point] = loadPng("textures/point.png");
	LOGI("create texture map");

	texturesSources[TEXTURE_FONT_CONSOLAS] = loadPng("textures/font_consolas.png");
//	texturesSources[TEXTURE_ALL_LEVELS] = makeTextureFromLevels();
	texturesSources[TEXTURE_BRUSHES] = NULL;

}


 List<Brick*> getBricks(char* map) {
        List<Brick*>* bricks = new List<Brick*>();




    }



GLuint Art::compileShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint Art::createProgram(const char* pVertexSource, const char* pFragmentSource) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = compileShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        //checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        //checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}




bool Art::setupGraphics(int w, int h) {
    LOGI("Art::setupGraphics(%d, %d)", w, h);
    initOpenGL();

	GLfloat* matrix = getMVPMatrix();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    stableProgram = getShaderProgram(SHADER_PROGRAM_0);
    if (stableProgram == SHADER_PROGRAM_NONE) {
        LOGE("Art could not create program.");
        return false;
    }

    vertexHandle = glGetAttribLocation(stableProgram, "aPosition");
    checkGlError("glGetAttribLocation");
    LOGI("glGetAttribLocation(\"aPosition\") = %d\n", vertexHandle);

    textureHandle = glGetAttribLocation(stableProgram, "aTexture");
	checkGlError("glGetAttribLocation");
	LOGI("glGetAttribLocation(\"aTexture\") = %d\n", textureHandle);

	mapHandle = glGetUniformLocation(stableProgram, "uMap");
	checkGlError("glGetUniformLocation");
	LOGI("glGetAttribLocation(\"uMap\") = %d\n", mapHandle);

	matrixHandle = glGetUniformLocation(stableProgram, "uMatrix");
	checkGlError("glGetUniformLocation");
	LOGI("glGetAttribLocation(\"uMatrix\") = %d\n", matrixHandle);



	shiftProgram = getShaderProgram(SHADER_PROGRAM_SHIFT);
	if(shiftProgram == SHADER_PROGRAM_NONE){
		LOGE("Art could not create shift program");
		return false;
	}

	shiftMapHandle = glGetUniformLocation(shiftProgram, "uMap");
	checkGlError("glGetUniformLocation");

	shiftMatrixHandle = glGetUniformLocation(shiftProgram, "uMatrix");
	checkGlError("glGetUniformLocation");

    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    glUseProgram(stableProgram);
	checkGlError("glUseProgram");

	// Sets the texture units to an uniform.
	glUniform1i(mapHandle, 0);
	checkGlError("glUniform1i");

	glUniformMatrix4fv(matrixHandle, 1, GL_FALSE, matrix);
	checkGlError("glUniformMatrix4fv");

	glUseProgram(shiftProgram);

	glUniform1i(shiftMapHandle, 0);
	checkGlError("glUniform1i");

	glUniformMatrix4fv(shiftMatrixHandle, 1, GL_FALSE, matrix);
	checkGlError("glUniformMatrix4fv");

    glActiveTexture(GL_TEXTURE0);

    return true;
}
