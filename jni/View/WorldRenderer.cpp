#include "WorldRenderer.h"

WorldRenderer::WorldRenderer(JNIEnv* env, jint _width, jint _height, jobject _pngManager, jobject javaAssetManager) {
	LOGI("Engine::constructor Engine");
	art = new Art();
	art->init(env, _width, _height, _pngManager, javaAssetManager);
	art->setupGraphics(_width, _height);
	initLogic();
	LOGI("Engine::constructor finished");

}


GLfloat texCoords[] = {
	0.0, 0.0, 1.0, 0.0, 1.0, 1.0,
	1.0, 1.0, 0.0, 1.0, 0.0, 0.0
};

void WorldRenderer::initLogic(){
	LOGI("Engine::initLogic");
    initGraphics(art);
}

void WorldRenderer::load(){
	LOGI("Engine::load");
}
void WorldRenderer::render(){
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	checkGlError("glClearColor");
	glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	checkGlError("glClear");
	if(art->isCreateTexture == true){

	for(int i=0; i < world->bricks->size()-1; i++){
		draw(world->bricks->get(i)->getTexture(),
				world->bricks->get(i)->getPosition()->getX(),
				world->bricks->get(i)->getPosition()->getY());
	}
	for(int i=0; i < world->spirits->size(); i++){
		draw(world->spirits->get(i)->getTexture(),world->spirits->get(i)->getPosition()->getX(), world->spirits->get(i)->getPosition()->getY());
	}
	draw(world->getPlayer()->getTexture(), world->getPlayer()->getPosition()->getX(),world->getPlayer()->getPosition()->getY());
	}
	glUseProgram(art->stableProgram);

}

void WorldRenderer::create(GLuint _shiftProgram, Art* _art){
	art = _art;
	shiftProgram = _shiftProgram;
	shiftHandle = glGetUniformLocation(shiftProgram, "uShift");
	shiftVertexHandle = glGetAttribLocation(shiftProgram, "aPosition");
	shiftTextureHandle = glGetAttribLocation(shiftProgram, "aTexture");
	const GLfloat PACMAN_SIZE = 1.0f;
	GLfloat tileSizeX = 30;
	GLfloat tileSizeY = 30;

	// 0 ---- 1
	// |      |
	// |      |
	// 3 ---- 2

	const int vertexLength = 8;
	const int verticesCount = 4;
	const int initVertsLength = verticesCount*vertexLength;


	//tx1, ty1 - animation step 1 and etc.
	GLfloat initVertsData[initVertsLength] = {
		//x, y, tx1, ty1, tx2, ty2, tx3, ty3

		//Vertex 0
		0.0f, 0.0f, 0.0f, 0.0f, PACMAN_SIZE, 0.0f, 0.0f, PACMAN_SIZE,
		//Vertex 1
		tileSizeX, 0.0f, PACMAN_SIZE, 0.0f, PACMAN_SIZE, 0.0f, PACMAN_SIZE, PACMAN_SIZE,
		//Vertex 2
		tileSizeX, tileSizeY, PACMAN_SIZE, PACMAN_SIZE, PACMAN_SIZE, PACMAN_SIZE, PACMAN_SIZE, PACMAN_SIZE,
		//Vertex 3
		0.0f, tileSizeX, 0.0f, PACMAN_SIZE, PACMAN_SIZE, PACMAN_SIZE, 0.0f, PACMAN_SIZE

	};

	//Rotation indices
	GLshort initInds[4*verticesCount] = {
		0, 1, 2, 3, //Right
		1, 0, 3, 2, //Left
		3, 0, 1, 2, //Down
		1, 2, 3, 0  //Up
	};

	//Create 4 groups, each of initVertsCount vertices(for rotation)
	const int verticesDataLength = initVertsLength*4;
	GLfloat* verticesData = new GLfloat[verticesDataLength];
	for(int i = 0; i < 4; ++i){
		for(int j = 0; j < verticesCount; ++j){
			verticesData[i*initVertsLength + j*vertexLength + 0] = initVertsData[j*vertexLength + 0];
			verticesData[i*initVertsLength + j*vertexLength + 1] = initVertsData[j*vertexLength + 1];
			for(int k = 2; k < vertexLength; ++k){
				verticesData[i*initVertsLength + j*vertexLength + k] = initVertsData[initInds[i*4 + j]*vertexLength + k];
			}
		}
	}

	GLshort indicesData[6] = {
		0, 1, 2, 2, 3, 0
	};

	glGenBuffers(1, &verticesBufferId);
	checkGlError("glGenBuffers(1, &verticesBufferId);");
//	LOGI("verticesBufferId: %d", verticesBufferId);

	glGenBuffers(1, &indicesBufferId);
	checkGlError("glGenBuffers(1, &indicesBufferId);");
//	LOGI("indicesBufferId: %d", indicesBufferId);

	glBindBuffer(GL_ARRAY_BUFFER, verticesBufferId);
	checkGlError("glBindBuffer(GL_ARRAY_BUFFER, verticesBufferId);");
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);
	checkGlError("glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);");

	glBufferData(GL_ARRAY_BUFFER, verticesDataLength*sizeof(GLfloat), verticesData, GL_STATIC_DRAW);
	checkGlError("glBufferData(GL_ARRAY_BUFFER, verticesDataLength*sizeof(GLfloat), verticesData, GL_STATIC_DRAW);");
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLshort), indicesData, GL_STATIC_DRAW);
	checkGlError("glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6*sizeof(GLshort), indicesData, GL_STATIC_DRAW);");

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	delete[] verticesData;

}
WorldRenderer::~WorldRenderer() {
	LOGI("Engine::~Engine");

	LOGI("Engine::~Engine finished");
}

