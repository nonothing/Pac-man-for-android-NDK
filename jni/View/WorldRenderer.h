#ifndef WorldRenderer_H_
#define WorldRenderer_H_

#include "log.h"

#include "Art.h"
#include "model/World.h"

class WorldRenderer{
public:
	WorldRenderer(JNIEnv* env, jint _screenWidth, jint _screenHeight, jobject _pngManager, jobject javaAssetManager);
	void setWorld(World* world);
	void initLogic();
	void initGraphics(Art* _art);
	bool stop();
	void render();
	void load();
	void draw(int _texture, GLfloat shiftX, GLfloat shiftY);
	void create(GLuint _shiftProgram, Art* _art);
	virtual ~WorldRenderer();
	Art* art;
	World* world;
	float tileSize;
	GLuint stableProgram;
	GLuint stableVertexHandle, stableTextureHandle;
	GLuint stableMapHandle, stableMatrixHandle;
	GLuint shiftProgram;
	GLuint shiftVertexHandle, shiftTextureHandle;
	GLuint shiftMapHandle, shiftMatrixHandle;
	GLuint shiftHandle;

	GLuint verticesBufferId, indicesBufferId;

};

#endif /* WorldRenderer_H_ */
