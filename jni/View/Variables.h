static const int MAX_PATH = 256;

static const int LEVELS_ON_SIDE_COUNT = 4;
static const int MAX_LEVELS_COUNT = LEVELS_ON_SIDE_COUNT * LEVELS_ON_SIDE_COUNT;
static const int MAX_LEVEL_SIZE = 32;
static const int FONT_CONSOLAS_ROWS_COUNT = 8;
static const int FONT_CONSOLAS_COLS_COUNT = 16;

static const GLuint SHADER_PROGRAM_NONE = 0;
static const int SHADER_PROGRAM_0 = 0;
static const int SHADER_PROGRAM_SHIFT = 1;
static const int SHADER_PROGRAM_MASK_OVERLAY = 2;
static const int SHADER_PROGRAMS_COUNT = 3;

static const int SHADER_VERTEX_0 = 0;
static const int SHADER_FRAGMENT_0 = 1;
static const int SHADER_VERTEX_SHIFT = 2;
static const int SHADER_VERTEX_BRUSHES = 3;
static const int SHADER_FRAGMENT_BRUSHES = 4;
static const int SHADER_VERTEX_MASK_OVERLAY = 5;
static const int SHADER_FRAGMENT_MASK_OVERLAY = 6;
static const int SHADERS_COUNT = 7;


#define TILE_SIZE 0.5f

static GLfloat TEX_COORDS_TILE_FREE[8] = {
	0.0, 0.0,
	TILE_SIZE, 0.0,
	TILE_SIZE, TILE_SIZE,
	0.0, TILE_SIZE
};

static GLfloat TEX_COORDS_TILE_WALL[8] = {
	TILE_SIZE, 0.0,
	2*TILE_SIZE, 0.0,
	2*TILE_SIZE, TILE_SIZE,
	TILE_SIZE, TILE_SIZE
};

static GLfloat TEX_COORDS_TILE_FOOD[8] = {
	0.0, TILE_SIZE,
	TILE_SIZE, TILE_SIZE,
	TILE_SIZE, 2*TILE_SIZE,
	0.0, 2*TILE_SIZE
};