void WorldRenderer::draw(int _texture,float  shiftX, float shiftY){
	glUseProgram(shiftProgram);

	glUniform2f(shiftHandle,(GLfloat) shiftX,(GLfloat) shiftY);

	glBindTexture(GL_TEXTURE_2D, art->getTexture(_texture));

	glBindBuffer(GL_ARRAY_BUFFER, verticesBufferId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indicesBufferId);

	//x, y, tx1, ty1, tx2, ty2, tx3, ty3
	GLsizei stride = 8 * sizeof(GLfloat);

	glVertexAttribPointer(shiftVertexHandle, 2, GL_FLOAT, GL_FALSE, stride, (void*)(0));
	glVertexAttribPointer(shiftTextureHandle, 2, GL_FLOAT, GL_FALSE, stride, (void*) (8));

	glEnableVertexAttribArray(shiftVertexHandle);
	glEnableVertexAttribArray(shiftTextureHandle);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(shiftTextureHandle);
	glDisableVertexAttribArray(shiftVertexHandle);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


void WorldRenderer::initGraphics(Art* _art){
	LOGI("Game::initGraphics");
	stableProgram = _art->stableProgram;
	shiftProgram = _art->shiftProgram;

	stableVertexHandle = glGetAttribLocation(stableProgram, "aPosition");
	checkGlError("Game -> glGetAttribLocation(aPosition)");

	stableTextureHandle = glGetAttribLocation(stableProgram, "aTexture");
	checkGlError("Game -> glGetAttribLocation(aTexture)");

	stableMapHandle = glGetUniformLocation(stableProgram, "uMap");
	checkGlError("glGetUniformLocation");

	stableMatrixHandle = glGetUniformLocation(stableProgram, "uMatrix");
	checkGlError("glGetUniformLocation");

	shiftVertexHandle = glGetAttribLocation(shiftProgram, "aPosition");
	checkGlError("glGetAttribLocation");

	shiftTextureHandle = glGetAttribLocation(shiftProgram, "aTexture");
	checkGlError("glGetAttribLocation");

	shiftMapHandle = glGetUniformLocation(shiftProgram, "uMap");
	checkGlError("glGetUniformLocation");

	shiftMatrixHandle = glGetUniformLocation(shiftProgram, "uMatrix");
	checkGlError("glGetUniformLocation");

	shiftHandle = glGetUniformLocation(shiftProgram, "uShift");
	checkGlError("glGetUniformLocation");
	create(art->shiftProgram, _art);
}

void WorldRenderer::setWorld(World* world){
	this->world = world;
}
